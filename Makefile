LIBS = -lm -lGLU -lGL -lglut
DEPS= Camera.o Car.o Model.o readPPM.o KeyFrameRecPlay.o

all:car
car: $(DEPS)
	g++ -o car $(DEPS) $(LIBS) 

Camera.o:Camera.h Camera.cpp
	g++ -c   Camera.cpp
Car.o:Car.h Car.cpp
	g++  -c Car.cpp 
Model.o: Model.h Model.cpp
	g++  -c Model.cpp 
readPPM.o:readPPM.h readPPM.cpp
	g++ -c readPPM.cpp 
KeyFrameRecPlay.o : KeyFrameRecPlay.cpp KeyFrameRecPlay.h
	g++ -c KeyFrameRecPlay.cpp

clean: 
	rm -f *.o car scene.dat

.PHONY: all clean 
