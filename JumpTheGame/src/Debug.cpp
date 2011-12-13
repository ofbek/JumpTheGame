#include "testApp.h"

void testApp::drawDebug() {
    if (!showDebug) return;
    
    ofSetColor(0,(int)ini.get("debugMaskAlpha",230));
    ofRect(0,0,ofGetWidth(),ofGetHeight());
    
    float x=5;
    float y=5;
    ofSetColor(255,255,0); 
    ofDrawBitmapString("frameRate: " + ofToString(ofGetFrameRate()), x, y+=15);
    ofDrawBitmapString("state: " + ofToString(currentState), x, y+=15);
    ofDrawBitmapString("videoScale: " + ofToString(videoScale), x, y+=15);
    ofDrawBitmapString("start button pos: " + ofToString(start.getPosition()), x, y+=15);
    ofDrawBitmapString("start button size: " + ofToString(start.getSize()), x, y+=15);
    ofDrawBitmapString("beginTimeLeft: " + ofToString(beginTimeLeft), x, y+=15);
    ofDrawBitmapString("timeLeft: " + ofToString(timeLeft), x, y+=15);
    ofDrawBitmapString("score: " + ofToString(score), x, y+=15);
    
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateZ(-90);
    ofScale(aspectRatio,aspectRatio);
    fbo.draw(-ofGetWidth()/2,-ofGetHeight()/2,ofGetWidth(),ofGetHeight());
    ofPopMatrix();
}

void testApp::drawWarpCorners() {
    if (!showBorders) return;
    ofSetColor(255, 0, 255);
    ofSetLineWidth(2);
    ofNoFill();
    ofBeginShape();
    for (int i=0; i<4; i++) {
        ofVertex(corners[i]);
    }
    ofEndShape();
    ofFill();
    for (int i=0; i<4; i++) {
        ofCircle(corners[i],20);
    }
}

void testApp::drawBorders() {
    if (!showBorders) return;
    //border
    ofNoFill();
    ofSetColor(255);
    ofSetLineWidth(5);
    ofRect(0,0,width,height);
    //origin
    ofSetColor(255,0,0);
    ofSetLineWidth(1);
    ofFill();
    ofCircle(0,0,10);
    //center
    ofSetColor(0,255,0);
    ofCircle(center,5);
    ofSetColor(255);
}