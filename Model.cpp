/*
 * Car.cpp
 *
 *  Created on: 20-Oct-2012
 *      Author: rahul
 */

#include "Model.h"

Wheel::Wheel() {
		radius = 0.3;
		thick = 0.15;
		xrot = 0;
		yrot=0;
		q = gluNewQuadric();
	}
Wheel::Wheel(GLfloat x, GLfloat y, GLfloat z) {
		xpos = x;
		ypos = y;
		zpos = z;
		radius = 0.3;
		thick = 0.15;
		xrot = 0;
		yrot=0;
		q = gluNewQuadric();
	}

void Wheel::init(GLuint texBase,GLuint* wheelTexName,GLuint* wheelRimTexName) {
	this->texBase=texBase;
	glNewList(texBase+WHEEL, GL_COMPILE);
	glTranslatef(0,0,-thick/2);
	glPushMatrix();
	gluQuadricDrawStyle(q, GLU_FILL);
	gluQuadricOrientation(q, GLU_OUTSIDE);
//	glRotatef(90, 0.0, 1.0, 0.0);
	glEnable( GL_TEXTURE_2D);
	gluQuadricTexture(q, GLU_TRUE);
	glBindTexture(GL_TEXTURE_2D, *wheelTexName);
	glColor3f(1.0, 1.0, 1.0);
	gluCylinder(q, radius, radius, thick, 15, 5);
	glDisable(GL_TEXTURE_2D);
	//-----Two disks at both end of cylinder
	glPushMatrix();
	glTranslatef(0.0, 0.0, thick);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(q, GLU_TRUE);
	glBindTexture(GL_TEXTURE_2D, *wheelRimTexName);
	gluDisk(q, 0, radius, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(q, GLU_TRUE);
	glBindTexture(GL_TEXTURE_2D, *wheelRimTexName);
	gluDisk(q, 0, radius, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();
	//---------
//	glEnd();


	glEndList();
}
void Wheel::setpos(GLfloat x, GLfloat y, GLfloat z) {
	xpos = x;
	ypos = y;
	zpos = z;
}
void Wheel::rotatex(GLfloat deg) {
	xrot += deg;
//	if (xrot >= 360)
//		xrot -= 360;
//	if(xrot<=-360)
//		xrot+=360;

}
void Wheel::rotatey(GLfloat deg) {
	yrot = deg;

}
void Wheel::draw() {
	glPushMatrix();
	glTranslatef(xpos, ypos, zpos);
	glRotatef(xrot, 0.0, 0.0, 1.0);
	glCallList(texBase+WHEEL);
	glPopMatrix();

}
Environment::Environment() {
	skyRadius=45;
	xpos = 0;
	ypos = 0;
	zpos = 0;
	quadric=gluNewQuadric();
	night=false;
}
void Environment::setpos(GLfloat x, GLfloat y, GLfloat z) {
	xpos = x;
	ypos = y;
	zpos = z;
}
void Environment::init(GLuint texBase,GLuint* skyTexture,GLuint* groundTexture,GLuint* roadTexture,GLuint* nightSkyTexture) {
	this->texBase=texBase;
	glNewList(texBase+DAYSKY, GL_COMPILE);
	//	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();
	glTranslatef(0,20,0);
	glRotated(90,1,0,0);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricOrientation(quadric, GLU_INSIDE);

	//	glColor3f(1, 0.4, 0.203);
	glColor3f(1.0, 1.0, 1.0);
	//front
	glEnable( GL_TEXTURE_2D);
	gluQuadricTexture(quadric, GLU_TRUE);
	//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture(GL_TEXTURE_2D, *skyTexture);
	//	gluCylinder(quadric,40,40,30,200,200);
	gluSphere(quadric,skyRadius,100,100);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEnable( GL_TEXTURE_2D);
	//	gluQuadricTexture(quadric, GLU_TRUE);
	glBindTexture(GL_TEXTURE_2D, *roadTexture);
	glBegin(GL_QUADS);
	for(int i=0;i<20;i++){
		for(int j=0;j<100;j++)
			for(int k=0;k<100;k++){
				glTexCoord2f(j*(1.0f/100.0f),k*(1.0f/100.0));
				glNormal3f(0,1,0);
				glVertex3f(-2.0+j*(4.0/100.0),-5.0,40.0-(i+1)*4.0-k*(4.0/100.0));
				glTexCoord2f((j+1)*(1.0/100),k*(1.0f/100.0));
				glNormal3f(0,1,0);
				glVertex3f(-2.0+(j+1)*(4.0/100.0),-5.0,40.0-(i+1)*4.0-k*(4.0/100.0));
				glTexCoord2f((j+1)*(1.0/100),(k+1)*(1.0f/100.0));
				glNormal3f(0,1,0);
				glVertex3f(-2.0+(j+1)*(4.0/100.0),-5.0,40.0-(i+1)*4.0-(k+1)*(4.0/100.0));
				glTexCoord2f((j)*(1.0/100),(k+1)*(1.0f/100.0));
				glNormal3f(0,1,0);
				glVertex3f(-2.0+(j)*(4.0/100.0),-5.0,40.0-(i+1)*4.0-(k+1)*(4.0/100.0));
			}
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, *groundTexture);
	glBegin(GL_QUADS);
	for(int i=0;i<80;i++){
		for(int j=0;j<160;j++){

			glTexCoord2f(0.0,0.0);
			//			glNormal3f(0,0,-1);
			glVertex3f(2.0+(i)*0.5,-5.0,40.0-(j+1)*0.5);
			glTexCoord2f(1.0,0.0);
			//			glNormal3f(0,0,-1);
			glVertex3f(2.5+(i)*0.5,-5.0,40.0-(j+1)*0.5);
			glTexCoord2f(1,1);
			//			glNormal3f(0,0,-1);
			glVertex3f(2.5+(i)*0.5,-5.0,40.0-(j)*0.5);
			glTexCoord2f(0.0,1.0);
			//			glNormal3f(0,0,-1);
			glVertex3f(2.0+(i)*0.5,-5.0,40.0-(j)*0.5);
			glTexCoord2f(0.0,0.0);
			//				glNormal3f(0,0,-1);
			glVertex3f(-2.5-(i)*0.5,-5.0,40.0-(j+1)*0.5);
			glTexCoord2f(1.0,0.0);
			//				glNormal3f(0,0,-1);
			glVertex3f(-2.0-(i)*0.5,-5.0,40.0-(j+1)*0.5);
			glTexCoord2f(1,1);
			//				glNormal3f(0,0,-1);
			glVertex3f(-2.0-(i)*0.5,-5.0,40.0-(j)*0.5);
			glTexCoord2f(0.0,1.0);
			//				glNormal3f(0,0,-1);
			glVertex3f(-2.5-(i)*0.5,-5.0,40.0-(j)*0.5);
		}
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEndList();
	glNewList(texBase+NIGHTSKY, GL_COMPILE);
	//	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();
	glTranslatef(0,20,0);
	glRotated(90,1,0,0);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricOrientation(quadric, GLU_INSIDE);

	//	glColor3f(1, 0.4, 0.203);
	glColor3f(1.0, 1.0, 1.0);
	//front
	glEnable( GL_TEXTURE_2D);
	gluQuadricTexture(quadric, GLU_TRUE);
	//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture(GL_TEXTURE_2D, *nightSkyTexture);
	//	gluCylinder(quadric,40,40,30,200,200);
	gluSphere(quadric,40,100,100);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEnable( GL_TEXTURE_2D);
	//	gluQuadricTexture(quadric, GLU_TRUE);
	glBindTexture(GL_TEXTURE_2D, *roadTexture);
	glBegin(GL_QUADS);
	for(int i=0;i<20;i++){
		for(int j=0;j<100;j++)
			for(int k=0;k<100;k++){
				glTexCoord2f(j*(1.0f/100.0f),k*(1.0f/100.0));
				glNormal3f(0,1,0);
				glVertex3f(-2.0+j*(4.0/100.0),-5.0,40.0-(i+1)*4.0-k*(4.0/100.0));
				glTexCoord2f((j+1)*(1.0/100),k*(1.0f/100.0));
				glNormal3f(0,1,0);
				glVertex3f(-2.0+(j+1)*(4.0/100.0),-5.0,40.0-(i+1)*4.0-k*(4.0/100.0));
				glTexCoord2f((j+1)*(1.0/100),(k+1)*(1.0f/100.0));
				glNormal3f(0,1,0);
				glVertex3f(-2.0+(j+1)*(4.0/100.0),-5.0,40.0-(i+1)*4.0-(k+1)*(4.0/100.0));
				glTexCoord2f((j)*(1.0/100),(k+1)*(1.0f/100.0));
				glNormal3f(0,1,0);
				glVertex3f(-2.0+(j)*(4.0/100.0),-5.0,40.0-(i+1)*4.0-(k+1)*(4.0/100.0));
			}
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, *groundTexture);
	glBegin(GL_QUADS);
	for(int i=0;i<80;i++){
		for(int j=0;j<160;j++){

			glTexCoord2f(0.0,0.0);
			//			glNormal3f(0,0,-1);
			glVertex3f(2.0+(i)*0.5,-5.0,40.0-(j+1)*0.5);
			glTexCoord2f(1.0,0.0);
			//			glNormal3f(0,0,-1);
			glVertex3f(2.5+(i)*0.5,-5.0,40.0-(j+1)*0.5);
			glTexCoord2f(1,1);
			//			glNormal3f(0,0,-1);
			glVertex3f(2.5+(i)*0.5,-5.0,40.0-(j)*0.5);
			glTexCoord2f(0.0,1.0);
			//			glNormal3f(0,0,-1);
			glVertex3f(2.0+(i)*0.5,-5.0,40.0-(j)*0.5);
			glTexCoord2f(0.0,0.0);
			//				glNormal3f(0,0,-1);
			glVertex3f(-2.5-(i)*0.5,-5.0,40.0-(j+1)*0.5);
			glTexCoord2f(1.0,0.0);
			//				glNormal3f(0,0,-1);
			glVertex3f(-2.0-(i)*0.5,-5.0,40.0-(j+1)*0.5);
			glTexCoord2f(1,1);
			//				glNormal3f(0,0,-1);
			glVertex3f(-2.0-(i)*0.5,-5.0,40.0-(j)*0.5);
			glTexCoord2f(0.0,1.0);
			//				glNormal3f(0,0,-1);
			glVertex3f(-2.5-(i)*0.5,-5.0,40.0-(j)*0.5);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEndList();

}

void Environment::draw() {
	glPushMatrix();
	glTranslatef(xpos, ypos, zpos);
//	glTranslatef(0,3,0);
	if(night)
		glCallList(texBase+NIGHTSKY);
	else
		glCallList(texBase+DAYSKY);
	glPopMatrix();
}
Car::Car() {
	headLight=true;
	wheel=Wheel(0,0,0);
	wheelRot=0;
	bRot=0;d1Rot=0.1;d2Rot=0;tRot=0;ws1=0;ws2=0;
	xpos=ypos=zpos=0;
	ypos=-4.81;
	xori=1;yori=zori=0;
	vOrientation=0;
	steerRot=0;
	scaleFactor=0.04;
}

Car::~Car() {
	// TODO Auto-generated destructor stub
}
void Car::init(GLuint texBase,GLuint* wheelTexName,GLuint* wheelRimTexName,GLuint* engineTexName,GLuint* seatTexName,GLuint* dashBoardTexName,GLuint* speedoTexName){
	this->speedoTexName=speedoTexName;
	this->engineTexName=engineTexName;
	this->seatTexName=seatTexName;
	this->dashBoardTexName=dashBoardTexName;
	this->texBase=texBase;
	drawChasi();
	drawBonet();
	drawDoorFront();
	drawDoorBehind();
	drawTrunk();
	drawWs1();
	drawWs2();
	drawSteering();
	drawWindshield();
	drawRearWindow();
	wheel.init(texBase,wheelTexName,wheelRimTexName);
}
void Car::changeOrientation(float deg){
	vOrientation+=deg;
	if(vOrientation>360){
		vOrientation-=360.0;
	}else if(vOrientation<0){
		vOrientation+=360.0;
	}
}
void Car::moveforward(float dis=0.01){
	xori=cos(vOrientation/180.0*M_PI);
	zori=-sin(vOrientation/180.0*M_PI);
	xpos+=xori*dis;
	zpos+=zori*dis;
	wheel.rotatey(0);
	wheel.rotatex(-dis*180.0/(M_PI*wheel.radius*scaleFactor*4));
	wheelRot=wheel.xrot;
	steerRot=0;

//	vOrientation=atan2(zori,xori)*180/M_PI;
//	xpos+=dis*cos((float)(vOrientation)/180*M_PI);
//	zpos+=dis*sin((float)(vOrientation)/180*M_PI);
}
void Car::turn(bool right,float dis,float wheelRota){
	if(right){
		vOrientation-=2;
		xori=cos(vOrientation/180.0*M_PI);
		zori=-sin(vOrientation/180.0*M_PI);
		xpos+=xori*dis;
		zpos+=zori*dis;
		wheel.rotatey(wheelRota);
		wheel.rotatex(-dis*180.0/(M_PI*wheel.radius*scaleFactor*4));
		wheelRot=wheel.xrot;
		steerRot=-30;
	}else{
		vOrientation+=2;
		xori=cos(vOrientation/180.0*M_PI);
		zori=-sin(vOrientation/180.0*M_PI);
		xpos+=xori*dis;
		zpos+=zori*dis;
		wheel.rotatey(wheelRota);
		wheel.rotatex(-dis*180.0/(M_PI*wheel.radius*scaleFactor*4));
		wheelRot=wheel.xrot;
		steerRot=30;
	}
}
void Car::draw(){

	GLfloat headlight1_position[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat headlight2_position[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat spot_direction[] = {-0.984807753,-0.173648178,0};
//	GLfloat spot_direction[] = { -0.939692621, -0.342020143, 0.0 };
	glTranslatef(xpos,ypos,zpos);
	glRotatef(vOrientation,0.0,1.0,0.0);
	glScalef(scaleFactor,scaleFactor,scaleFactor);
	glRotatef(180,0.0,1.0,0.0);
	glTranslatef(-10.5,-4.0,0.0);
	glPushMatrix ();
////	drawChasi();
		glPushMatrix();
			glPushMatrix();
				glTranslatef(-0.2,1.0,2.7);
//				glRotatef(180,0,1,0);

				glLightfv(GL_LIGHT0, GL_POSITION, headlight1_position);
				glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.2,1.0,-2.7);
				glLightfv(GL_LIGHT1, GL_POSITION, headlight2_position);
				glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
			glPopMatrix();

		glPopMatrix();
		glCallList(texBase+CHASSI);
		glPushMatrix();
//			glRotatef(steerRot,8,2,-1.5);
			glTranslatef(10.0,4.0,-1.5);
			glRotatef(90,0.0,1.0,0.0);
			glRotatef(-30,1.0,0.0,0.0);
			glScalef(.20,0.20,0.10);
			glRotatef(steerRot,0.0,0.0,1.0);
			glCallList(texBase+STEERING);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(3.5,0.4,2.7);
			glScalef(4,4,4);
			glRotatef(wheel.yrot,0.0,1.0,0.0);
			glRotatef(wheelRot,0.0,0.0,1.0);
			glCallList(texBase+WHEEL);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(3.5,0.4,-2.7);
			glScalef(4,4,4);
			glRotatef(wheel.yrot,0.0,1.0,0.0);
			glRotatef(wheelRot,0.0,0.0,1.0);
			glCallList(texBase+WHEEL);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(19.5,0.4,2.7);
			glScalef(4,4,4);
			glRotatef(wheelRot,0.0,0.0,1.0);
			glCallList(texBase+WHEEL);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(19.5,0.5,-2.7);
			glScalef(4,4,4);
			glRotatef(wheelRot,0.0,0.0,1.0);
			glCallList(texBase+WHEEL);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(8.0,4.0,3.0);
			glRotatef(bRot,0.0,0.0,1.0);
			glCallList(texBase+BONET);
//			drawBonet();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(8.0,4.0,3.0);
			glRotatef(d1Rot,0.0,1.0,0.0);
			glCallList(texBase+FRONTDOOR);
			glTranslatef(0.0,ws1,0.0);
			glColor3f(0,0,0);
			glCallList(texBase+WS1);
//			drawDoorFront(ws1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(8.0,4.0,-3.0);
			glRotatef(d2Rot,0.0,1.0,0.0);
//			drawDoorBehind(ws2);
			glCallList(texBase+BACKDOOR);
			glTranslatef(0.0,ws2,0.0);
			glCallList(texBase+WS2);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(21.0,6.0,3.0);
			glRotatef(tRot,0.0,0.0,1.0);
//			drawTrunk();
			glCallList(texBase+TRUNK);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(16.3,4.0,3.0);
			glCallList(texBase+REARWINDOW);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(16.3,4.0,-3.0);
			glCallList(texBase+REARWINDOW);
		glPopMatrix();
		glPushMatrix();
//			glColor3f(1,1,1);
			glTranslatef(8.0,4.0,2.7);
			glCallList(texBase+WINDSHIELD);
		glPopMatrix();
	glPopMatrix();
	glColor3f(1,1,1);
}
void Car::drawChasi(){


	glNewList(texBase+CHASSI, GL_COMPILE);
	GLfloat chassi_ambient[] = {0.7, 0.7, 0.7, 1.0};
		GLfloat chassi_diffuse[] = {0.5, 0.0, 0.0, 1.0};
		GLfloat chassi_specular[] = {1.0, 0.8, 0.8, 1.0};
		GLfloat chassi_shininess[] = {90.0};

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, chassi_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, chassi_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, chassi_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, chassi_shininess);
	glColor3f(1,0,0);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::front_face[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
				0, 1, 12, 4,(const GLfloat *) &(Car::front_face[0][0][0]));
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_FILL,0,20,0,20);

		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
				0, 1, 12, 4,(const GLfloat *) &(Car::tyre_guard_front[0][0][0]));
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_FILL,0,20,0,20);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
				0, 1, 12, 4,(const GLfloat *) &(Car::tyre_guard_front_flat[0][0][0]));
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_FILL,0,20,0,20);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
				0, 1, 12, 4,(const GLfloat *) &(Car::tyre_guard_rear[0][0][0]));
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_FILL,0,20,0,20);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
				0, 1, 12, 4,(const GLfloat *) &(Car::tyre_guard_rear_flat[0][0][0]));
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::bonet_panels1[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::bonet_panels2[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::windshield_panels1[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);


	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::windshield_panels2[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);


	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::roof_top[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::bottom_front1[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::bottom_front2[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

/*
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::left_front_panel[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);*/

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::front_panel_left1[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);



	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::front_panel_left2[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::front_panel_left3[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);


	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::front_panel_right1[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::front_panel_right2[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::front_panel_right3[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);



	/*
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::tyre_shape_front[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::tyre_shape_middle[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::tyre_shape_end[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::tyre_shape_front_behind[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::tyre_shape_middle_behind[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::tyre_shape_end_behind[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);*/
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::	rear_panel_left1[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::	rear_panel_left2[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::	rear_panel_left3[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

//	glScalef(1,1,-1);
//	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
//			0, 1, 12, 4,(const GLfloat *) &(Car::	rear_panel_left1[0][0][0]));
//	glEnable(GL_MAP2_VERTEX_3);
//	glEnable(GL_AUTO_NORMAL);
//	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
//	glEvalMesh2(GL_FILL,0,20,0,20);
//
//	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
//			0, 1, 12, 4,(const GLfloat *) &(Car::	rear_panel_left2[0][0][0]));
//	glEnable(GL_MAP2_VERTEX_3);
//	glEnable(GL_AUTO_NORMAL);
//	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
//	glEvalMesh2(GL_FILL,0,20,0,20);
//
//	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
//			0, 1, 12, 4,(const GLfloat *) &(Car::	rear_panel_left3[0][0][0]));
//	glEnable(GL_MAP2_VERTEX_3);
//	glEnable(GL_AUTO_NORMAL);
//	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
//	glEvalMesh2(GL_FILL,0,20,0,20);
//	glScalef(1,1,-1);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::	rear_panel_right1[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::	rear_panel_right2[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::	rear_panel_right3[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);


	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::trunk_panel_behind[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::trunk_panel_front[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);


	/*glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::back_panel_front[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);*/
/*
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::back_panel_behind[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);
*/
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::window_pane_front[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::window_pane_behind[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);

/*	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glColor4f(1.0, 1.0, 1.0, 0.6);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::rear_glass_right[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);
	glDisable(GL_BLEND);

	glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glColor4f(1.0, 1.0, 1.0, 0.6);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
				0, 1, 12, 4,(const GLfloat *) &(Car::rear_glass_left[0][0][0]));
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_FILL,0,20,0,20);
		glDisable(GL_BLEND);
*/
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
		//behind headlights
		glColor3f(1,1,1);
		glVertex3f( 0.0, 0.0,  3.0);
		glVertex3f( 0.0, 2.0,  3.0);
		glVertex3f( 0.0, 2.0,  -3.0);
		glVertex3f( 0.0, 0.0,  -3.0);
		glColor3f(1,1,0);
		//Drawing seats
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,*seatTexName);
			glTexCoord2f(0,0);
			glVertex3f( 16.0, 6.0,  2.7);
			glTexCoord2f(0,1);
			glVertex3f( 16.0, 6.0,  0.3);
			glTexCoord2f(1,1);
			glVertex3f( 16.0, 2.0,  0.3);
			glTexCoord2f(1,0);
			glVertex3f( 16.0, 2.0,  2.7);

			glTexCoord2f(0,0);
			glVertex3f( 16.0, 6.0, -2.7);
			glTexCoord2f(0,1);
			glVertex3f( 16.0, 6.0, -0.3);
			glTexCoord2f(1,1);
			glVertex3f( 16.0, 2.0, -0.3);
			glTexCoord2f(1,0);
			glVertex3f( 16.0, 2.0, -2.7);

			glTexCoord2f(0,0);
			glVertex3f( 16.0, 2.0,  0.3);
			glTexCoord2f(0,1);
			glVertex3f( 16.0, 2.0,  2.7);
			glTexCoord2f(1,1);
			glVertex3f( 13.0, 2.0,  2.7);
			glTexCoord2f(1,0);
			glVertex3f( 13.0, 2.0,  0.3);

			glTexCoord2f(0,0);
			glVertex3f( 16.0, 2.0,   2.7);
			glTexCoord2f(0,1);
			glVertex3f( 13.0, 2.0,   2.7);
			glTexCoord2f(1,1);
			glVertex3f( 13.0, 0.0,   2.7);
			glTexCoord2f(1,0);
			glVertex3f( 16.0, 0.0,   2.7);

			glTexCoord2f(0,0);
			glVertex3f( 16.0, 2.0,   -2.7);
			glTexCoord2f(0,1);
			glVertex3f( 13.0, 2.0,   -2.7);
			glTexCoord2f(1,1);
			glVertex3f( 13.0, 0.0,   -2.7);
			glTexCoord2f(1,0);
			glVertex3f( 16.0, 0.0,   -2.7);

			glTexCoord2f(0,0);
			glVertex3f( 16.0, 2.0,   2.7);
			glTexCoord2f(0,1);
			glVertex3f( 16.0, 2.0,   0.3);
			glTexCoord2f(1,1);
			glVertex3f( 13.0, 2.0,   0.3);
			glTexCoord2f(1,0);
			glVertex3f( 13.0, 2.0,   2.7);

			glTexCoord2f(0,0);
			glVertex3f( 16.0, 2.0,   -2.7);
			glTexCoord2f(0,1);
			glVertex3f( 16.0, 2.0,   -0.3);
			glTexCoord2f(1,1);
			glVertex3f( 13.0, 2.0,   -0.3);
			glTexCoord2f(1,0);
			glVertex3f( 13.0, 2.0,   -2.7);

			glTexCoord2f(0,0);
			glVertex3f( 13.0, 2.0,   2.7);
			glTexCoord2f(0,1);
			glVertex3f( 13.0, 2.0,   0.3);
			glTexCoord2f(1,1);
			glVertex3f( 13.0, 0.0,   0.3);
			glTexCoord2f(1,0);
			glVertex3f( 13.0, 0.0,   2.7);


			glTexCoord2f(0,0);
			glVertex3f( 13.0, 2.0,   -2.7);
			glTexCoord2f(0,1);
			glVertex3f( 13.0, 2.0,   -0.3);
			glTexCoord2f(1,1);
			glVertex3f( 13.0, 0.0,   -0.3);
			glTexCoord2f(1,0);
			glVertex3f( 13.0, 0.0,   -2.7);
			glDisable(GL_TEXTURE_2D);
			//Drawing frontbonet partition
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,*dashBoardTexName);

			glTexCoord2f(0,0);
			glVertex3f( 8.0, 4.0, -3.0);
			glTexCoord2f(0,1);
			glVertex3f( 8.0, 4.0, 3.0);
			glTexCoord2f(1,1);
			glVertex3f( 8.0, 0.0, 3.0);
			glTexCoord2f(1,0);
			glVertex3f( 8.0, 0.0, -3.0);
			glDisable(GL_TEXTURE_2D);
			glColor3f(0.4,0.4,0.4);
			//rear bumper
			glVertex3f( 22.0, 0.0, 3.0);
			glVertex3f( 22.5, 0.0, 3.0);
			glVertex3f( 22.5, 0.0,-3.0);
			glVertex3f( 22.0, 0.0, -3.0);

			glVertex3f( 22.5, 0.0, -3.0);
			glVertex3f( 22.5, 1.0, -3.0);
			glVertex3f( 22.5, 1.0, 3.0);
			glVertex3f( 22.5, 0.0, 3.0);

			glVertex3f( 22.0, 1.0, 3.0);
			glVertex3f( 22.5, 1.0, 3.0);
			glVertex3f( 22.5, 1.0, -3.0);
			glVertex3f( 22.0, 1.0, -3.0);

			glVertex3f( 22.0, 0.0, 3.0);
			glVertex3f( 22.5, 0.0, 3.0);
			glVertex3f( 22.5, 1.0, 3.0);
	     	glVertex3f( 22.0, 1.0, 3.0);

			glVertex3f( 22.5, 0.0, -3.0);
			glVertex3f( 22.0, 0.0, -3.0);
			glVertex3f( 22.0, 1.0, -3.0);
			glVertex3f( 22.5, 1.0, -3.0);

			//front bumper
			glVertex3f( 0.0, 0.0, 3.0);
			glVertex3f( 0.0, 0.0, -3.0);
			glVertex3f( -0.7, 0.0,-3.0);
			glVertex3f( -0.7, 0.0, 3.0);

			glVertex3f( -0.7, 0.5, -3.0);
			glVertex3f( -0.7, 0.5, 3.0);
			glVertex3f( -0.7, 0.0, 3.0);
			glVertex3f( -0.7, 0.0,-3.0);

			glVertex3f( -0.7, 0.5, -3.0);
			glVertex3f( -0.7, 0.5, 3.0);
			glVertex3f( -0.2, 0.5, 3.0);
			glVertex3f( -0.2, 0.5, -3.0);

			glVertex3f( 0.0, 0.0, -3.0);
			glVertex3f( -0.7, 0.0, -3.0);
			glVertex3f( -0.7, 0.5, -3.0);
			glVertex3f( -0.0, 0.5, -3.0);

			glVertex3f( -0.0, 0.0, 3.0);
			glVertex3f( -0.7, 0.0, 3.0);
			glVertex3f( -0.7, 0.5, 3.0);
			glVertex3f( -0.0, 0.5, 3.0);
			glColor3f(1,1,1);
			//draw bonet quad for texture
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,*engineTexName);

			glTexCoord2f(0,1);
			glVertex3f(  0.0, 2.0,  3.0);

			glTexCoord2f(0,0);
			glVertex3f(  8.0, 4.0,  3.0);
			glTexCoord2f(1,0);
			glVertex3f(  8.0, 4.0, -3.0);
			glTexCoord2f(1,1);
			glVertex3f(  0.0, 2.0, -3.0);
			glDisable(GL_TEXTURE_2D);

			//draw dash board
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,*dashBoardTexName);
			glTexCoord2f(0,0);
	    	glVertex3f( 8.0, 4.0, 3.0);
	    	glTexCoord2f(0,1);
			glVertex3f( 9.0, 4.5, 3.0);
			glTexCoord2f(1,1);
			glVertex3f( 9.0, 4.5, -3.0);
			glTexCoord2f(1,0);
			glVertex3f( 8.0, 4.0, -3.0);

			glBindTexture(GL_TEXTURE_2D,*speedoTexName);

			glTexCoord2f(0,0);

			glVertex3f( 9.0, 4.5, -1.0);
			glTexCoord2f(1,0);
			glVertex3f( 9.0, 4.5, -3.0);
			glTexCoord2f(1,1);
			glVertex3f( 9.7, 3.0, -3.0);
			glTexCoord2f(0,1);
			glVertex3f( 9.7, 3.0, -1.0);

			glBindTexture(GL_TEXTURE_2D,*dashBoardTexName);
			glTexCoord2f(0,0);
			glVertex3f( 9.0, 4.5, 3.0);
			glTexCoord2f(0,1);
			glVertex3f( 9.0, 4.5, -1.0);
			glTexCoord2f(1,1);
			glVertex3f( 9.7, 3.0, -1.0);
			glTexCoord2f(1,0);
			glVertex3f( 9.7, 3.0, 3.0);

			glTexCoord2f(0,0);
			glVertex3f( 9.7, 3.0, -1.0);
			glTexCoord2f(1,0);
			glVertex3f( 9.7, 3.0, 3.0);
			glTexCoord2f(1,1);
			glVertex3f( 8.0, 2.0, 3.0);
			glTexCoord2f(0,1);
			glVertex3f( 8.0, 2.0, -1.0);


			glTexCoord2f(0,0);
			glVertex3f( 9.7, 3.0, -3.0);
			glTexCoord2f(0,1);
			glVertex3f( 9.7, 3.0, -1.0);
			glTexCoord2f(1,1);
			glVertex3f( 8.0, 2.0, -1.0);
			glTexCoord2f(1,0);
			glVertex3f( 8.0, 2.0, -3.0);

			glBindTexture(GL_TEXTURE_2D,*dashBoardTexName);
			glTexCoord2f(0,0);
			glVertex3f( 8.0, 4.0, 3.0);
			glTexCoord2f(0,1);
			glVertex3f( 8.0, 2.0, 3.0);
			glTexCoord2f(1,1);
			glVertex3f( 9.7, 3.0, 3.0);
			glTexCoord2f(1,0);
			glVertex3f( 9.0, 4.5, 3.0);

			glTexCoord2f(0,0);
			glVertex3f( 9.0, 4.5, -3.0);
			glTexCoord2f(0,1);
			glVertex3f( 9.7, 3.0, -3.0);
			glTexCoord2f(1,1);
			glVertex3f( 8.0, 2.0, -3.0);
			glTexCoord2f(1,0);
			glVertex3f( 8.0, 4.0, -3.0);
			glDisable(GL_TEXTURE_2D);
			//reflecting surface behind headlights
			chassi_shininess[0] = 150.0;
			glNormal3f(-1.0,0,0);
			glVertex3f(  0.0, 0.0,  3.0);
			glNormal3f(-1.0,0,0);
			glVertex3f(  0.0, 2.0,  3.0);
			glNormal3f(-1.0,0,0);
			glVertex3f(  0.0, 2.0, -3.0);
			glNormal3f(-1.0,0,0);
			glVertex3f(  0.0, 0.0, -3.0);

			glEnd();
			glPushMatrix();

						glTranslatef(8.0,2.8,-1.5);
						glRotatef(90,0.0,1.0,0.0);
						glRotatef(-30,1.0,0.0,0.0);

						glScalef(0.2,0.4,15.0);
						//glRotatef(wheelRot,0.0,0.0,1.0);
						glCallList(texBase+WHEEL);
					glPopMatrix();
	glPopMatrix();
	glEndList();

}
void Car::drawSteering(){
	//draw steering wheel
	glNewList(texBase+STEERING,GL_COMPILE);
	GLfloat chassi_ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat chassi_diffuse[] = {0.01, 0.01, 0.01, 1.0};
	GLfloat chassi_specular[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat chassi_shininess[] = {32.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT, chassi_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, chassi_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, chassi_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, chassi_shininess);
	glColor3f(0,0,0);
	glLineWidth(20.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0.1, 0);
	glVertex3f(0 ,2.5, 0);

	glVertex3f(0, 0.1, 0);
	glVertex3f(1.7 ,-2.5, 0);

	glVertex3f(0, 0.1, 0);
	glVertex3f(-1.7 ,-2.5, 0);
	glEnd();
	glutSolidTorus(0.5,3.0,20, 20);

				//glCallList(texBase+WHEEL);
	glEndList();
}
void Car::drawBonet(){

	glNewList(texBase+BONET, GL_COMPILE);
	GLfloat chassi_ambient[] = {0.7, 0.7, 0.7, 1.0};
	GLfloat chassi_diffuse[] = {0.5, 0.0, 0.0, 1.0};
	GLfloat chassi_specular[] = {1.0, 0.8, 0.8, 1.0};
	GLfloat chassi_shininess[] = {90.0};
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, chassi_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, chassi_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, chassi_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, chassi_shininess);
	glColor3f(1,0,0);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
				0, 1, 12, 4,(const GLfloat *) &(Car::bonet[0][0][0]));
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_FILL,0,20,0,20);
	glPopMatrix();
	glEndList();
}

void Car::drawWindshield(){
	glNewList(texBase+WINDSHIELD,GL_COMPILE);
	glColor3f(1,1,1);
	glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glColor4f(1.0, 1.0, 1.0, 0.2);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
				0, 1, 12, 4,(const GLfloat *) &(Car::windshield[0][0][0]));
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_FILL,0,20,0,20);
		glDisable(GL_BLEND);
	glEndList();
}
void Car::drawTrunk(){
	glNewList(texBase+TRUNK, GL_COMPILE);
	glColor3f(1,1,1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glColor4f(1.0, 1.0, 1.0, 0.2);
	glPushMatrix();
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::trunk_curve[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);
	glDisable(GL_BLEND);
	GLfloat chassi_ambient[] = {0.7, 0.7, 0.7, 1.0};
	GLfloat chassi_diffuse[] = {0.5, 0.0, 0.0, 1.0};
	GLfloat chassi_specular[] = {1.0, 0.8, 0.8, 1.0};
	GLfloat chassi_shininess[] = {90.0};

	glMaterialfv(GL_FRONT, GL_AMBIENT, chassi_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, chassi_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, chassi_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, chassi_shininess);
	glColor3f(1,0,0);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::trunk_bottom[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);
	glPopMatrix();
	glEndList();
}


void Car::drawDoorBehind(){
	glNewList(texBase+BACKDOOR, GL_COMPILE);
	GLfloat chassi_ambient[] = {0.7, 0.7, 0.7, 1.0};
	GLfloat chassi_diffuse[] = {0.5, 0.0, 0.0, 1.0};
	GLfloat chassi_specular[] = {1.0, 0.8, 0.8, 1.0};
	GLfloat chassi_shininess[] = {90.0};
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, chassi_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, chassi_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, chassi_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, chassi_shininess);

	glColor3f(1,0,0);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::door_behind[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);
	glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glVertex3f(0,-4,-0.0);
			glNormal3f(0,0,-1);
			glVertex3f(8,-4,-0.0);
			glNormal3f(0,0,-1);
			glVertex3f(8,0, 0.2);
			glNormal3f(0,0,-1);
			glVertex3f(0,0, 0.2);
		glEnd();
	glPopMatrix();
	glEndList();
}

void Car::drawRearWindow(){
	glNewList(texBase+REARWINDOW,GL_COMPILE);
	glColor3f(1,1,1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glColor4f(1.0, 1.0, 1.0, 0.6);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::rear_glass_left[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);
	glDisable(GL_BLEND);
	glEndList();



}


//void Car::drawRearWindowBehind(){}


void Car::drawDoorFront(){
	glNewList(texBase+FRONTDOOR, GL_COMPILE);
	glPushMatrix();
	GLfloat chassi_ambient[] = {0.7, 0.7, 0.7, 1.0};
	GLfloat chassi_diffuse[] = {0.5, 0.0, 0.0, 1.0};
	GLfloat chassi_specular[] = {1.0, 0.8, 0.8, 1.0};
	GLfloat chassi_shininess[] = {90.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT, chassi_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, chassi_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, chassi_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, chassi_shininess);
	glColor3f(1,0,0);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::door_front[0][0][0]));
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0,20,0,20);
	glBegin(GL_QUADS);
		glVertex3f(0,0,-0.2);
		glVertex3f(8,0,-0.2);
		glVertex3f(8,-4,-0.0);
		glVertex3f(0,-4,-0.0);
	glEnd();
	glPopMatrix();
	glEndList();
}
void Car::drawWs1(){
	glNewList(texBase+WS1, GL_COMPILE);
	GLfloat mat_diffuse[] = {0.6, 0.6, 0.6, 1.0};
	GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat mat_shininess[] = {10.0};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glColor4f(1.0, 1.0, 1.0, 0.4);
	glPushMatrix();
		glScalef(1.0,1.0,-1.0);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4,(const GLfloat *) &(Car::door_glass_front[0][0][0]));
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_FILL,0,20,0,20);
	glPopMatrix();
	glDisable(GL_BLEND);
	glEndList();
}
void Car::drawWs2(){
	glNewList(texBase+WS2, GL_COMPILE);
	GLfloat mat_diffuse[] = {0.6, 0.6, 0.6, 1.0};
	GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat mat_shininess[] = {10.0};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glColor4f(1.0, 1.0, 1.0, 0.4);
	glPushMatrix();
		glScalef(1.0,1.0,-1.0);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
				0, 1, 12, 4,(const GLfloat *) &(Car::door_glass_rear[0][0][0]));
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_FILL,0,20,0,20);
	glPopMatrix();
	glDisable(GL_BLEND);
	glEndList();
}
const GLfloat Car::chasis_control_points[4][4][3]={
		{
				{-1.5,1.5, -2.0},{-0.5, 1.7, -2.0},
				{0.5, 1.7, -2.0},{1.5, 1.5, -2.0}
		},
		{
				{-1.5,1.5, -1.0},{-0.5, 1.7, -1.0},
				{0.5, 1.7, -1.0},{1.5, 1.5, -1.0}
		},
		{
				{-1.5, 1.5, 1.0}, {-0.5, 1.7, 1.0},
				{0.5, 1.7, 1.0},{1.5, 1.5, 1.0}
		},
		{
				{-1.5,1.5, 2.0},{-0.5, 1.7, 2.0},
				{0.5, 1.7, 2.0},{1.5, 1.5, 2.0}
		},
};
const GLfloat Car::front_face[4][4][3]={
		{
				//{0.0,0.0, -3.0},{-0.5, 0.66, -3.0},
				//{-0.5, 1.32, -3.0},{0.0, 2.0, -3.0}
				//-2 2
				{0.0, 2.0, -3.0},{-0.5, 1.32, -2.0},
				{-0.5, 0.66, -2.0},{0.0,0.0, -2.0}


		},
		{
				//{0.0,0.0, -1.5},{-0.5, 0.66, -1.5},
				//{-0.5, 1.32, -1.5},{0.0, 2.0, -1.5}

				{0.0, 2.0, -1.0},{-0.5, 1.32, -1.0},
				{-0.5, 0.66, -1.0},{0.0,0.0, -1.0}
		},


		{
				//{0.0,0.0, 1.5}, {-0.5, 0.66, 1.5},
				//{-0.5, 1.32, 1.0},{0.0, 2.0, 1.0}

				{0.0, 2.0, 1.0},{-0.5, 1.32, 1.0},
				{-0.5, 0.66, 1.0},{0.0,0.0, 1.0}
		},
		{
				//{0.0,0.0, 3.0},{-0.5, 0.5, 3.0},
				//{-0.5, 1.0, 3.0},{0.0, 2.0, 3.0}

				{0.0, 2.0, 3.0},{-0.5, 1.0, 2.0},
				{-0.5, 0.5, 2.0},{0.0,0.0, 2.0}

		},
};


