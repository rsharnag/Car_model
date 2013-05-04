/*
 * Model.h
 *
 *  Created on: 20-Oct-2012
 *      Author: rahul
 */

#ifndef MODEL_H_
#define MODEL_H_
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include "readPPM.h"
using namespace std;
#define WHEEL 0
#define DAYSKY 1
#define CHASSI 2
#define BONET 3
#define FRONTDOOR 4
#define BACKDOOR 5
#define TRUNK 6
#define WS1 7
#define WS2 8
#define STEERING 9
#define REARWINDOW 10
#define WINDSHIELD 11
#define NIGHTSKY 12
class Wheel {

public:
	GLfloat xpos, ypos, zpos;
	GLfloat xrot,yrot;
	GLfloat radius, thick;

	Wheel();
	Wheel(GLfloat x, GLfloat y, GLfloat z);
	void setpos(GLfloat x, GLfloat y, GLfloat z);
	void rotatex(GLfloat deg);
	void rotatey(GLfloat deg);
	void init(GLuint texBase,GLuint* wheelTexName,GLuint* wheelRimTexName);
	void draw();
private:
	GLUquadricObj* q;
	GLuint texBase;
};
class Car {
public:
	bool headLight;
	GLfloat bRot,d1Rot,d2Rot,tRot,ws1,ws2,steerRot;
	GLfloat xori,yori,zori;
	GLfloat wheelRot;
	GLfloat xpos,ypos,zpos;
	GLfloat vOrientation;
	GLuint texBase;
	GLfloat scaleFactor;
	Wheel wheel;
	GLfloat velocity;
	GLuint* seatTexName;GLuint* dashBoardTexName,*engineTexName,*speedoTexName;
	Car();
	virtual ~Car();
	void changeOrientation(float deg);
	void init(GLuint texBase,GLuint* wheelTexName,GLuint* wheelRimTexName,GLuint* engineTexName,GLuint* seatTexName,GLuint* dashBoardTexName,GLuint* speedoTexName);
	void setBonnetParams(GLfloat bRot){this->bRot=bRot;}
	GLfloat getBonnetParams(){return bRot;}
	void setDoor1Rotation(GLfloat d1Rot){this->d1Rot=d1Rot;}
	GLfloat getDoor1Rotation(){return this->d1Rot;}
	void setDoor2Rotation(GLfloat d2Rot){this->d2Rot=d2Rot;}
	GLfloat getDoor2Rotation(){return this->d2Rot;}
	void setTrunkParams(GLfloat tRot){this->tRot=tRot;}
	GLfloat getTrunkParams(){return this->tRot;}
	void setWindSheil1dParam(float height){this->ws1=height;}
	GLfloat getWindSheil1dParam(){return this->ws1;}
	void setWindSheil2dParam(float height){this->ws2=height;}
	GLfloat getWindSheil2dParam(){return this->ws2;}
	void setPosition(GLfloat x,GLfloat y,GLfloat z){xpos=x;ypos=y;zpos=z;}
	void setOrientation(GLfloat ori){this->vOrientation=ori;}
	void draw();
	void drawChasi();
	void drawBonet();
	void drawTrunk();
	void drawDoorBehind();
	void drawDoorFront();
	void drawWs1();
	void drawWs2();
	void drawRearWindow();
	void drawWindshield();
	void drawSteering();
	void moveforward(float dis);
	void turn(bool right,float dis,float wheelRotation);
	static const GLfloat chasis_control_points[4][4][3] ;
	static const GLfloat front_face[4][4][3];
	static const GLfloat bonet_panels1[4][4][3];
	static const GLfloat bonet_panels2[4][4][3];
	static const GLfloat windshield_panels1[4][4][3];
	static const GLfloat windshield_panels2[4][4][3];
	static const GLfloat windshield[4][4][3];
	static const GLfloat roof_top[4][4][3];
	static const GLfloat bottom_front[4][4][3];
	static const GLfloat left_front_panel[4][4][3];
	static const GLfloat left_back_panel[4][4][3];
	static const GLfloat number_plate[4][4][3];
	static const GLfloat trunk_panel_front[4][4][3];
	static const GLfloat trunk_panel_behind[4][4][3];
	static const GLfloat back_panel_front[4][4][3];
	static const GLfloat back_panel_behind[4][4][3];
	static const GLfloat bonet[4][4][3];
	static const GLfloat trunk_curve[4][4][3];
	static const GLfloat trunk_bottom[4][4][3];
	static const GLfloat window_pane_front[4][4][3];
	static const GLfloat window_pane_behind[4][4][3];
	static const GLfloat door_behind[4][4][3];
	static const GLfloat door_front[4][4][3];
	static const GLfloat door_glass_rear[4][4][3];
	static const GLfloat door_glass_front[4][4][3];
	static const GLfloat front_panel_left1[4][4][3];
	static const GLfloat front_panel_left3[4][4][3];
	static const GLfloat front_panel_left2[4][4][3];
	static const GLfloat front_panel_right1[4][4][3];
	static const GLfloat front_panel_right3[4][4][3];
	static const GLfloat front_panel_right2[4][4][3];
	static const GLfloat rear_panel_left1[4][4][3];
	static const GLfloat rear_panel_left2[4][4][3];
	static const GLfloat rear_panel_left3[4][4][3];
	static const GLfloat rear_panel_right1[4][4][3];
	static const GLfloat rear_panel_right2[4][4][3];
	static const GLfloat rear_panel_right3[4][4][3];
	static const GLfloat rear_glass_left[4][4][3];
	static const GLfloat rear_glass_right[4][4][3];
	static const GLfloat tyre_guard_front[4][4][3];
	static const GLfloat tyre_guard_front_flat[4][4][3];
	static const GLfloat tyre_guard_rear[4][4][3];
	static const GLfloat tyre_guard_rear_flat[4][4][3];
	static const GLfloat bottom_front1[4][4][3];
	static const GLfloat bottom_front2[4][4][3];
};

//class TessQuad {
//public:
//	int ind, fact, texRepeat;//fact is degree of tessellation texRepeat is how many times to repeate tex
//	GLfloat x[4], y[4], z[4];
//	void init(int f);
//	void vertex(GLfloat x1, GLfloat y1, GLfloat z1);
//	void draw();
//};
class Environment {
public:
	GLfloat xpos, ypos, zpos;
	GLuint texBase;
//	GLfloat length, breadth, height;
	GLUquadricObj* quadric;
	GLfloat skyRadius;
	bool night;
	GLuint* skyTexture,* groundTexture,* roadTexture,*nightSkyTexture;
	Environment();
	void init(GLuint texBase,GLuint* wheelTexName,GLuint* wheelRimTexName,GLuint* roadTexture,GLuint* nightSkyTexture);
	void setpos(GLfloat x, GLfloat y, GLfloat z);
	void draw();
};
#endif /* MODEL_H_ */
