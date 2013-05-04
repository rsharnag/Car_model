/*
 * Car.h
 *
 *  Created on: 19-Oct-2012
 *      Author: rahul
 */

#ifndef CAR_H_
#define CAR_H_

#include <GL/glut.h>
#include <cstdlib>
#include <GL/glu.h>
#include <GL/gl.h>
#include "Model.h"
#include "Camera.h"
#include "KeyFrameRecPlay.h"
// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127
unsigned char keyboard[256];
GLsizei sWidth, sHeight;
bool l0,l1,l2;
GLuint wheelTexName;
	GLuint texBase;
	GLuint wheelRimTexName;
	GLuint skyTexName;
	GLuint groundTexName;
	GLuint roadTexName;
	GLuint engineTexName,seatTexName,dashBoardTexName,speedoTexName,nightSkyTexName;
//Wheel wheel;
Environment env;
Car car;
KeyFrameRecPlay animation;
GLfloat rot;
Camera cam;
GLfloat spot_direction[3];
GLfloat headlight2_position[4];
GLfloat headlight1_position[4];
bool turn_right=false,turn_left=false,trans=false;
bool environmentLight=true,headlightSwitch=true;
#endif /* CAR_H_ */
