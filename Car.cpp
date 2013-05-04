/*
 * Car.cpp
 *
 *  Created on: 19-Oct-2012
 *      Author: rahul
 */
#include "Car.h"

void idle(int x) {
	if (animation.mode == animation.ANIMATING) {
		animation.nextframe();
		glutPostRedisplay();
		if (animation.mode == animation.ANIMATING)
			glutTimerFunc(1000.0 / 24, idle, 0);
	}
}

//Function to initialize some basic parameters
GLvoid initLights() {

	GLfloat light1_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light1_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat light1_specular[] = { 0.9, 0.9, 0.9, 1.0 };
	//Light properties

	GLfloat light2_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light2_diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light2_specular[] = { 0.9, 0.9, 0.9, 1.0 };
	//Night Light
	GLfloat light3_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat light3_diffuse[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat light3_specular[] = { 0.3, 0.3, 0.3, 1.0 };

	// --- light0 -- Spotlight -- Right head light
	glLightfv(GL_LIGHT0, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light1_specular);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.5);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);

	//-------Light 1 --Spotlight -- Left head Light
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.1);

	//-------Light 2 -- Global light
	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 2.0);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.5);

	//-------Light 3 -- Global light
	glLightfv(GL_LIGHT3, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light2_specular);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.0);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 1.0);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.5);

	//-------Light 3 -- Global Night light
	glLightfv(GL_LIGHT4, GL_AMBIENT, light3_ambient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light3_diffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, light3_specular);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 2.0);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 1.0);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.5);
	//---Initializing light model
//	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
//	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHTING);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	GLfloat position_1[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat position_2[] = { -1.0, 1.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT2, GL_POSITION, position_1);
	glLightfv(GL_LIGHT3, GL_POSITION, position_2);

//
//	GLfloat mat_diffuse[] = {0.6, 0.6, 0.6, 1.0};
//	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
//	GLfloat mat_shininess[] = {50.0};
//
//	glGetLightfv(GL_LIGHT3,GL_POSITION,position_2);
////	glEnable(GL_LIGHTING);
//	//	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT2);
//	glEnable(GL_LIGHT3);
//	glLightfv(GL_LIGHT0,GL_POSITION,headlight1_position);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	l0 = l1 = l2 = true;

}
//Function to initialize texture
void initTexture(GLuint* texName, int Width, int Height, GLubyte* array) {
	glGenTextures(1, texName);
	glBindTexture(GL_TEXTURE_2D, *texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, array);
}

