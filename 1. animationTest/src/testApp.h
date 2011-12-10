#pragma once

#include "ofMain.h"
#include "ofxImageSequence.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void draw();
    void mousePressed(int x, int y, int button);
    
    void drawSprite(ofxImageSequence &mov, float x, float y, float scale);
    
    ofxImageSequence explosie,jet;		
    
    ofSoundPlayer sound;
};
