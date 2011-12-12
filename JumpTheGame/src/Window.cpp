#include "testApp.h"


void testApp::setupWindow() {
    //called at the start of every draw function
    
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2); //center
    ofRotateZ(90);  // rotate
    ofTranslate(-center); //set origin to left top
}

void testApp::windowResized(int w, int h) {
    //program runs always in portrait mode. width and height are reversed
    
    aspectRatio = (float)h/w;
    
    width = h;
    height = w;
    
    center.set(width/2,height/2);
    
    fbo.allocate(w,h,GL_RGB);
    
    //quad warp corners
    corners[0].set(0,0);
    corners[1].set(ofGetWidth(),0);
    corners[2].set(ofGetWidth(),ofGetHeight());
    corners[3].set(0,ofGetHeight());
}