const GLfloat Car::bonet_panels1[4][4][3]={
		{

				{8.0, 4.0, -3.0},{6.0, 3.9, -3.0},
				{4.0, 3.4, -3.0},{0.0,2.0, -3.0},

		},
		{
				{8.0, 4.0, -2.9},{6.0, 3.9, -2.9},
				{4.0, 3.4, -2.9},{0.0,2.0, -2.9},
		},


		{

				{8.0, 4.0, -2.8},{6.0, 3.9, -2.8},
				{4.0, 3.4, -2.8},{0.0,2.0, -2.8},
		},
		{

				{8.0, 4.0, -2.7},{6.0, 3.9, -2.7},
				{4.0, 3.4, -2.7},{0.0,2.0, -2.7},
		},
};

const GLfloat Car::bonet_panels2[4][4][3]={
        {
                {0.0,2.0, 3.0},{4.0, 3.4, 3.0},
                {6.0, 3.9, 3.0},{8.0, 4.0, 3.0}
        },
        {
                {0.0,2.0, 2.9},{4.0, 3.4, 2.9},
                {6.0, 3.9, 2.9},{8.0, 4.0, 2.9}
        },


        {
                {0.0,2.0, 2.8}, {4.0, 3.4, 2.8},
                {6.0, 3.9, 2.8},{8.0, 4.0, 2.8}
        },
        {
                {0.0,2.0, 2.7},{4.0, 3.4, 2.7},
                {6.0, 3.9, 2.7},{8.0, 4.0, 2.7}
        },
};

