#ifndef MYWINDOW_H_
#define MYWINDOW_H_

#include "Window.h"

class MyWindow: public Window {
public:
	static constexpr int WINDOW_WIDTH = 1080;
	static constexpr int WINDOW_HEIGHT = 720;

	virtual void update();
	virtual void render();
	virtual void setupGL();

protected:
	double _seconds {0.0};
	double _minutes {0.0};
	double _hours {0.0};
	double _position_camer_x {0.0};
	double _position_camer_y {0.0};
	double _angle_rotation_camera {0.0};

	void draw_clock();
	void moving_camera();

public:
	MyWindow();
	virtual ~MyWindow() = default;

};

#endif
