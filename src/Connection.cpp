#include <iostream>
#include <emscripten.h>
#include "Connection.h"
#include "Browser.h"
#include "Util.h"

namespace Connection{
	State state;
	std::string serverUrl = "";
	std::vector<std::string> messages = {};

	bool urlAcquired(){
		return serverUrl.length() > 0;
	}

	void loadServerUrl(){
		EM_ASM(
			const server = window['connection'];
			if(server === undefined) return;
			let uriScheme = (server.ssl ? 'wss' : 'ws');
			let url = uriScheme + '://' + server.ip + ':' + server.port;
			_setServerUrl(allocateUTF8(url));
		);
	}

	void update(){
		SocketState readyState = getSocketState();
		processEventQueue();

		switch(readyState){
			case OPEN:
				state.connected = 1;
				processMessageQueue();
				break;
			case CLOSED:
				attempt();
				break;
			default:
				return;
		}
	}

	void processEventQueue(){
		EM_ASM({
			let socket = window['objects']['websocket'];
			if(!socket) return;

			for(let i in socket.events){
				_handle(socket.events[i]);
			}
			socket.events = [];
		});
	}

	void processMessageQueue(){
		EM_ASM({
			let socket = window['objects']['websocket'];
			for(let i in socket.messages){
				const rawMessage = socket.messages[i];
				const ptr = rawMessage[0];
				let uint8Array = HEAPU8.subarray(ptr, ptr + rawMessage[1]);
				let message = String.fromCharCode.apply(null, uint8Array);
				_receive(allocateUTF8(message));
			}
			socket.messages = [];
		});
		updatePing();
	}

	void updatePing(){

	}

	void attempt(){
		if(state.connected) return;
		loadServerUrl();
		if(urlAcquired()){
			buildWebSocket(serverUrl);
		}
	}

	void send(std::string message){
		EM_ASM_({
			let socket = window['objects']['websocket'];
			if(!socket || socket.readyState != 1) return;
			socket.send(HEAPU8.subarray($0, $0 + $1));
		}, message.c_str(), message.length());
	}

	void buildWebSocket(std::string url){
		EM_ASM_INT({
			let ws = new WebSocket(UTF8ToString($0));
			ws.binaryType = 'arraybuffer';
			ws.events = [];
			ws.messages = [];
			ws.onmessage = (function(e){
				let uint8Array = new Uint8Array(e.data);
				let buffer = Module._malloc(uint8Array.length);
				writeArrayToMemory(uint8Array, buffer);
				ws.messages.push([buffer, uint8Array.length]);
			});
			ws.onopen = (function(){
				ws.events.push(0);
			});
			ws.onclose = (function(){
				ws.events.push(1);
			});
			ws.onerror = (function(){
				ws.events.push(2)
			});
			window['objects']['websocket'] = ws;
		}, url.c_str());
	}

	SocketState getSocketState(){
		int readyState = EM_ASM_INT(
			if(window['objects']['websocket'] == null) return 3;
			return window['objects']['websocket'].readyState;
		);
		return static_cast<SocketState>(readyState);
	}

	extern "C"{
		void setServerUrl(char* url){
			serverUrl = std::string(url);
		}

		void receive(char* message){
			std::vector<std::string> splitMessages = String::split(std::string(message), '|');
			for(std::string& messagePiece : splitMessages){
				if(messagePiece.size() <= 0) continue;

				if(messagePiece[0] == '.'){ //Pings
					send(".");
					continue;
				}

				messages.push_back(messagePiece);
			}
		}

		void handle(EventCode eventCode){
			switch(eventCode){
				case EVENT_OPEN:
					send("."); //Initial Ping
					Browser::showGame();
					break;
				case EVENT_CLOSE:
					std::cout << "Connection Closed" << std::endl;
					Browser::showConnecting();
					break;
				case EVENT_ERROR:
					std::cout << "Socket Error" << std::endl;
					break;
			}
		}
	}
};