GLvoid setCamera() {


	if (cam.cameraId == 0) {
		//Leave as it is
	}
	// Camera always in front of car
	if (cam.cameraId == 1) {
//		cam.lx = car.xpos;
//		cam.ly = car.ypos;
//		cam.lz = car.zpos;
		cam.xzdeg=-car.vOrientation-90;
		cam.ey = car.ypos;
		cam.ex = car.xpos + 1.2 * cos(car.vOrientation / 180.0 * M_PI);
		cam.ez = car.zpos - 1.2 * sin(car.vOrientation / 180.0 * M_PI);
		cam.updateLookAt();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat) sWidth / (GLfloat) sHeight, 0.1,
				1000.0);
		glMatrixMode(GL_MODELVIEW);
	}// Camera always in back of car
	if (cam.cameraId == 2) {
//		cam.lx = car.xpos;
//		cam.ly = car.ypos;
//		cam.lz = car.zpos;
		cam.xzdeg=-car.vOrientation+90;
		cam.ey = car.ypos+0.1;
		cam.ex = car.xpos - 1.2 * cos(car.vOrientation / 180 * M_PI);
		cam.ez = car.zpos + 1.2 * sin(car.vOrientation / 180 * M_PI);
		cam.updateLookAt();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat) sWidth / (GLfloat) sHeight, 0.1,
				1000.0);
		glMatrixMode(GL_MODELVIEW);
	}
	//Drivers view
	if (cam.cameraId == 3) {
//		cam.lx = car.xpos + 0.8 * cos((car.vOrientation) / 180 * M_PI);
//		cam.ly = car.ypos + 0.04;
//		cam.lz = car.zpos - 0.8 * sin((car.vOrientation) / 180 * M_PI);
		cam.xzdeg=-car.vOrientation+90;
		cam.ey = car.ypos + 0.04;
		cam.ex = car.xpos - 0.1 * cos((car.vOrientation) / 180 * M_PI);
		cam.ez = car.zpos + 0.1 * sin((car.vOrientation) / 180 * M_PI);
		cam.updateLookAt();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat) sWidth / (GLfloat) sHeight, 0.0009,
				1000.0);
		glMatrixMode(GL_MODELVIEW);
	}
	//Window view
	if (cam.cameraId == 4) {
//		cam.lx = car.xpos + 0.8 * sin((car.vOrientation) / 180 * M_PI);
//		cam.ly = car.ypos + 0.04;
//		cam.lz = car.zpos - 0.8 * cos((car.vOrientation) / 180 * M_PI);
		cam.ey = car.ypos + 0.04;
		cam.ex = car.xpos - 0.09 * cos((car.vOrientation) / 180 * M_PI);
		cam.ez = car.zpos + 0.09 * sin((car.vOrientation) / 180 * M_PI);
		cam.xzdeg=-car.vOrientation;
		cam.updateLookAt();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat) sWidth / (GLfloat) sHeight, 0.001,
				1000.0);
		glMatrixMode(GL_MODELVIEW);
	}

}
GLvoid InitGL() {

	//Setting the color used to clear the framebuffer
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	//Setting the depth used to clear the depthbuffer
	glClearDepth(1.0);
	//Enabling Z-buffering
	glEnable(GL_DEPTH_TEST);
	//Enabling Smooth Shading
	glShadeModel(GL_SMOOTH);
	//Setup backface culling
	glCullFace(GL_BACK);

	// Height and width of textures
	int wheelTexHeight, wheelTexWidth;
	int outerwheelTexWidth, outerwheelTexHeight;
	int skyTexHeight, skyTexWidth;
	int groundTexHeight, groundTexWidth;
	int roadTexWidth, roadTexHeight;
	int engineTexWidth, engineTexHeight;
	int seatTexWidth, seatTexHeight;
	int dashboardTexWidth, dashboardTexHeight;
	int speedoTexWidth, speedoTexHeight;
	int nightSkyTexHeight, nightSkyTexWidth;
	texBase = glGenLists(13);
	//Texture storages
	GLubyte* wheelTex;
	GLubyte* outerWheelTex;
	GLubyte* skyTex;
	GLubyte* groundTex;
	GLubyte* roadTex;
	GLubyte* engineTex;
	GLubyte* seatTex;
	GLubyte* dashBoardTex;
	GLubyte* speedoTex;
	GLubyte* nightSkyTex;

	//Reading textures
	wheelTex = read_PPM(strdup("resources/tyre_texture.ppm"), &wheelTexWidth,
			&wheelTexHeight);
	outerWheelTex = read_PPM(strdup("resources/wheel-rim.ppm"),
			&outerwheelTexWidth, &outerwheelTexHeight);
	skyTex = read_PPM(strdup("resources/sky.ppm"), &skyTexWidth, &skyTexHeight);
	groundTex = read_PPM(strdup("resources/ground.ppm"), &groundTexWidth,
			&groundTexHeight);
	roadTex = read_PPM(strdup("resources/road.ppm"), &roadTexWidth,
			&roadTexHeight);
	engineTex = read_PPM(strdup("resources/engine.ppm"), &engineTexWidth,
			&engineTexHeight);
	seatTex = read_PPM(strdup("resources/seat_texture.ppm"), &seatTexWidth,
			&seatTexHeight);
	dashBoardTex = read_PPM(strdup("resources/dashboard_texture.ppm"),
			&dashboardTexWidth, &dashboardTexHeight);
	speedoTex = read_PPM(strdup("resources/speedometer.ppm"), &speedoTexWidth,
			&speedoTexHeight);
	nightSkyTex= read_PPM(strdup("resources/nightSky.ppm"),&nightSkyTexWidth,&nightSkyTexHeight);
	//Initialize textures
	initTexture(&wheelTexName, wheelTexWidth, wheelTexHeight, wheelTex);
	initTexture(&wheelRimTexName, outerwheelTexWidth, outerwheelTexHeight,
			outerWheelTex);
	initTexture(&skyTexName, skyTexWidth, skyTexHeight, skyTex);
	initTexture(&groundTexName, groundTexWidth, groundTexHeight, groundTex);
	initTexture(&roadTexName, roadTexWidth, roadTexHeight, roadTex);
	initTexture(&engineTexName, engineTexWidth, engineTexHeight, engineTex);
	initTexture(&seatTexName, seatTexWidth, seatTexHeight, seatTex);
	initTexture(&dashBoardTexName, dashboardTexWidth, dashboardTexHeight,
			dashBoardTex);
	initTexture(&speedoTexName, speedoTexWidth, speedoTexHeight, speedoTex);
	initTexture(&nightSkyTexName,nightSkyTexWidth,nightSkyTexHeight,nightSkyTex);
	initLights();
	//	glEnable(GL_COLOR_MATERIAL);
	//	glEnable(GL_NORMALIZE);
	rot = 0;
	env.init(texBase, &skyTexName, &groundTexName, &roadTexName,&nightSkyTexName);
	car.init(texBase, &wheelTexName, &wheelRimTexName, &engineTexName,
			&seatTexName, &dashBoardTexName, &speedoTexName);
	cam.ex = car.xpos;
	cam.ey = car.ypos + 0.1;
	cam.ez = car.zpos + 3;
	cam.lx = car.xpos;
	cam.ly = car.ypos;
	cam.lz = car.zpos;
	cam.ux = cam.uz = 0;
	cam.uy = 1;
}

