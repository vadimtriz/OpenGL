#include <iostream>
#include "MyWindow.h"
#include <cmath>
#include <chrono>
#include <ctime>


MyWindow::MyWindow()
:Window(WINDOW_WIDTH, WINDOW_HEIGHT)
{
	SDL_SetWindowTitle(_window.get(), "My OpenGL Window");

}
void MyWindow::moving_camera() {
	_position_camer_x =  3.0 *cos(_angle_rotation_camera);
	_position_camer_y = 3.0 *sin(_angle_rotation_camera);

	gluLookAt(
			_position_camer_x, _position_camer_y, 2.0,
			0.0, 0.0, 0.0,
			0.0, 0.0, 1.0);
}

void MyWindow::draw_clock() {

	for (double a = 0.0; a < 360.0; a += 360.0 / 12.0) {
		glPushMatrix();
		glRotated(a, 0.0, 0.0, 1.0);
		glTranslated(0.0, 0.9, 0);

		glBegin(GL_QUADS);
		glColor3d(0.3, 1.0, 1.0);
		glVertex2d(-0.05, 0.1);
		glVertex2d(0.05, 0.1);
		glVertex2d(0.05, -0.1);
		glVertex2d(-0.05, -0.1);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glRotated(a, 0.0, 0.0, 1.0);
		glTranslated(0.0, 0.9, 0);
		glBegin(GL_QUADS);
		glColor3d(0.3, 1.0, 1.0);
		glVertex2d(-0.02, 0.05);
		glVertex2d(0.02, 0.05);
		glVertex2d(0.02, -0.05);
		glVertex2d(-0.02, -0.05);
		glEnd();
		glPopMatrix();

	}
	for (double a = 0.0; a < 360.0; a += 360.0 / 60.0) {


		glPushMatrix();
		glRotated(a, 0.0, 0.0, 1.0);
		glTranslated(0.0, 0.9, 0);
		glBegin(GL_QUADS);
		glColor3d(0.3, 1.0, 1.0);
		glVertex2d(-0.02, 0.05);
		glVertex2d(0.02, 0.05);
		glVertex2d(0.02, -0.05);
		glVertex2d(-0.02, -0.05);
		glEnd();
		glPopMatrix();

		}



	double hours_angle = fmod(_hours, 60.0) /12 * 360.0;
	glPushMatrix();
	glRotated(hours_angle, 0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glColor3d(0.0, 1.0, 0.0);
	glVertex2d(0.0, 0.0);
	glVertex2d(-0.04, 0.1);
	glVertex2d(0.0, 0.6);
	glVertex2d(0.04, 0.1);
	glEnd();
	glPopMatrix();


	double minutes_angle = fmod(_minutes, 60.0) /60 * 360.0;
	glPushMatrix();
	glRotated(minutes_angle, 0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glColor3d(0.0, 0.0, 0.1);
	glVertex2d(0.0, 0.0);
	glVertex2d(-0.04, 0.1);
	glVertex2d(0.0, 0.9);
	glVertex2d(0.04, 0.1);
	glEnd();
	glPopMatrix();



	double seconds_angle = fmod(_seconds, 60.0) / 60.0 * 360.0;
	glPushMatrix();
	glRotated(seconds_angle, 0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glColor3d(1.0, 0.0, 0.0);
	glVertex2d(0.0, 0.0);
	glVertex2d(-0.025, 0.1);
	glVertex2d(0.0, 0.9);
	glVertex2d(0.025, 0.1);
	glEnd();
	glPopMatrix();




}

void MyWindow::render()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLoadIdentity();

	moving_camera();



	glBegin(GL_QUADS);


	glColor3d(0.3, 0.3, 0.3);
	glVertex3d(-1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(1.0, -1.0, 0.0);
	glVertex3d(-1.0, -1.0, 0.0);


	glColor3d(0.2, 0.2, 0.2);
	glVertex3d(-1.0, 1.0, -0.1);
	glVertex3d(1.0, 1.0, -0.1);
	glVertex3d(1.0, -1.0, -0.1);
	glVertex3d(-1.0, -1.0, -0.1);


	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(-1.0, 1.0, 0.0);
	glVertex3d(-1.0, 1.0, -0.1);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, -0.1);

	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, -0.1);
	glVertex3d(1.0, -1.0, 0.0);
	glVertex3d(1.0, -1.0, -0.1);

	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(-1.0, -1.0, 0.0);
	glVertex3d(-1.0, -1.0, -0.1);
	glVertex3d(1.0, -1.0, 0.0);
	glVertex3d(1.0, -1.0, -0.1);

	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(-1.0, -1.0, 0.0);
	glVertex3d(-1.0, -1.0, -0.1);
	glVertex3d(-1.0, 1.0, 0.0);
	glVertex3d(-1.0, 1.0, -0.1);


	glEnd();
	glTranslated(0.0, 0.0, 0.05);

	draw_clock();
}

void MyWindow::setupGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.25f, 0.45f, 1.0f);

	double aspect_ratio = double(width()) / double(height());

	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, aspect_ratio, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void MyWindow::update()
{
	auto now = std::chrono::high_resolution_clock::now();
	auto tt = std::chrono::high_resolution_clock::to_time_t(now);
	auto local_time = *localtime(&tt);

	_seconds = local_time.tm_sec + 60*local_time.tm_min + 3600 * local_time.tm_hour;
	_minutes = (local_time.tm_sec + 60*local_time.tm_min + 3600 * local_time.tm_hour)/60;
	_hours = (local_time.tm_sec + 60*local_time.tm_min + 3600 * local_time.tm_hour)/3600;

	if (_angle_rotation_camera == 360){
	_angle_rotation_camera = 0.0;
	}else{
		_angle_rotation_camera += 0.0001;
	}


}