const GLfloat Car::windshield[4][4][3]={
		{
				{0.0,0.0, 0.0},{1.0, 1.5, 0.0},
				{3.0, 2.5, 0.0},{4.0, 3.0, 0.0}
		},
		{
				{0.0,0.0, -1.8},{1.0, 1.5,-1.8},
				{3.0, 2.5, -1.8},{4.0, 3.0,-1.8}
		},

		{
				{0.0,0.0, -3.6}, {1.0, 1.5, -3.6},
				{3.0, 2.5, -3.6},{4.0, 3.0,-3.6}
		},
		{
				{0.0,0.0, -5.4},{1.0, 1.5, -5.4},
				{3.0, 2.5,-5.4},{4.0,3.0,-5.4}
		},
};

const GLfloat Car::windshield_panels1[4][4][3]={
		{
				{8.0,4.0, 3.0},{9.0, 5.5, 3.0},
				{11.0, 6.5, 3.0},{12.0, 7.0, 3.0}
		},
		{
				{8.0,4.0, 2.9},{9.0, 5.5, 2.9},
				{11.0, 6.5, 2.9},{12.0, 7.0, 2.9}
		},

		{
				{8.0,4.0, 2.8}, {9.0, 5.5, 2.8},
				{11.0, 6.5, 2.8},{12.0, 7.0, 2.8}
		},
		{
				{8.0,4.0, 2.7},{9.0, 5.5, 2.7},
				{11.0, 6.5, 2.7},{12.0,7.0, 2.7}
		},
};

