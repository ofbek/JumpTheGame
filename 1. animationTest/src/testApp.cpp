#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofEnableAlphaBlending();
    ofBackground(0);
    
    explosie.loadSequence("explosie/", "png", 1, 14, 2);
	explosie.preloadAllFrames();
	explosie.setFrameRate(10);

    jet.loadSequence("jet/", "png", 1, 3, 2);
	jet.preloadAllFrames();
	jet.setFrameRate(10);
    
    sound.loadSound("sound/explosion.wav");
}

//--------------------------------------------------------------
void testApp::draw() {
    
    float explosieX = ofGetWidth()/2;
    float explosieY = 100;
    
    drawSprite(explosie, explosieX, explosieY, .5);
    
    float jetX = sin(ofGetElapsedTimef())*ofGetWidth()/2+ofGetWidth()/2;
    float jetY = mouseY;
    
    drawSprite(jet, jetX, jetY, .5);
}

void testApp::mousePressed(int x, int y, int button) {
    sound.play();
}

void testApp::drawSprite(ofxImageSequence &mov, float x, float y, float scale) {
    ofPushMatrix();
    ofTranslate(x,y);
    ofScale(scale, scale);
    ofTexture &tex = *mov.getFrameForTime(ofGetElapsedTimef());
    tex.draw(-tex.getWidth()/2, -tex.getHeight()/2);
    ofPopMatrix();   
}