#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    output.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
    lattice = LatticeGas(output.getPixelsRef());
    lattice.setStartingState(100, true);
}

//--------------------------------------------------------------
void ofApp::update(){
    lattice.update();
    output.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    output.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}