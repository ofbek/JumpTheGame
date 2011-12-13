#include "testApp.h"


//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
    
    //if GAME_OVER then return to WAIT_FOR_START
    setState(getState(WAIT_FOR_START) ? PLAYING : WAIT_FOR_START);
    
    //check for quad warping corners
    for (int i=0; i<4; i++) {
        if (ofDist(x,y,corners[i].x,corners[i].y)<20) {
            currentCorner = &corners[i];
        }
    }
}

void testApp::mouseDragged(int x, int y, int button) {
    if (currentCorner) {
        currentCorner->set(x,y);   
    }
}

void testApp::mouseReleased(int x, int y, int button) {
    currentCorner = 0;
}

void testApp::mouseMoved(int x, int y) {
    //videoScale = ofMap(x, 0, ofGetWidth(), 1, 2.5);
}

ofPoint testApp::getMouse() {
    ofPoint mouse;
    mouse.x = mouseY;
    mouse.y = height-mouseX;
    return mouse;
//    if (isSceneRotated) {
//        mouse.x = mouseY;
//        mouse.y = height-mouseX;
//    } else {
//        float minMouseX = ofGetWidth()/2 - scaledWidth/2;
//        float maxMouseX = ofGetWidth()/2 + scaledWidth/2;
//        mouse.x = ofMap(ofGetMouseX(), minMouseX, maxMouseX, 0, width, false);
//        mouse.y = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, height, false);
//    //}
//    return mouse;
}