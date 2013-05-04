/*
 * KeyFrameRecPlay.cpp
 *
 *  Created on: 09-Nov-2012
 *      Author: rahul
 */

#include "KeyFrameRecPlay.h"

KeyFrameRecPlay::KeyFrameRecPlay() {
	interFrame = 24;
	cur_frame = 0;
	interFrameDefault=24;
}

KeyFrameRecPlay::~KeyFrameRecPlay() {
	// TODO Auto-generated destructor stub
}
void KeyFrameRecPlay::init(Car* car, Camera* camera,Environment* env ,char* file){
	this->car=car;
	this->cam=camera;
	this->env=env;

	char frameRate[10];
	strcpy(filename,file);
	this->fileReader.open(filename,ios::in);
	if(this->fileReader.is_open()){
		int frame=0;
		while(!this->fileReader.eof()){
			if(fileReader.getline(carData[frame],200).eof()){
				break;
			}
			strcat(carData[frame],"\n");
			if(fileReader.getline(camData[frame],100).eof()){
				break;
			}
			strcat(camData[frame],"\n");
			if(fileReader.getline(frameRate,10).eof()){
				frame++;
				break;
			}
			sscanf(frameRate,"%d",&(num_inter_frames[frame]));

			frame++;
		}
		fileReader.close();
		numKeyFrame=frame;
		nextFrame=0;
	}
	mode=NORMAL;
}
void KeyFrameRecPlay::setOutFile(char* filename){
	strcpy(this->filename,filename);
}
void KeyFrameRecPlay::nextframe() {
	static float wheelRotation ;
	static float bonnetRotation;
	static float door1Rotation ;
	static float door2Rotation ;
	static float trunkRotaion ;
	static float windSheild1 ;
	static float windsheild2 ;
	static float carxpos ;
	static float carypos ;
	static float carzpos ;
	static float vOrientation ;
	static float steerRot ;
	static float wheelYRot;
	static bool night,headlight;
	static float ex,ey,ez,xydeg,xzdeg;
	if(cur_inter_state==0){
		if(nextFrame==numKeyFrame){
			stopPlaying();
			return;
		}
		if(&nextCarFrame!=NULL){
			setFrame(&nextCarFrame,&nextEnvironFrame);
		}else{
			cerr<<"Record KeyFrames first";
		}
		interstates=num_inter_frames[nextFrame-2];
		//Interpolating
		//Car position
		carxpos=(nextCarFrame.xpos-car->xpos)*(1.0/interstates);
		carypos=(nextCarFrame.ypos-car->ypos)*(1.0/interstates);
		carzpos=(nextCarFrame.zpos-car->zpos)*(1.0/interstates);
		//Wheel Rotation
		wheelRotation=(nextCarFrame.wheelRot-car->wheelRot)*(1.0/interstates);
		wheelYRot=(nextCarFrame.wheel.yrot-car->wheel.yrot)*(1.0/interstates);

		bonnetRotation=(nextCarFrame.bRot-car->bRot)*(1.0/interstates);
		trunkRotaion=(nextCarFrame.tRot-car->tRot)*(1.0/interstates);
		windSheild1=(nextCarFrame.ws1-car->ws1)*(1.0/interstates);
		windsheild2=(nextCarFrame.ws2-car->ws2)*(1.0/interstates);
		door1Rotation=(nextCarFrame.d1Rot-car->d1Rot)*(1.0/interstates);
		door2Rotation=(nextCarFrame.d2Rot-car->d2Rot)*(1.0/interstates);

		vOrientation=(nextCarFrame.vOrientation-car->vOrientation)*(1.0/interstates);
		steerRot=(nextCarFrame.steerRot-car->steerRot)*(1.0/interstates);
		headlight=nextCarFrame.headLight;
		night=nextEnvironFrame.night;

		ex=(nextCameraFrame.ex-cam->ex)*(1.0/interstates);
		ey=(nextCameraFrame.ey-cam->ey)*(1.0/interstates);
		ez=(nextCameraFrame.ez-cam->ez)*(1.0/interstates);
		xydeg=(nextCameraFrame.xydeg-cam->xydeg)*(1.0/interstates);
		xzdeg=(nextCameraFrame.xzdeg-cam->xzdeg)*(1.0/interstates);

		//set mode
		mode=ANIMATING;
	}

	car->xpos+=carxpos;
	car->ypos+=carypos;
	car->zpos+=carzpos;
	car->wheelRot+=wheelRotation;
//	if(car->wheelRot<=-360)
//		car->wheelRot+=360;
//	else if(car->wheelRot>=360)
//		car->wheelRot=car->wheelRot-360;
	car->bRot+=bonnetRotation;
	car->tRot+=trunkRotaion;
	car->ws1+=windSheild1;
	car->ws2+=windsheild2;
	car->d1Rot+=door1Rotation;
	car->d2Rot+=door2Rotation;
	car->vOrientation+=vOrientation;
	car->steerRot+=steerRot;
	car->wheel.yrot+=wheelYRot;
	car->headLight=headlight;
	env->night=night;
	cam->ex+=ex;
	cam->ez+=ez;
	cam->ey+=ey;
	cam->xydeg+=xydeg;
	cam->xzdeg+=xzdeg;
	cam->updateLookAt();
	cur_inter_state=(cur_inter_state+1)%interstates;


}
void KeyFrameRecPlay::saveState() {

	sprintf(carData[numKeyFrame], "%.5f %.5f "
			"%.5f %.5f "
			"%.5f %.5f "
			"%.5f %.5f "
			"%.5f %.5f "
			"%.5f %.5f %.5f "
			"%i %i\n"
			, -car->wheelRot, car->bRot, car->d1Rot, car->d2Rot,
			car->tRot, car->ws1, car->ws2, car->xpos, car->ypos, car->zpos,
			car->vOrientation, car->steerRot,car->wheel.yrot,car->headLight,env->night);
	sprintf(camData[numKeyFrame], "%f %f %f "
			"%f %f \n", cam->ex, cam->ey, cam->ez, cam->xydeg, cam->xzdeg);
	//TODO sprintf(lightData[numKeyFrame], "", car->bRot);
	num_inter_frames[numKeyFrame] = interFrameDefault;
	numKeyFrame++;
	cout << "Key frame " << numKeyFrame << " saved." << endl;

}
void KeyFrameRecPlay::setInterFrames(int count) {
	num_inter_frames[nextFrame - 1] = count;
	cout << "InterFrames for Key Frame No. " << nextFrame << " updated to "
			<< count << " .\n" << endl;
}

