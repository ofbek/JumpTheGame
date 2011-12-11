#pragma once

#include "ofMain.h"
#include "ofxSpriteManager.h"

class testApp : public ofBaseApp {
public:
    void setup();
    void draw();
    void mousePressed(int x, int y, int button);
            
    ofxSpriteManager sprites;
    ofSoundPlayer sound;
    
    float bgScrollValue;
};
