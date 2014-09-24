#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	//	set every bit in keys to 0;
	memset(keys, 0, sizeof(keys));
	
	doPause = false;
	
	drone.connect();
	
	// setup command history lengths for debugging and dumping onscreen
	drone.controller.commandHistory.setMaxLength(30);
	drone.dataReceiver.commandHistory.setMaxLength(30);
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
	//	if doPause is true, skip updating
	if (doPause) return;
	
	float s = 0.02;
	
	//	these are here instead of in keyPressed() because we want to be able to press multiple keys at once
	//	FORWARD/BACK
	if (keys[OF_KEY_UP]) drone.controller.pitchAmount -= s;
	else if (keys[OF_KEY_DOWN]) drone.controller.pitchAmount += s;
	//	STRAFE R/L
	if (keys[OF_KEY_LEFT]) drone.controller.rollAmount -= s;
	else if (keys[OF_KEY_RIGHT]) drone.controller.rollAmount += s;
	//	UP/DOWN
	if (keys['w']) drone.controller.liftSpeed += s;
	else if (keys['s']) drone.controller.liftSpeed -= s;
	//	TURN R/L
	if (keys['a']) drone.controller.spinSpeed -= s;
	else if (keys['d']) drone.controller.spinSpeed += s;
	
	drone.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	switch (key) {
			
		//	TAKEOFF/LAND
		case 't':
			drone.controller.takeOff(!drone.state.isTakingOff(), 3000);
			break;
		case 'l':
			drone.controller.land(!drone.state.isLanding(), 3000);
			break;
			
		//	PAUSE/UNPAUSE
		case 'p':
			doPause ^= true;
			
		//	EMERGENCY/UNEMERGENCY
		case 'e':
			drone.controller.emergency(0);
			break;
		case 'E':
			drone.controller.emergency(1);
	}
	
	//	pressed key added to array here
	keys[key] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	//	pressed key removed from array here
	keys[key] = false;
	
	//	set all movement changes to 0
	switch (key) {
		case OF_KEY_UP:
		case OF_KEY_DOWN:
			drone.controller.pitchAmount = 0;
			break;
		case OF_KEY_LEFT:
		case OF_KEY_RIGHT:
			drone.controller.rollAmount = 0;
			break;
		case 'w':
		case 's':
			drone.controller.liftSpeed = 0;
			break;
		case 'a':
		case 'd':
			drone.controller.spinSpeed = 0;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}