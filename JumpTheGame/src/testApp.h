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
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseMoved(int x, int y);
    void windowResized(int x, int y);
    
    void createCircle(int x, int y);
    void drawCircles();
    void drawBackground();
    void drawVideo();
    
    void rotateScene(bool bRotate);
    
    ofxSimpleOpenNI ni;
    VideoProcessing vid;
    ofxBox2d box;
    ofxBox2dPolygon poly;
    ofxIniSettings ini;
    ofImage imgVideo;
    ofPolyline polyline;
        
    ofxSprite bg,explosie,jet,moonbg,moonfg;

    vector<ofxBox2dCircle*> circles;
            
    ofxSpriteManager sprites;
    ofSoundPlayer sound;
    
    float bgScrollPos;
    float bgScrollSpeed;
    bool isSceneRotated;
    float aspectRatio;
    bool showBorders;
    bool showVideoOutline;
    bool showRawVideo;
    float videoScale;
    ofPoint videoPosition;
    
    int width,height; //window width corrected for rotation
    
    int w,h;
    unsigned char* rgb;
    unsigned char* rgba;
};
