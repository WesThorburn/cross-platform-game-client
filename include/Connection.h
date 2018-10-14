#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <vector>

namespace Connection{
	struct State{
		bool connected = 0;
	};
	enum SocketState{CONNECTING, OPEN, CLOSING, CLOSED};
	enum EventCode{EVENT_OPEN, EVENT_CLOSE, EVENT_ERROR};

	extern State state;
	extern std::string serverUrl;
	extern std::vector<std::string> messages;

	bool urlAcquired();
	void loadServerUrl();
	void update();
	void send(std::string message);
	void processEventQueue();
	void processMessageQueue();
	void processMessages();
	void updatePing();
	void attempt();
	void buildWebSocket(std::string url);
	SocketState getSocketState();

	extern "C"{
		void setServerUrl(char* url);
		void receive(char* message);
		void handle(EventCode eventCode);
	}
};

#endif