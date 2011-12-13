#include "testApp.h"

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