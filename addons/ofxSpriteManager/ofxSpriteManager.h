#pragma once

#include "ofMain.h"
#include "ofxExtras.h"
#include "ofxSprite.h"

class ofxSpriteManager : public vector<ofxSprite> {
public:

    ofxSprite& loadSprite(string filename, int numFrames=1, int start=0, string id="");
    
    ofxSprite& operator[](string id);
    ofxSprite& operator[](int i) { return at(i); }; 
    
    void update();
    
};
