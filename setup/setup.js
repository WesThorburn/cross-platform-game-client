var Module = Module || {};
Module["postRun"] = Module["postRun"] || [];
Module["postRun"].push((function(){
	window["objects"] = {
		"contexts": [],
		"websocket": null
	};
	window["input"] = {
		"onkeydown": _onkeydown,
		"onkeyup": _onkeyup,
		"onmousemove": _onmousemove,
		"onmousedown": _onmousedown,
		"onmouseup": _onmouseup,
		"onwheel": _onwheel,
		"onblur": _onblur,
		"onfocus": _onfocus,
		"touchstart": _touchstart,
		"touchend": _touchend,
		"touchmove": _touchmove
	};
	window["size"] = {
		"orientationchange": _orientationchange,
		"onresize": _onresize
	};
}));

window.onresize = function(e){
	if(!window["size"] || !e) return;

	window["size"]["onresize"]();
};

function orientationchange(e){
	if(!window["size"] || !e) return;

	window["size"]["orientationchange"]();
}

document.onkeydown = function(e){
	if(!window["input"] || !e) return;

	window["input"]["onkeydown"](e.keyCode);
	
	if(e.keyCode == 32) e.preventDefault();
};

document.onkeyup = function(e){
	if(!window["input"] || !e) return;

	window["input"]["onkeyup"](e.keyCode);

	if(e.keyCode == 32) e.preventDefault(); //Disables spacebar scrolling
};

document.onmousemove = function(e){
	if(!window["input"] || !e) return;

	window["input"]["onmousemove"](e.clientX, e.clientY);
};

document.onmousedown = function(e){
	if(!window["input"] || !e) return;

	window["input"]["onmousedown"](e.clientX, e.clientY, e.which);
};

document.onmouseup = function(e){
	if(!window["input"] || !e) return;

	window["input"]["onmouseup"](e.clientX, e.clientY, e.which);
};

document.onwheel = function(e){
	if(!window["input"] || !e) return;

	window["input"]["onwheel"](e.deltaY);

	event.preventDefault();
};

window.onblur = function(){
	if(!window["input"]) return;
	window["input"]["onblur"]();
};

window.onfocus = function(){
	if(!window["input"]) return;
	window["input"]["onfocus"]();
};

function touchStart(e){
	e.preventDefault();
	for(var i = 0; i < e.changedTouches.length; i++){
		var touch = e.changedTouches[i];
		if(!window["input"] || !e) continue;
		window["input"]["touchstart"](touch.identifier, touch.clientX, touch.clientY);
	}
}

function touchEnd(e){
	e.preventDefault();
	for(var i = 0; i < e.changedTouches.length; i++){
		var touch = e.changedTouches[i];
		if(!window["input"] || !e) continue;
		window["input"]["touchend"](touch.identifier);
	}
}

function touchMove(e){
	e.preventDefault();
	for(var i = 0; i < e.changedTouches.length; i++){
		var touch = e.changedTouches[i];
		if(!window["input"] || !e) continue;
		window["input"]["touchmove"](touch.identifier, touch.clientX, touch.clientY);
	}
}

window.addEventListener('orientationchange', orientationchange);
window.addEventListener("touchstart", touchStart, {passive: false});
window.addEventListener("touchend", touchEnd, {passive: false});
window.addEventListener("touchcancel", touchEnd, {passive: false});
window.addEventListener("touchmove", touchMove, {passive: false});