#ifndef CAMERA_H
#define CAMERA_H

class Camera{
public:
	Camera();
	void update();
	int getX(){ return m_x; }
	int getY(){ return m_y; }
	int getWidth(){ return m_width; }
	int getHeight(){ return m_height; }
	void setXYOffset(int xOffset, int yOffset);
private:
	int m_x = 0, m_y = 0;
	int m_width = 1366, m_height = 768;
	int m_xOffset = 0, m_yOffset = 0;
};

#endif