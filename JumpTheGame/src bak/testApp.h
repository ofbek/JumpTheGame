#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"
#include "VideoProcessing.h"
#include "ofxBox2d.h"
#include "ofxSpriteManager.h"
#include "ofxIniSettings.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void mousePressed(int x, int y, int button);
    
    ofxSimpleOpenNI ni;
    VideoProcessing vid;
    ofxBox2d box;
    ofxBox2dPolygon poly;
    ofxIniSettings ini;

    vector<ofxBox2dCircle*> circles;
    
    //float release_on;
        
    ofxSpriteManager sprites;
    ofSoundPlayer sound;
    
    float bgScrollValue;
    
    int w,h;
    unsigned char* rgb;
    unsigned char* rgba;
};