//-------------------------------------------------------------------------

//GL reshape callback
GLvoid ReshapeGL(GLsizei Width, GLsizei Height) {
	//Prevent a divison by zero
	sWidth = Width;
	sHeight = Height;
	if (Height == 0)
		Height = 1;
	//Set the viewport to the whole of the current window
	glViewport(0, 0, Width, Height);
	//Change the matrix mode to projection
	glMatrixMode(GL_PROJECTION);
	//Load the identity matrix
	glLoadIdentity();
	//Setup a perspective projection
	//Parameters are in the order -
	//vertical field of view angle - 60 degrees
	//Aspect Ratio i.e. width/height of window - 1.0
	//Near clipping plane distance - 0.1
	//Far clipping plane distance - 1000.0
	gluPerspective(45.0f, (GLfloat) Width / (GLfloat) Height, 0.1, 1000.0);
	//Change the matrix mode to modelview
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------

//GL display callback - does all the drawing
GLvoid DisplayGL() {
	if (keyboard[GLUT_KEY_RIGHT] && (keyboard[GLUT_KEY_UP])) {
			car.turn(true, 0.04,-30);
		} else if (keyboard[GLUT_KEY_RIGHT] && keyboard[GLUT_KEY_DOWN]) {
			car.turn(false, -0.04,-30);
		} else if (keyboard[GLUT_KEY_LEFT] && (keyboard[GLUT_KEY_UP])) {
			car.turn(false, 0.04,30);
		} else if (keyboard[GLUT_KEY_LEFT] && keyboard[GLUT_KEY_DOWN]) {
			car.turn(true, -0.04,30);
		} else if (keyboard[GLUT_KEY_RIGHT]) {
			car.wheel.yrot = -30;
			car.steerRot = -50;
		}

		else if (keyboard[GLUT_KEY_LEFT]) {
			car.wheel.yrot = 30;
			car.steerRot = 50;
		} else if (keyboard[GLUT_KEY_UP]) {
			car.moveforward(0.04);
			car.wheel.yrot = 0;
			car.steerRot = 0;
		} else if (keyboard[GLUT_KEY_DOWN]) {
			car.wheel.yrot = 0;
			car.steerRot = 0;
			car.moveforward(-0.04);
		}
	if (env.night) {
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT4);
	} else {
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
	}
	if (car.headLight) {
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	} else {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
	}
//	GLfloat cx0, cx1, cy, cz0, cz1, nx, ny, nz, normal;
//	cx0 = car.xpos
//			+ car.scaleFactor * 10.4 * cos(car.vOrientation / 180 * M_PI);
//	cy = car.ypos;
//	cz0 = car.zpos
//			- car.scaleFactor * 10.4 * sin(car.vOrientation / 180 * M_PI);
//	cx1 = cx0
//			+ car.scaleFactor * 2.6 * cos((90 - car.vOrientation) / 180 * M_PI);
//	cz1 = cz0
//			+ car.scaleFactor * 2.6 * sin((90 - car.vOrientation) / 180 * M_PI);
//	cx0 -= car.scaleFactor * 2.6 * sin((car.vOrientation) / 180 * M_PI);
//	cz0 += car.scaleFactor * 2.6 * cos((car.vOrientation) / 180 * M_PI);
//	std::cout << cx0 << " " << cy << " " << cz1 << " " << endl;
//	nx = cos(car.vOrientation);
//	ny = 0;
//	nz = sin(car.vOrientation);
//
//	GLfloat headlight1_position[] = { cx0, cy, cz0, 1.0 };
//	GLfloat headlight2_position[] = { cx1, cy, cz1, 1.0 };
//	GLfloat spot_direction[] = { nx, ny, nz };
	setCamera();
	//Clear the frame and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	//	glEnable(GL_CULL_FACE);

//	//Setup the camera
//	//Camera center at 0.0,5.0,0.0
//	//LookAt 0.0,0.0,0.0
//	//Up Vector 0.0,1.0,0.0
	gluLookAt(cam.ex, cam.ey, cam.ez, cam.lx, cam.ly, cam.lz, cam.ux, cam.uy,
			cam.uz);
//	const float deg=2.0;
//	const float axle_distance=0.160;
//	float turning_radius=-fabs(axle_distance/sin(deg/180*M_PI));
//	if(turn_right){
//		turning_radius=-turning_radius;
//	}
	env.draw();
	glPushMatrix();

	car.draw();

	glPopMatrix();



	//Translate as per the current translation parameters
	//  glTranslatef(xpos,ypos,zpos);
	//  //Rotate as per the current rotation parameters
	//  glRotatef(xrot,1.0,0.0,0.0);
	//  glRotatef(yrot,0.0,1.0,0.0);
	//  glRotatef(zrot,0.0,0.0,1.0);
	//
	//  //Toggle Backface culling
	//  if (enable_culling)
	//    glEnable(GL_CULL_FACE);
	//  else
	//    glDisable(GL_CULL_FACE);
	//
	//  //Toggle solid/wireframe drawing
	//  if(solid)
	//    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	//  else
	//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//
	//  //Draw the color cube
	//  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, allIndices);

	//Swap the double buffers
	glutSwapBuffers();
//	glutPostRedisplay();
}

