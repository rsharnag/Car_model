/*
 * Camera.cpp
 *
 *  Created on: 27-Oct-2012
 *      Author: rahul
 */

#include "Camera.h"

Camera::Camera() {
	ex=0;
	ey=0;
	ez=2;
	ux=0;
	uy=1;
	uz=0;
	xzdeg=0;
	updateLookAt();
	cameraMovementEnable=false;
	cameraId=0;


}
void Camera::setCameraPos(float x,float y,float z){
	ex = x;
	ey = y;
	ez = z;
	updateLookAt();
}
void Camera::updateLookAt(){
	lx=ex+sin(xzdeg/180.0*M_PI);
	ly=ey+sin(xydeg/180.0*M_PI);
	lz=ez-cos(xzdeg/180.0*M_PI);
}
void Camera::lookUp(float d)
{
	xydeg+=d;
	if(xydeg>60) xydeg=60;
	if(xydeg<-60) xydeg=-60;
	updateLookAt();
}
void Camera::switchCamera(int cameraId){
	this->cameraId=cameraId;
	switch(cameraId){
	case 0:
		ex=0;
		ey=0;
		ez=5;
		xzdeg=0;
		xydeg=0;
		ux=uz=0;
		uy=1;
		break;
	case 1:
		ey=0;
		ex=2;
		ez=-2.4;
		xzdeg=10;
		xydeg=-40;
		ux=uz=0;
		uy=1;
		break;
	case 2:
		ey=0;
		ex=2.1;
		ez=-2.5;
		xzdeg=30;
		xydeg=-45;
		ux=uz=0;
		uy=1;
		break;
	case 3:
		break;

	}
	updateLookAt();
}
float Camera::getLookAt(int axis){
		switch(axis)
		{
		case 1:
			return ex+sin(xzdeg/180.0*M_PI);
		case 2:
			return ey;
		case 3:
			return  ez-cos(xzdeg/180.0*M_PI);

		}

}
void Camera::rotate(float deg)
{
	xzdeg+=deg;
	updateLookAt();
}
Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::movefront(float dis)
{
	ez=ez-dis*cos(xzdeg/180.0*M_PI);
	ex=ex+dis*sin(xzdeg/180.0*M_PI);
	updateLookAt();
}
void Camera::moveright(float dis)
{
	ex=ex+dis*cos(xzdeg/180.0*M_PI);
	ez=ez+dis*sin(xzdeg/180.0*M_PI);
	updateLookAt();

}
void Camera::moveUp(float dis){
	ey+=dis;
	updateLookAt();
}
