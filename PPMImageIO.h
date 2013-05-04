#include <GL/gl.h>
#include <GL/glu.h>
bool PPMReader(char* filename, int& height, int& width, GLubyte*& pixels); 
bool PPMWriter(char* filename, int height, int width, GLubyte* pixels); 
struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
int ImageLoad(char *filename, Image *image);