const GLfloat Car::windshield_panels2[4][4][3]={
		{
				//{8.0,4.0, -3.0},{9.0, 5.5, -3.0},
				//{11.0, 6.5, -3.0},{12.0, 7.0, -3.0}

				{12.0, 7.0, -3.0},{11.0, 6.5, -3.0},
				{9.0, 5.5, -3.0},{8.0,4.0, -3.0}
		},
		{
				//{8.0,4.0, -2.9},{9.0, 5.5, -2.9},
				//{11.0, 6.5, -2.9},{12.0, 7.0, -2.9}

				{12.0, 7.0, -2.9},{11.0, 6.5, -2.9},
				{9.0, 5.5, -2.9},{8.0,4.0, -2.9}

		},

		{
				//{8.0,4.0, -2.8}, {9.0, 5.5, -2.8},
				//{11.0, 6.5, -2.8},{12.0, 7.0, -2.8}

				{12.0, 7.0, -2.8},{11.0, 6.5, -2.8},
				{9.0, 5.5, -2.8},{8.0,4.0, -2.8}


		},
		{
				//{8.0,4.0, -2.7},{9.0, 5.5, -2.7},
				//{11.0, 6.5, -2.7},{12.0,7.0, -2.7}

				{12.0,7.0, -2.7},{11.0, 6.5, -2.7},
				{9.0, 5.5, -2.7},{8.0,4.0, -2.7}


		},
};

