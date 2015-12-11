#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:

		//These are the main 3 open frameworks functions that get called on every app
		//setup for global vars, update for math to do while drawing, drawing to call in the values from update

		void setup();
		void update();
		void draw();
		int start = 1;
		//variable for FFT pitch tracking, some volume generation, timeslicing, and 3d graphics stuff too 

		ofSoundPlayer 			beat;


		float 				* fftSmoothed;
		int 				nBandsToGet;

		float 				* timeslicing;
		int 				timeslice = 0;

		float 				* volGeneration;
		int 				factor = 1;


		ofFloatImage			 img;
		ofEasyCam 			 cam;
		ofVboMesh 			 mesh;
};

