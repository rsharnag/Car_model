/*
 * Camera.h
 *
 *  Created on: 27-Oct-2012
 *      Author: rahul
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include <cmath>

class Camera {
public:
	float ex, ey, ez;
	float lx, ly, lz;
	float ux, uy, uz;
	float xzdeg, xydeg;
	int cameraId;
	bool cameraMovementEnable;
	void switchCamera(int id);
	void setCameraPos(float x, float y, float z);
	void updateLookAt();
	float getLookAt(int axis);
	void rotate(float deg);
	void movefront(float dis);
	void moveright(float dis);
	void moveUp(float dis);
	void lookUp(float deg);
	Camera();
	virtual ~Camera();
};

#endif /* CAMERA_H_ */