const GLfloat Car::roof_top[4][4][3]={
		{
				//{12.0,7.0, -3.0},{15.0, 7.5, -3.0},
				//{18.0, 7.5, -3.0},{21.0, 6.0, -3.0}

				{21.0, 6.0, -3.0},{18.0, 7.5, -3.0},
				{15.0, 7.5, -3.0},{12.0,7.0, -3.0}
		},
		{
				//{12.0,7.0, -1.5},{15.0, 7.5, -1.5},
				//{18.0, 7.5, -1.5},{21.0, 6.0, -1.5}

				{21.0, 6.0, -1.5},{18.0, 7.5, -1.5},
				{15.0, 7.5, -1.5},{12.0,7.0, -1.5},
		},

		{
				//{12.0,7.0, 1.5}, {15.0, 7.5, 1.5},
				//{18.0,7.5, 1.5},{21.0, 6.0, 1.5}

				{21.0, 6.0, 1.5},{18.0,7.5, 1.5},
				{15.0, 7.5, 1.5},{12.0,7.0, 1.5}
		},
		{
				//{12.0,7.0,  3.0},{15.0, 7.5, 3.0},
				//{18.0, 7.5, 3.0},{21.0,6.0, 3.0}

				{21.0,6.0, 3.0},{18.0, 7.5, 3.0},
				{15.0, 7.5, 3.0},{12.0,7.0,  3.0}


		},
};


const GLfloat Car::bottom_front[4][4][3]={
		{
				{0.0,0.0, -3.0},{1.0, 0.2, -3.0},
				{2.0, 0.0, -3.0},{20.0, 0.0, -3.0}
		},
		{
				{0.0,0.0, -1.5},{1.0, 0.2, -1.5},
				{2.0, 0.0, -1.5},{20.0, 0.0, -1.5}
		},

		{
				{0.0,0.0, 1.5}, {1.0, 0.2, 1.5},
				{2.0, 0.0, 1.5},{20.0, 0.0, 1.5}
		},
		{
				{0.0,0.0,  3.0},{1.0, 0.2, 3.0},
				{2.0, 0.0, 3.0},{20.0, 0.0, 3.0}
		},
};



const GLfloat Car::left_front_panel[4][4][3]={
		{
				{0.0,2.0, -3.0},{4.0, 3.4, -3.0},
				{6.0, 3.9, -3.0},{8.0, 4.0, -3.0}
		},
		{
				{-0.5, 1.32, -3.0},{4.0, 2.5, -3.0},
				{6.0, 3.0, -3.0},{8.0, 3.5, -3.0}
		},

		{
				{-0.5,0.66, -3.0}, {4.0, 1.5, -3.0},
				{6.0, 2.0, -3.0},{8.0, 3.0, -3.0}
		},
		{
				{0.0,0.0, -3.0},{3.5, 0.0, -3.0},
				{3.5, 0.0, -3.0},{8.0, 0.0, -3.0}
		},
};

const GLfloat Car::front_panel_left1[4][4][3]={
		{
				//{0.0,2.0, 3.0},{4.0, 3.4, 3.0},
				//{6.0, 3.9, 3.0},{8.0, 4.0, 3.0}

				{2.0, 2.6, 3.0},{1.5, 2.5, 3.0},
				{1.0, 2.4, 3.0},{0.0,2.0, 3.0}

		},
		{
				//{-0.5, 1.32, 3.0},{4.0, 2.5, 3.0},
				//{6.0, 3.0, 3.0},{8.0, 3.5, 3.0}


				{2.0, 2.6, 3.0},{1.5, 2.5, 3.0},
				{1.0, 2.5, 3.0},{-0.5, 1.32, 3.0}
		},

		{
				//{-0.5,0.66, 3.0}, {4.0, 1.5, 3.0},
				//{6.0, 2.0, 3.0},{8.0, 3.0, 3.0}


				{2.0, 1.5, 3.0},{1.5, 1.0, 3.0},
				{1.0, 1.5, 3.0},{-0.5,0.66, 3.0}

		},
		{
				//{0.0,0.0, 3.0},{3.5, 0.0, 3.0},
				//{3.5, 0.0, 3.0},{8.0, 0.0, 3.0}

				{2.0, 0.0, 3.0},{1.5, 0.0, 3.0},
				{1.0, 0.0, 3.0},{0.0,0.0, 3.0}

		},
};

const GLfloat Car::front_panel_left2[4][4][3]={
		{
				//{0.0,2.0, 3.0},{4.0, 3.4, 3.0},
				//{6.0, 3.9, 3.0},{8.0, 4.0, 3.0}

				{5.0,3.5, 3.0},{4.0, 3.2, 3.0},
				{3.0, 3.0, 3.0},{2.0, 2.6, 3.0}

		},
		{
				//{-0.5, 1.32, 3.0},{4.0, 2.5, 3.0},
				//{6.0, 3.0, 3.0},{8.0, 3.5, 3.0}

				{5.0, 2.2, 3.0},{4.7, 2.2, 3.0},
				{2.6, 2.2, 3.0},{2.0,2.2, 3.0}
		},

		{
				//{-0.5,0.66, 3.0}, {4.0, 1.5, 3.0},
				//{6.0, 2.0, 3.0},{8.0, 3.0, 3.0}


				{5.0, 2.2, 3.0},{4.7, 2.2, 3.0},
				{2.6, 2.2, 3.0},{2.0,2.2, 3.0}

		},
		{
				//{0.0,0.0, 3.0},{3.5, 0.0, 3.0},
				//{3.5, 0.0, 3.0},{8.0, 0.0, 3.0}

				{5.0, 0.0, 3.0},{4.7, 2.2, 3.0},
				{2.6, 2.2, 3.0},{2.0,0.0, 3.0}

		},
};


const GLfloat Car::front_panel_left3[4][4][3]={
		{
				//{0.0,2.0, 3.0},{4.0, 3.4, 3.0},
				//{6.0, 3.9, 3.0},{8.0, 4.0, 3.0}

				{8.0, 4.0, 3.0},{7.5, 4.0, 3.0},
				{7.0, 4.0, 3.0},{5.0,3.5, 3.0}

		},
		{
				//{-0.5, 1.32, 3.0},{4.0, 2.5, 3.0},
				//{6.0, 3.0, 3.0},{8.0, 3.5, 3.0}


				{8.0, 3.0, 3.7},{7.5, 2.5, 3.7},
				{7.0, 2.5, 3.7},{5.0, 2.0, 3.0}
		},

		{
				//{-0.5,0.66, 3.0}, {4.0, 1.5, 3.0},
				//{6.0, 2.0, 3.0},{8.0, 3.0, 3.0}


				{8.0, 1.5, 3.7},{7.5, 1.0, 3.7},
				{7.0, 1.5, 3.4},{5.0,0.66, 3.0}

		},
		{
				//{0.0,0.0, 3.0},{3.5, 0.0, 3.0},
				//{3.5, 0.0, 3.0},{8.0, 0.0, 3.0}

				{8.0, 0.0, 3.0},{7.5, 0.0, 3.0},
				{7.0, 0.0, 3.0},{5.0,0.0, 3.0}

		},
};


const GLfloat Car::front_panel_right1[4][4][3]={
		{
				{0.0,2.0, -3.0},{1.0, 2.4, -3.0},
				{1.5, 2.5, -3.0},{2.0, 2.6, -3.0}

		},
		{

				{-0.5, 1.32, -3.0},{1.0, 2.5, -3.0},
				{1.5, 2.5, -3.0},{2.0, 2.6, -3.0}
		},

		{
				{-0.5,0.66, -3.0},{1.0, 1.5, -3.0},
				{1.5, 1.0, -3.0},{2.0, 1.5, -3.0}


		},
		{
				{0.0,0.0, -3.0},{1.0, 0.0, -3.0},
				{1.5, 0.0, -3.0},{2.0, 0.0, -3.0}


		},
};

