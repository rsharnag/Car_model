/*
 * readPPM.h
 *
 *  Created on: 21-Oct-2012
 *      Author: rahul
 */

#ifndef READPPM_H_
#define READPPM_H_

#include<stdio.h>
#include<string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
GLubyte* read_PPM(char* filename, int* width, int* height);


#endif /* READPPM_H_ */
