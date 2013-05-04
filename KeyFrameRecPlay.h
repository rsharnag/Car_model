/*
 * KeyFrameRecPlay.h
 *
 *  Created on: 09-Nov-2012
 *      Author: rahul
 */

#ifndef KEYFRAMERECPLAY_H_
#define KEYFRAMERECPLAY_H_
#include "Model.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class KeyFrameRecPlay {
public:
	//file pointers
	char filename[100];
	ofstream file;
	ifstream fileReader;

	Car* car; // pointer to car object
	Camera* cam; // pointer to camera object
	Environment* env;//pointer to environment object
	Car nextCarFrame; // Temporary car object to hold it for next frame while interpolation
	Camera nextCameraFrame; // Temporary camera object to hold it for next frame while interpolation
	Environment nextEnvironFrame; // Temporary Environment object to hold it for next frame while interpolation

	//Data
	char carData[100][200];
	char camData[100][100];
//	char lightData[100][100];
	int num_inter_frames[100];

	int interFrame; // number of frames to interpolate between two frames
	int interFrameDefault;// Default number of frames to interpolate
	int numKeyFrame; // number of key frames
	int nextFrame; // index to next frame
	int cur_frame;

	int interstates, cur_inter_state;

	//Setters
	void init(Car* car, Camera* camera,Environment* env, char* file);
	void setLight(bool state, GLenum Light);
	void setLightState();
	void setLight();
	void setInterFrames(int count);
	void startRecording();
	void continueRecording();
	void stopRecording();

	void setFrame(Car* car,Environment* env);
	void setOutFile(char* filename);

	//Store and get Data
	void storeData();
	void getData();
	void saveState();
	void nextframe();

	void play();
	void stopPlaying();

	enum {
		NORMAL, ANIMATING, RECORDING
	} mode;
	KeyFrameRecPlay();
	virtual ~KeyFrameRecPlay();
};

#endif /* KeyFrameRecPlay_H_ */