const GLfloat Car::front_panel_right2[4][4][3]={
		{

				{2.0, 2.6, -3.0},{3.0, 3.0, -3.0},
				{4.0, 3.2, -3.0},{5.0,3.5, -3.0}
		},
		{
				//{-0.5, 1.32, 3.0},{4.0, 2.5, 3.0},
				//{6.0, 3.0, 3.0},{8.0, 3.5, 3.0}

				//,{2.0, 2.6, 3.0}{3.0, 3.0, 3.0}
				//,{4.0, 3.2, 3.0},{5.0,3.5, 3.0}
//
//				{2.0,0.0, 3.0},{2.6, 2.2, 3.0},
//				{4.7, 2.2, 3.0},{5.0, 0.0, 3.0}
//

				{2.0, 2.6, -3.0},{3.0, 3.0, -3.0},
				{4.0, 3.2, -3.0},{5.0, 3.5, -3.0}

		},

		{
				//{-0.5,0.66, 3.0}, {4.0, 1.5, 3.0},
				//{6.0, 2.0, 3.0},{8.0, 3.0, 3.0}


				{2.0,2.6, -3.0},{3.0, 3.0, -3.0},
				{4.0, 3.2, -3.0},{5.0, 3.5, -3.0}


		},
		{
				//{0.0,0.0, 3.0},{3.5, 0.0, 3.0},
				//{3.5, 0.0, 3.0},{8.0, 0.0, 3.0}

				{2.0,0.0, -3.0},{2.6, 2.2, -3.0},
				{4.7, 2.2, -3.0},{5.0, 0.0, -3.0}


		},
};


const GLfloat Car::front_panel_right3[4][4][3]={
		{
				//{0.0,2.0, 3.0},{4.0, 3.4, 3.0},
				//{6.0, 3.9, 3.0},{8.0, 4.0, 3.0}

				{5.0,3.5, -3.0},{7.0, 4.0, -3.0},
				{7.5, 4.0, -3.0},{8.0, 4.0, -3.0}

		},
		{
				//{-0.5, 1.32, 3.0},{4.0, 2.5, 3.0},
				//{6.0, 3.0, 3.0},{8.0, 3.5, 3.0}

				{5.0, 2.0, -3.0},{7.0, 2.5, -3.0},
				{7.5, 2.5, -3.6},{8.0, 3.0, -3.7}

		},

		{
				//{-0.5,0.66, 3.0}, {4.0, 1.5, 3.0},
				//{6.0, 2.0, 3.0},{8.0, 3.0, 3.0}

				{5.0,0.66, -3.0},{7.0, 1.5, -3.0},
				{7.5, 1.0, -3.6},{8.0, 1.5, -3.7}


		},
		{
				//{0.0,0.0, 3.0},{3.5, 0.0, 3.0},
				//{3.5, 0.0, 3.0},{8.0, 0.0, 3.0}

				{5.0,0.0, -3.0},{7.0, 0.0, -3.0},
				{7.5, 0.0, -3.0},{8.0, 0.0, -3.0}
		},
};

const GLfloat Car::trunk_panel_front[4][4][3]={
        {
                        {22.0, 3.0, -3.0},{21.66, 4.5, -3.0},
                        {21.33, 5.0, -3.0},{21.0, 6.0, -3.0}
                },
                {
                        {22.0, 3.0,-2.9},{21.66,4.5, -2.9},
                        {21.33, 5.0, -2.9},{21.0, 6.0, -2.9}
                },

                {
                        {22.0, 3.0, -2.8},{21.66, 4.5, -2.8},
                        {21.33, 5.0, -2.8},{21.0, 6.0, -2.8}
                },
                {
                        {22.0, 3.0,-2.7},{21.66, 4.5, -2.7},
                        {21.33, 5.0, -2.7},{21.0, 6.0, -2.7}
                },
        };
const GLfloat Car::trunk_panel_behind[4][4][3]={
        {
                {21.0, 6.0, 3.0},{21.33, 5.0, 3.0},
                {21.66, 4.5, 3.0},{22.0, 3.0, 3.0}
        },
        {
                {21.0, 6.0, 2.9},{21.33, 5.0, 2.9},
                {21.66,4.5, 2.9},{22.0, 3.0,2.9}
        },

        {
                {21.0, 6.0, 2.8}, {21.33, 5.0, 2.8},
                {21.66, 4.5, 2.8},{22.0, 3.0, 2.8}
        },
        {
                {21.0, 6.0, 2.7},{21.33, 5.0, 2.7},
                {21.66, 4.5, 2.7},{22.0, 3.0,2.7}
        },
};


const GLfloat Car::number_plate[4][4][3]={
		{
						{0.0, 0.0, 3.0},{0.0, 0.0, 1.5},
						{0.0, 0.0, 1.5},{8.0, 0.0, 1.5}
				},
				{
						{0.0,-0.33, 3.0},{6.33,-0.33, 3.0},
						{7.166,-0.33, 3.0},{8.0, -0.33, 3.0}
				},

				{
						{5.5,-0.66, 3.0}, {6.33,-0.66, 3.0},
						{7.0, -0.66, 3.0},{8.0, -0.66, 3.0}
				},
				{
						{5.5,-1.0, 3.0},{6.33, -1.0, 3.0},
						{7.166, -1.0, 3.0},{8.0, -1.0, 3.0}
				},
		};

const GLfloat Car::back_panel_front[4][4][3] = {
		{
				//{16.0, 4.0, 3.0},{18.0, 3.8, 3.0},
				//{20.0, 3.7, 3.0},{22.0, 3.0, 3.0}


				{22.0, 3.0, 3.0},{20.0, 3.7, 3.0},
				{18.0, 3.8, 3.0},{16.0, 4.0, 3.0}
		},
		{
				//{16.0, 3.0, 3.0},{18.0, 3.0, 3.0},
				//{20.0, 2.8,3.0},{22.0, 2.0,3.0}


				{22.0, 2.0,3.0},{20.0, 2.8,3.0},
				{18.0, 3.0, 3.0},{16.0, 3.0, 3.0}
		},

		{
				//{16.0, 1.0, 3.0}, {18.0, 1.0, 3.0},
				//{20.0, 1.0, 3.0},{22.0, 1.0, 3.0}

				{22.0, 1.0, 3.0},{20.0, 1.0, 3.0},
				{18.0, 1.0, 3.0},{16.0, 1.0, 3.0}
		},
		{
				//{16.0, 0.0, 3.0},{18.0, 0.0, 3.0},
				//{20.0, 0.0, 3.0},{22.0, 0.0,3.0}

				{22.0, 0.0,3.0},{20.0, 0.0, 3.0},
				{18.0, 0.0, 3.0},{16.0, 0.0, 3.0}



		},
};

const GLfloat Car::rear_panel_left1[4][4][3] = {
		{
				//{16.0, 4.0, 3.0},{18.0, 3.8, 3.0},
				//{20.0, 3.7, 3.0},{22.0, 3.0, 3.0}


				{18.0, 3.7, 3.0},{17.5, 3.8, 3.0},
				{17.0, 3.9, 3.0},{16.0, 4.0, 3.0}
		},
		{
				//{16.0, 3.0, 3.0},{18.0, 3.0, 3.0},
				//{20.0, 2.8,3.0},{22.0, 2.0,3.0}


				{18.0, 2.0,3.0},{17.5, 2.8,3.4},
				{17.0, 3.0, 3.4},{16.0, 3.0, 3.4}
		},

		{
				//{16.0, 1.0, 3.0}, {18.0, 1.0, 3.0},
				//{20.0, 1.0, 3.0},{22.0, 1.0, 3.0}

				{18.0, 1.0, 3.0},{17.5, 1.0, 3.4},
				{17.0, 1.0, 3.4},{16.0, 1.0, 3.4}
		},
		{
				//{16.0, 0.0, 3.0},{18.0, 0.0, 3.0},
				//{20.0, 0.0, 3.0},{22.0, 0.0,3.0}

				{18.0, 0.0,3.0},{17.0, 0.0, 3.0},
				{16.5, 0.0, 3.0},{16.0, 0.0, 3.0}



		},
};


const GLfloat Car::rear_panel_left2[4][4][3] = {
		{
				//{16.0, 4.0, 3.0},{18.0, 3.8, 3.0},
				//{20.0, 3.7, 3.0},{22.0, 3.0, 3.0}


				{21.0, 3.16, 3.0},{20.0, 3.4, 3.0},
				{19.0, 3.5, 3.0},{18.0, 3.7, 3.0}
		},
		{
				//{16.0, 3.0, 3.0},{18.0, 3.0, 3.0},
				//{20.0, 2.8,3.0},{22.0, 2.0,3.0}


				{21.0, 3.16,3.0},{20.0, 3.4,3.0},
				{19.0, 3.0, 3.0},{18.0, 3.0, 3.0}
		},

		{
				//{16.0, 1.0, 3.0}, {18.0, 1.0, 3.0},
				//{20.0, 1.0, 3.0},{22.0, 1.0, 3.0}

				{21.0, 2.16, 3.0},{20.0, 3.4, 3.0},
				{19.0, 2.4, 3.0},{18.0, 2.0, 3.0}
		},
		{
				//{16.0, 0.0, 3.0},{18.0, 0.0, 3.0},
				//{20.0, 0.0, 3.0},{22.0, 0.0,3.0}

				{21.0, 0.0,3.0},{20.7, 2.3, 3.0},
				{18.5, 2.3, 3.0},{18.0, 0.0, 3.0}



		},
};
const GLfloat Car::rear_panel_left3[4][4][3] = {
		{
				//{16.0, 4.0, 3.0},{18.0, 3.8, 3.0},
				//{20.0, 3.7, 3.0},{22.0, 3.0, 3.0}


				{22.0, 3.0, 3.0},{21.66, 3.05, 3.0},
				{21.33, 3.10, 3.0},{21.0, 3.16, 3.0}
		},
		{
				//{16.0, 3.0, 3.0},{18.0, 3.0, 3.0},
				//{20.0, 2.8,3.0},{22.0, 2.0,3.0}


				{22.0, 2.0,3.0},{21.66, 2.05,3.0},
				{21.33, 2.1, 3.0},{21.0, 2.16, 3.0}
		},

		{
				//{16.0, 1.0, 3.0}, {18.0, 1.0, 3.0},
				//{20.0, 1.0, 3.0},{22.0, 1.0, 3.0}

				{22.0, 1.0, 3.0},{21.66, 1.05, 3.0},
				{21.33, 1.1, 3.0},{21.0, 1.16, 3.0}
		},
		{
				//{16.0, 0.0, 3.0},{18.0, 0.0, 3.0},
				//{20.0, 0.0, 3.0},{22.0, 0.0,3.0}

				{22.0, 0.0,3.0},{21.66, 0.0, 3.0},
				{21.33, 0.0, 3.0},{21.0, 0.0, 3.0}



		},
};

