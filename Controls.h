#ifndef CONTROLS_H
#define CONTROLS_H

namespace Controls{
	void initialize();
	void onkeydown(int keyCode);
	void onkeyup(int keyCode);
	void onmousemove(int clientX, int clientY);
	void onmousedown(int clientX, int clientY, int mouseKeyCode);
	void onmouseup(int clientX, int clientY, int mouseKeyCode);
	void onwheel(int deltaY);
	void onfocus(bool state);
};

#endif