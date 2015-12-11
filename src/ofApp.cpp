#include "ofApp.h"
#include "math.h"

//--------------------------------------------------------------
void ofApp::setup(){	 

	ofBackgroundGradient(ofColor::gray, ofColor::black, OF_GRADIENT_CIRCULAR);
	// load in sound to be analyzed:

	beat.loadSound("sounds/song1.mp3");



	// the fft needs to be smoothed out, so we create an array of floats
	// for that purpose:
	
	fftSmoothed = new float[512];
	for (int i = 0; i < 512; i++){
		fftSmoothed[i] = 0;
	}
	
	//generating fake vol buffer ^^

	volGeneration = new float[512];
	for (int i = 0; i < 512; i++){
		volGeneration[i] = 0;
	}
	
	//setting time as a float so I can 

	timeslicing = new float[512];
	for (int i = 0; i < 512; i++){
		timeslicing[i] = 0;
	}

	//this stores the number of frequency bands to spread out the range of all frequencies

	nBandsToGet = 128;

	//specify the type of point or line that is drawn at the given vertex of my mesh
	
	mesh.setMode(OF_PRIMITIVE_LINES);
	//mesh.setMode(OF_PRIMITIVE_POINTS);
	
	//depth testing never enabled...

	ofEnableDepthTest();
	
	//for points only 
	//glEnable(GL_POINT_SMOOTH); // use circular points instead of square points ; smooth gives squares? commented out gives circles..
	glPointSize(2); // make the points bigger

	
}


//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(12,12,12);
	// update the sound playing system:
	ofSoundUpdate();	
	

	//Cant initiate audio in setup, simply calling beat.play() does nothing	

	if (start == 1){
		beat.play();
	}
	start++;
	
	//This returns nBandsToGet values kept in the buffer, val	

	float * val = ofSoundGetSpectrum(nBandsToGet);	

	//useful for smoothing out (decay over time)	
	
	for (int i = 0;i < nBandsToGet; i++){
		
		// let the smoothed calue sink to zero:

		fftSmoothed[i] *= 0.96f;
		
		// take the max, either the smoothed or the incoming:

		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
		
	}
	
	//Generating a slight volume increase over time, do this during presentation

	for (int v=0;v<nBandsToGet;v++){
		volGeneration[v] = fmod(.05*factor, 32);
		//cerr<< volGeneration[v] <<endl;

	}
	
	//Generating time intervals 0-33 factor == speed
	
	for (int t=0;t<nBandsToGet;t++){
		timeslicing[t] = fmod(20.5*factor, 32);
		//cerr<< timeslicing[t] <<endl;

	}

	factor++;
	

	


}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackgroundGradient(ofColor::gray, ofColor::black, OF_GRADIENT_CIRCULAR);
	//Automate volume change over 
	

	float * val = ofSoundGetSpectrum(nBandsToGet);
	
	
	// draw the fft resutls:
	//ofSetColor(255,255,255,255);
	int w = 32; int h = 32; int d = 32;

	int skip = 3;
	
	
	for (int i = -1*w;i < w; i+=skip){
		
		//iterating along chunks of time ie rows
		
		for (int j=-1*h;j<h;j+=skip){
			//iterating along chunks frequency bins of columns 
			
			//for (int k=-1*d;k<d;k+=skip){

			
	
			
	
			mesh.addColor(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));

			//ofIndexType saved_pos(timeslicing[i+w], (val[j+w]*25), (volGeneration[i+w]) );

			ofVec3f pos(timeslicing[i+w], (val[j+w]*18), (volGeneration[i+w]) );
	
			mesh.addVertex(pos);

			if (volGeneration[i+w] > 31.5)
				mesh.clear();
		
			
			
			//}
		}	
	}

	//begin 3D cam

	cam.begin();
	cam.setDistance(100);
	//ofScale(2, -2, 2); // flip the y axis and zoom in a bit
	//ofRotateY(90);
	
	//draw the mesh	
	
	mesh.draw();
	
	cam.end();
}