const GLfloat Car::rear_panel_right1[4][4][3] = {
		{
				//{16.0, 4.0, 3.0},{18.0, 3.8, 3.0},
				//{20.0, 3.7, 3.0},{22.0, 3.0, 3.0}



				{16.0, 4.0, -3.0},{17.0, 3.9, -3.0},
				{17.5, 3.8, -3.0},{18.0, 3.7, -3.0}
		},
		{
				//{16.0, 3.0, 3.0},{18.0, 3.0, 3.0},
				//{20.0, 2.8,3.0},{22.0, 2.0,3.0}


				{16.0, 3.0, -3.4},{17.0, 3.0, -3.4},
				{17.5, 2.8,-3.4},{18.0, 2.0,-3.0}
		},

		{
				//{16.0, 1.0, 3.0}, {18.0, 1.0, 3.0},
				//{20.0, 1.0, 3.0},{22.0, 1.0, 3.0}



				{16.0, 1.0, -3.4},{17.0, 1.0, -3.4},
				{17.5, 1.0, -3.4},{18.0, 1.0, -3.0}
		},
		{
				//{16.0, 0.0, 3.0},{18.0, 0.0, 3.0},
				//{20.0, 0.0, 3.0},{22.0, 0.0,3.0}

				{16.0, 0.0, -3.0},{16.5, 0.0, -3.0},
				{17.0, 0.0, -3.0},{18.0, 0.0,-3.0}




		},
};


const GLfloat Car::rear_panel_right2[4][4][3] = {
		{
				//{16.0, 4.0, 3.0},{18.0, 3.8, 3.0},
				//{20.0, 3.7, 3.0},{22.0, 3.0, 3.0}


				{18.0, 3.7, -3.0},{19.0, 3.5, -3.0},
				{20.0, 3.4, -3.0},{21.0, 3.16, -3.0}
		},
		{
				//{16.0, 3.0, 3.0},{18.0, 3.0, 3.0},
				//{20.0, 2.8,3.0},{22.0, 2.0,3.0}


				{18.0, 3.0, -3.0},{19.0, 3.0, -3.0},
				{20.0, 3.4,-3.0},{21.0, 3.16,-3.0}

		},

		{
				//{16.0, 1.0, 3.0}, {18.0, 1.0, 3.0},
				//{20.0, 1.0, 3.0},{22.0, 1.0, 3.0}

				{18.0, 2.0, -3.0},{19.0, 2.4, -3.0},
				{20.0, 3.4, -3.0},{21.0, 2.16, -3.0}

		},
		{
				//{16.0, 0.0, 3.0},{18.0, 0.0, 3.0},
				//{20.0, 0.0, 3.0},{22.0, 0.0,3.0}
				//{21.0, 0.0,3.0},{20.7, 2.3, 3.0},
				//{18.5, 2.3, 3.0},{18.0, 0.0, 3.0}

				{18.0, 0.0, -3.0},{18.7, 2.3, -3.0},
				{20.7, 2.3, -3.0},{21.0, 0.0,-3.0}




		},
};
const GLfloat Car::rear_panel_right3[4][4][3] = {
		{
				//{16.0, 4.0, 3.0},{18.0, 3.8, 3.0},
				//{20.0, 3.7, 3.0},{22.0, 3.0, 3.0}

				{21.0, 3.16, -3.0},{21.33, 3.10, -3.0},
				{21.66, 3.05, -3.0},{22.0, 3.0, -3.0}
		},
		{
				//{16.0, 3.0, 3.0},{18.0, 3.0, 3.0},
				//{20.0, 2.8,3.0},{22.0, 2.0,3.0}

				{21.0, 2.16, -3.0},{21.33, 2.1, -3.0},
				{21.66, 2.05,-3.0},{22.0, 2.0,-3.0}

		},

		{
				//{16.0, 1.0, 3.0}, {18.0, 1.0, 3.0},
				//{20.0, 1.0, 3.0},{22.0, 1.0, 3.0}

				{21.0, 1.16, -3.0},{21.33, 1.1, -3.0},
				{21.66, 1.05, -3.0},{22.0, 1.0, -3.0}

		},
		{
				//{16.0, 0.0, 3.0},{18.0, 0.0, 3.0},
				//{20.0, 0.0, 3.0},{22.0, 0.0,3.0}
				{21.0, 0.0, -3.0},{21.33, 0.0, -3.0},
				{21.66, 0.0, -3.0},{22.0, 0.0,-3.0}




		},
};


const GLfloat Car::back_panel_behind[4][4][3] = {
		{
				{16.0, 4.0, -3.0},{18.0, 3.8, -3.0},
				{20.0, 3.7, -3.0},{22.0, 3.0, -3.0}
		},
		{
				{16.0, 3.0, -3.0},{18.0, 3.0, -3.0},
				{20.0, 2.8,-3.0},{22.0, 2.0,-3.0}
		},

		{
				{16.0, 1.0, -3.0}, {18.0, 1.0, -3.0},
				{20.0, 1.0, -3.0},{22.0, 1.0, -3.0}
		},
		{
				{16.0, 0.0, -3.0},{18.0, 0.0, -3.0},
				{20.0, 0.0, -3.0},{22.0, 0.0,-3.0}
		},
};

const GLfloat Car::bonet[4][4][3]={
		{
				{-8.0,-2.0, 0.0},{-4.0,-0.6, 0.0},
				{-2.0, -0.1, 0.0},{0.0,0.0, 0.0}
		},
		{
				{-8.0, -2.0, -2.0},{-4.0,-0.6, -2.0},
				{-2.0, -0.1,-2.0},{0.0,0.0, -2.0}
		},


		{

				{-8.0, -2.0, -4.0},{-4.0,-0.6, -4.0},
				{-2.0, -0.1, -4.0},{0.0,0.0, -4.0}
		},
		{
				//{0.0,0.0, -6.0},{-2.0, -0.1, -6.0},
				//{-4.0,-0.6, -6.0},{-8.0, -2.0, -6.0}

				{-8.0, -2.0, -6.0},{-4.0,-0.6, -6.0},
				{-2.0, -0.1, -6.0},{0.0,0.0, -6.0}
		},
};

const GLfloat Car::trunk_curve[4][4][3]={
		{
				{0.0, 0.0, 0.0},{0.33, -1.0, 0.0},
				{0.66, -1.5, 0.0},{1.0,-3.0, 0.0}
		},
		{
				{0.0, 0.0, -2.0},{0.33, -1.0, -2.0},
				{0.66, -1.5, -2.0},{1.0,-3.0,-2.0}
		},

		{
				{0.0, 0.0, -4.0}, {0.33, -1.0, -4.0},
				{0.66, -1.5, -4.0},{1.0,-3.0, -4.0}
		},
		{
				{0.0, 0.0, -6.0},{0.33, -1.0, -6.0},
				{0.66, -1.5, -6.0},{1.0,-3.0,-6.0}
		},
};

const GLfloat Car::trunk_bottom[4][4][3]={
		{
				{1.0, -3.0, 0.0},{1.0, -4.0, 0.0},
				{1.0, -4.5, 0.0},{1.0,-5.0, 0.0}
		},
		{
				{1.0, -3.0, -2.0},{1.0, -4.0, -2.0},
				{1.0, -4.5, -2.0},{1.0,-5.0,-2.0}
		},

		{
				{1.0, -3.0, -4.0}, {1.0, -4.0, -4.0},
				{1.0, -4.5, -4.0},{1.0,-5.0, -4.0}
		},
		{
				{1.0, -3.0, -6.0},{1.0, -4.0, -6.0},
				{1.0, -4.5, -6.0},{1.0,-5.0,-6.0}
		},
};


const GLfloat Car::window_pane_front[4][4][3]={
		{
				//{16.0, 7.4, 3.0},{16.1, 7.4, 3.0},
				//{16.2, 7.4, 3.0},{16.3, 7.4, 3.0}

				{16.3, 7.3, 3.0},{16.2, 7.3, 3.0},
				{16.1, 7.3, 3.0},{16.0, 7.3, 3.0},
		},
		{
				//{16.0,  6.0,  3.0},{16.1, 6.0, 3.0},
				//{16.2,  6.0,  3.0},{16.3,6.0, 3.0}

				{16.3,6.0, 3.0},{16.2,  6.0,  3.0},
				{16.1, 6.0, 3.0},{16.0,  6.0,  3.0}
		},

		{
				//{16.0, 5.0, 3.0}, {16.1, 5.0, 3.0},
				//{16.2, 5.0, 3.0},{16.3, 5.0, 3.0}

				{16.3, 5.0, 3.0},{16.2, 5.0, 3.0},
				{16.1, 5.0, 3.0},{16.0, 5.0, 3.0}

		},
		{
				//{16.0,  4.0, 3.0},{16.1, 4.0, 3.0},
				//{16.2,  4.0, 3.0},{16.3,4.0,3.0}

				{16.3,4.0,3.0},{16.2,  4.0, 3.0},
				{16.1, 4.0, 3.0},{16.0,  4.0, 3.0}

		},
};

const GLfloat Car::window_pane_behind[4][4][3]={
	{
			{16.0, 7.3, -3.0},{16.1, 7.3, -3.0},
			{16.2, 7.3, -3.0},{16.3, 7.3, -3.0}
	},
	{
			{16.0,  6.0,  -3.0},{16.1, 6.0, -3.0},
			{16.2,  6.0,  -3.0},{16.3,6.0, -3.0}
	},

	{
			{16.0, 5.0, -3.0}, {16.1, 5.0, -3.0},
			{16.2, 5.0, -3.0},{16.3, 5.0, -3.0}
	},
	{
			{16.0,  4.0, -3.0},{16.1, 4.0, -3.0},
			{16.2,  4.0, -3.0},{16.3,4.0,-3.0}
	},
};
const GLfloat Car::door_behind[4][4][3]={
	{
			{0.0, 0.0, 0.0},{2.0, 0.3, 0.0},
			{6.0, 0.5, 0.0},{8.0, 0.0, 0.0}
	},
	{
			{0.0, -1.0, -0.6},{2.0, -1.3, -0.6},
			{6.0,-1.5, -0.6},{8.0,-1.0, 0.0}
	},

	{
			{0.0, -2.0, -0.6}, {2.0, -2.3, -0.6},
			{6.0, -2.5, -0.6},{8.0, -2.0, -0.6}
	},
	{
			{0.0, -4.0, 0.0},{2.0, -4.0, 0.0},
			{6.0,  -4.0, 0.0},{8.0, -4.0, 0.0}
	},
};