//-------------------------------------------------------------------------

//GL keyboard callback
GLvoid KeyPressedGL(unsigned char key, GLint x, GLint y) {
	switch (key) {
	//quit
	case ESCAPE:
		exit(1);
		break;
	case 'c':
	case 'C':
		cam.cameraMovementEnable = !cam.cameraMovementEnable;
		break;
		//Change camera
	case '0':
		cam.cameraId = 0;
		setCamera();
		glutPostRedisplay();
		break;
	case '1':
		cam.cameraId = 1;
		setCamera();
		glutPostRedisplay();
		break;
	case '2':
		cam.cameraId = 2;
		setCamera();
		glutPostRedisplay();
		break;
	case '3':
		cam.cameraId = 3;
		setCamera();
		glutPostRedisplay();
		break;
	case '4':
		cam.cameraId = 4;
		setCamera();
		glutPostRedisplay();
		break;
	case 'l':
	case 'L':
		l0 = ~l0;
		break;
		//	//move along Z
	case 'q':
		if (cam.cameraMovementEnable) {
			cam.moveUp(0.15);
		}else{
			if (car.getDoor1Rotation() - 4 > -50)
				car.setDoor1Rotation(car.getDoor1Rotation() - 4);
			else
				car.setDoor1Rotation(-50);
		}
		glutPostRedisplay();
		break;
	case 'w':
		if (cam.cameraMovementEnable) {
			cam.movefront(0.15);
		}
		else{
			if (car.getDoor1Rotation() + 4 > 0)
				car.setDoor1Rotation(0);
			else
				car.setDoor1Rotation(car.getDoor1Rotation() + 4);
		}
		glutPostRedisplay();
		break;
	case 'a':
		if (cam.cameraMovementEnable) {
			cam.moveright(-0.15);
		}else{
			if (car.getDoor2Rotation() + 4 < 50)
				car.setDoor2Rotation(car.getDoor2Rotation() + 4);
			else
				car.setDoor2Rotation(50);
		}
		glutPostRedisplay();
		break;
	case 's':
		if (cam.cameraMovementEnable) {
					cam.movefront(-0.15);
		}
		else if (car.getDoor2Rotation() - 4 < 0)
			car.setDoor2Rotation(0);
		else
			car.setDoor2Rotation(car.getDoor2Rotation() - 4);
		glutPostRedisplay();
		break;
	case 'e':
		if (cam.cameraMovementEnable) {
			cam.moveUp(-0.15);
		}else{
			if (car.getWindSheil1dParam() + 0.2 > 0)
				car.setWindSheil1dParam(0);
			else
				car.setWindSheil1dParam(car.getWindSheil1dParam() + 0.2);
		}
		glutPostRedisplay();
		break;
	case 'd':
		if (cam.cameraMovementEnable) {
			cam.moveright(0.15);
		}
		else {
			if (car.getWindSheil1dParam() - 0.2 < -3.0)
				car.setWindSheil1dParam(-3.0);
			else
				car.setWindSheil1dParam(car.getWindSheil1dParam() - 0.2);
		}
		glutPostRedisplay();
		break;
	case 'r':
		if (car.getWindSheil2dParam() + 0.2 > 0)
			car.setWindSheil2dParam(0);
		else
			car.setWindSheil2dParam(car.getWindSheil2dParam() + 0.2);
		glutPostRedisplay();
		break;
	case 'f':
		if (car.getWindSheil2dParam() - 0.2 < -3.0)
			car.setWindSheil2dParam(-3.0);
		else
			car.setWindSheil2dParam(car.getWindSheil2dParam() - 0.2);
		glutPostRedisplay();
		break;
	case 't':
		if (car.getTrunkParams() + 4 > 100)
			car.setTrunkParams(100);
		else
			car.setTrunkParams(car.getTrunkParams() + 4);
		glutPostRedisplay();
		break;
	case 'g':
		if (car.getTrunkParams() - 4 < 0)
			car.setTrunkParams(0);
		else
			car.setTrunkParams(car.getTrunkParams() - 4);
		glutPostRedisplay();
		break;
	case 'y':
		if (car.getBonnetParams() - 4 < -50)
			car.setBonnetParams(-50);
		else
			car.setBonnetParams(car.getBonnetParams() - 4);
		glutPostRedisplay();
		break;
	case 'h':
		if (car.getBonnetParams() + 4 > 0)
			car.setBonnetParams(0);
		else
			car.setBonnetParams(car.getBonnetParams() + 4);
		glutPostRedisplay();
		break;
	case 'p':
		env.night=!env.night;
		glutPostRedisplay();
		break;
	case '.':
		car.headLight=!car.headLight;
		glutPostRedisplay();
		break;
	case 'z':
		if(animation.mode==animation.RECORDING){
			animation.stopRecording();
			cout<<"Recording stopped."<<endl;
		}else if(animation.mode == animation.NORMAL){
			animation.startRecording();
			cout<<"Recording started."<<endl;
		}
		break;
	case 'x':
		if(animation.mode==animation.NORMAL){
			animation.continueRecording();
			cout<<"Continue Recording"<<endl;
		}
		break;
	case 'v':
		if(animation.RECORDING){
			animation.saveState();
		}
		break;
	case 'b':
		if(animation.mode==animation.NORMAL){
			animation.play();
			cout<<"Playing animation."<<endl;
			glutTimerFunc(1000.0 / 24, idle, 0);
		}
		break;
	case 'n':
		if(animation.mode==animation.ANIMATING){
			animation.stopPlaying();
			cout<<"animation stopped."<<endl;
		}
		break;
	case 'm':
		if(animation.mode==animation.RECORDING){
			int frameRate=0;
			cout<<"Enter frame rate:";
			cin>>frameRate;cout<<endl;
			animation.setInterFrames(frameRate);
		}
		break;
	default:
		break;
	}

}