void KeyFrameRecPlay::storeData() {
	cout<<filename<<endl;
	file.open(filename, ios::out);
	if (file.is_open()) {
		for (int i = 0; i < numKeyFrame; i++) {
			file << carData[i];
//			file << lightData[i];
			file << camData[i];
			if (i != numKeyFrame - 1)
				file << num_inter_frames[i] << endl;
		}
		file.close();
	} else {
		cerr << "File could not be opened" << endl;
	}
}

void KeyFrameRecPlay::setFrame(Car* car,Environment* env) {
	int headlight,night;
	sscanf(carData[nextFrame], "%f %f "
			"%f %f "
			"%f %f "
			"%f %f "
			"%f %f "
			"%f %f %f"
			"%d %d", &(car->wheelRot), &(car->bRot), &(car->d1Rot),
			&(car->d2Rot), &(car->tRot), &(car->ws1), &(car->ws2), &(car->xpos),
			&(car->ypos), &(car->zpos), &(car->vOrientation),&(car->wheel.yrot), &(car->steerRot),&(headlight),&(night));
	if(headlight==1){
		car->headLight=true;
	}else
		car->headLight=false;
	if(night==1)
		env->night=true;
	else
		env->night=false;
//	sscanf(lightData[nextFrame], "", &(car->bRot));
	if (car == this->car) {
		sscanf(camData[nextFrame], "%f%f%f%f%f", &(cam->ex), &(cam->ey), &(cam->ez),
				&(cam->xydeg), &(cam->xzdeg));
//		setLightState();

	} else if (car == &(this->nextCarFrame)) {
		sscanf(camData[nextFrame], "%f%f%f%f%f", &(nextCameraFrame.ex),
				&(nextCameraFrame.ey), &(nextCameraFrame.ez),
				&(nextCameraFrame.xydeg), &(nextCameraFrame.xzdeg));
	}
	cam->updateLookAt();
	nextFrame++;

}

void KeyFrameRecPlay::startRecording() {

	numKeyFrame = 0;
	mode = RECORDING;
}
void KeyFrameRecPlay::continueRecording(){
	mode=RECORDING;
}
void KeyFrameRecPlay::stopRecording() {
	storeData();
	mode = NORMAL;
}
void KeyFrameRecPlay::play() {
	mode = ANIMATING;
	cur_inter_state = 0;
	nextFrame = 0;
	setFrame(car,env);
}

void KeyFrameRecPlay::stopPlaying() {
	mode = NORMAL;
	cur_inter_state = 0;
	nextFrame = 0;
	cout<<"finished playing"<<endl;
}
