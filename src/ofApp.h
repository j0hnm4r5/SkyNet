#pragma once

#include "ofMain.h"
#include "ofxARDrone.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
	
		ofxARDrone::Drone drone;
	
		bool doPause;
		bool keys[65535];
	
};