//-------------------------------------------------------------------------
GLvoid SpecialKeyUpGL(GLint key, GLint x, GLint y) {
	keyboard[key] = false;
}
//GL Keyboard callback for special keys
GLvoid SpecialKeyPressedGL(GLint key, GLint x, GLint y) {
	switch (key) {
	//Move along Y
	case GLUT_KEY_UP:
		if (cam.cameraMovementEnable) {
			cam.lookUp(1);
		} else {

			keyboard[key] = true;

			//  car.setDoor1Rotation(car.getDoor1Rotation()+1.1);
		}
		glutPostRedisplay();
		break;
		//Move along Y
	case GLUT_KEY_DOWN:
		if (cam.cameraMovementEnable) {
			cam.lookUp(-1);
		} else {

			keyboard[key] = true;
			//car.setDoor1Rotation(car.getDoor1Rotation()-1.1);
		}
		glutPostRedisplay();
		break;
		//Move along X
	case GLUT_KEY_LEFT:
		if (cam.cameraMovementEnable) {

			cam.rotate(-1);
		} else {

			keyboard[key] = true;
			rot -= 5.0f;
		}
		glutPostRedisplay();
		break;
		//       //Move along X
	case GLUT_KEY_RIGHT:
		if (cam.cameraMovementEnable) {

			cam.rotate(1);
		} else {

			keyboard[key] = true;
			rot += 5.0f;
		}
		glutPostRedisplay();
		break;
		//       //Rotate right about Z


	default:
		break;
	}
}

//-------------------------------------------------------------------------
int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	//Initialize GLUT display
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	//Window top-left corner position
	glutInitWindowPosition(0, 0);
	//Window size
	glutInitWindowSize(1300, 700);
	//Window title
	glutCreateWindow("Car");

	//Our Init function
	InitGL();

	//Register the callbacks
	glutDisplayFunc(DisplayGL);
	glutReshapeFunc(ReshapeGL);
	glutKeyboardFunc(KeyPressedGL);
	glutSpecialFunc(SpecialKeyPressedGL);
	glutSpecialUpFunc(SpecialKeyUpGL);
	glutFullScreen();
	char filename[100];
	if(argc<2){
		strcpy(filename,"scene.dat");
	}else{
		strcpy(filename,argv[1]);
	}
	animation.init(&car,&cam,&env,filename);

	//Start the GLUT event handling loop
	glutMainLoop();
}