const GLfloat Car::door_front[4][4][3]={
	{
			//{0.0, 0.0, 0.2},{2.0, 0.3, 0.2},
			//{6.0, 0.5, 0.2},{8.0, 0.0, 0.2}

			{8.0, 0.0, 0.0},{6.0, 0.5, 0.0},
			{2.0, 0.3, 0.0},{0.0, 0.0, 0.0}
	},
	{
			//{0.0, -1.0, 0.3},{2.0, -1.3, 0.3},
			//{6.0,-1.5, 0.3},{8.0,-1.0, 0.3}

			{8.0,-1.0, 0.0},{6.0,-1.5, 0.6},
			{2.0, -1.3, 0.6},{0.0, -1.0, 0.6},

	},

	{
			//{0.0, -2.0, 0.3}, {2.0, -2.3, 0.3},
			//{6.0, -2.5, 0.3},{8.0, -2.0, 0.3}

			{8.0, -2.0, 0.6},{6.0, -2.5, 0.6},
			{2.0, -2.3, 0.6},{0.0, -2.0, 0.6}
	},
	{
			//{0.0, -4.0, 0.0},{2.0, -4.0, 0.0},
			//{6.0,  -4.0, 0.0},{8.0, -4.0, 0.0}
			{8.0, -4.0, 0.0},{6.0,  -4.0, 0.0},
			{2.0, -4.0, 0.0},{0.0, -4.0, 0.0}

	},
};


const GLfloat Car::door_glass_rear[4][4][3]={
	{
			{4.0, 3.0, 0.0},{7.0, 3.4, 0.0},
			{7.5, 3.4, 0.2},{8.0, 3.3, 0.0}
	},
	{
			{2.0, 2.1, 0.0},{4.0, 3.0, 0.0},
			{6.0, 3.5, 0.0},{8.0,3.0, 0.0}
	},

	{
			{1.0, 1.2, 0.0}, {3.0, -2.0, 0.0},
			{6.0, 2.5, 0.0},{8.0, 2.5, 0.0}
	},
	{
			{0.0, 0.0, 0.0},{2.0, 0.0, 0.0},
			{6.0,  0.0, 0.0},{8.0, 0.0, 0.0}
	},
};

const GLfloat Car::door_glass_front[4][4][3]={
	{
			{8.0, 3.3, 0.0},{7.5, 3.4, 0.2},
			{7.0, 3.4, 0.0},{4.0, 3.0, 0.0}

	},
	{
			{8.0,3.0, 0.0},{6.0, 3.5, 0.0},
			{4.0, 3.0, 0.0},{2.0, 2.1, 0.0}
	},

	{
			{8.0, 2.5, 0.0},{6.0, 2.5, 0.0},
			{3.0, -2.0, 0.0},{1.0, 1.2, 0.0}

	},
	{
			{8.0, 0.0, 0.0},{6.0,  0.0, 0.0},
			{2.0, 0.0, 0.0},{0.0, 0.0, 0.0}

	},
};

const GLfloat Car::rear_glass_left[4][4][3]={
	{
			{0.0, 0.0, 0.0},{1.7, -0.3, 0.0},
			{4.7, -0.84, 0.0},{5.7, -1.0, 0.0}

	},
	{
			{0.0,1.3, 0.0},{1.8, 1.0, 0.0},
			{4.3, 0.4, 0.0},{5.4, 0.0, 0.0}
	},

	{
			{0.0, 2.3, 0.0},{1.9, 2.3, 0.0},
			{4.0, 1.6, 0.0},{5.2, 1.0, 0.0}
	},
	{
			{0.0, 3.3, 0.0},{2.0,  3.2, 0.0},
			{3.7, 2.60, 0.0},{4.7, 2.0, 0.0}

	},
};


const GLfloat Car::rear_glass_right[4][4][3]={
{
		{0.0, 0.0, 0.0},{1.7, -0.3, 0.0},
		{4.7, -0.84, 0.0},{5.7, -1.0, 0.0}

},
{
		{0.0,1.3, 0.0},{1.8, 1.0, 0.0},
		{4.3, 0.4, 0.0},{5.4, 0.0, 0.0}
},

{
		{0.0, 2.3, 0.0},{1.9, 2.3, 0.0},
		{4.0, 1.6, 0.0},{5.2, 1.0, 0.0}
},
{
		{0.0, 3.3, 0.0},{2.0,  3.2, 0.0},
		{3.7, 2.60, 0.0},{4.7, 2.0, 0.0}

},
};
const GLfloat Car::left_back_panel[4][4][3]={
		{
				//{0.0,2.0, 3.0},{4.0, 3.4, 3.0},
				//{6.0, 3.9, 3.0},{8.0, 4.0, 3.0}

				{8.0, 4.0, 3.0},{6.0, 3.9, 3.0},
				{4.0, 3.4, 3.0},{0.0,2.0, 3.0}

		},
		{
				//{-0.5, 1.32, 3.0},{4.0, 2.5, 3.0},
				//{6.0, 3.0, 3.0},{8.0, 3.5, 3.0}


				{8.0, 3.5, 3.0},{6.0, 3.0, 3.0},
				{4.0, 2.5, 3.0},{-0.5, 1.32, 3.0}
		},

		{
				//{-0.5,0.66, 3.0}, {4.0, 1.5, 3.0},
				//{6.0, 2.0, 3.0},{8.0, 3.0, 3.0}


				{8.0, 3.0, 3.0},{6.0, 2.0, 3.0},
				{4.0, 1.5, 3.0},{-0.5,0.66, 3.0}

		},
		{
				//{0.0,0.0, 3.0},{3.5, 0.0, 3.0},
				//{3.5, 0.0, 3.0},{8.0, 0.0, 3.0}

				{8.0, 0.0, 3.0},{3.5, 0.0, 3.0},
				{3.5, 0.0, 3.0},{0.0,0.0, 3.0}

		},
};
const GLfloat Car::tyre_guard_front[4][4][3]={
        {
                {18.0, 0.0, 3.0},{19.0, 3.0, 3.0},
                {20.0, 3.0, 3.0},{21.0, 0.0, 3.0}
        },
        {
                {18.0, 0.0, 2.7},{19.0, 3.0, 2.7},
                {20.0, 3.0, 2.7},{21.0, 0.0,2.7}
        },

        {
                {18.0, 0.0, 2.5}, {19.0, 3.0, 2.5},
                {20.0, 3.0, 2.5},{21.0, 0.0, 2.5}
        },
        {
                {18.0, 0.0, 2.2},{19.0, 3.0, 2.2},
                {20.0, 3.0, 2.2},{21.0, 0.0,2.2}
        },
};

const GLfloat Car::tyre_guard_front_flat[4][4][3]={
        {
                {18.0, 0.0, 2.2},{19.0, 0.0, 2.2},
                {20.0, 0.0, 2.2},{21.0, 0.0, 2.2}
        },
        {
                {18.0, 0.0, 2.2},{19.0, 1.0, 2.2},
                {20.0, 1.0, 2.2},{21.0, 0.0,2.2}
        },

        {
                {18.0, 0.0, 2.2}, {19.0, 2.0, 2.2},
                {20.0, 2.0, 2.2},{21.0, 0.0, 2.2}
        },
        {
                {18.0, 0.0, 2.2},{19.0, 3.0, 2.2},
                {20.0, 3.0, 2.2},{21.0, 0.0,2.2}
        },
};


const GLfloat Car::tyre_guard_rear[4][4][3]={
        {
                {21.0, 0.0, -3.0},{20.0, 3.0, -3.0},
                {19.0, 3.0, -3.0},{18.0, 0.0, -3.0}

        },
        {
                {21.0, 0.0,-2.7},{20.0, 3.0, -2.7},
                {19.0, 3.0, -2.7},{18.0, 0.0, -2.7},

        },

        {
                {21.0, 0.0, -2.5},{20.0, 3.0, -2.5},
                {19.0, 3.0, -2.5},{18.0, 0.0, -2.5}
        },
        {
                {21.0, 0.0,-2.2},{20.0, 3.0, -2.2},
                {19.0, 3.0, -2.2},{18.0, 0.0, -2.2}
        },
};

const GLfloat Car::tyre_guard_rear_flat[4][4][3]={
        {
                {18.0, 0.0, -2.2},{19.0, 0.0, -2.2},
                {20.0, 0.0, -2.2},{21.0, 0.0, -2.2}
        },
        {
                {18.0, 0.0, -2.2},{19.0, 1.0, -2.2},
                {20.0, 1.0, -2.2},{21.0, 0.0,-2.2}
        },

        {
                {18.0, 0.0, -2.2}, {19.0, 2.0, -2.2},
                {20.0, 2.0, -2.2},{21.0, 0.0, -2.2}
        },
        {
                {18.0, 0.0, -2.2},{19.0, 3.0, -2.2},
                {20.0, 3.0, -2.2},{21.0, 0.0,-2.2}
        },
};



const GLfloat Car::bottom_front1[4][4][3]={
        {
                {0.0,0.0, -3.0},{1.0, 0.0, -3.0},
                {1.5, 0.0, -3.0},{2.0, 0.0, -3.0}
        },
        {
                {0.0,0.0, -1.5},{1.0, 0.0, -1.5},
                {1.5, 0.0, -1.5},{2.0, 0.0, -1.5}
        },

        {
                {0.0,0.0, 1.5}, {1.0, 0.0, 1.5},
                {1.5, 0.0, 1.5},{2.0, 0.0, 1.5}
        },
        {
                {0.0,0.0,  3.0},{1.0, 0.0, 3.0},
                {1.5, 0.0, 3.0},{2.0, 0.0, 3.0}
        },
};

const GLfloat Car::bottom_front2[4][4][3]={
        {
                {5.0,0.0, -3.0},{6.0, 0.0, -3.0},
                {7.0, 0.0, -3.0},{20.0, 0.0, -3.0}
        },
        {
                {5.0,0.0, -1.5},{6.0, 0.0, -1.5},
                {7.0, 0.0, -1.5},{20.0, 0.0, -1.5}
        },

        {
                {5.0,0.0, 1.5}, {6.0, 0.0, 1.5},
                {7.0, 0.0, 1.5},{20.0, 0.0, 1.5}
        },
        {
                {5.0,0.0,  3.0},{6.0, 0.0, 3.0},
                {7.0, 0.0, 3.0},{20.0, 0.0, 3.0}
        },
};
