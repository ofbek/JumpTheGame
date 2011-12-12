#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"
#include "VideoProcessing.h"
#include "ofxBox2d.h"
#include "ofxSpriteManager.h"
#include "ofxIniSettings.h"

class testApp : public ofBaseApp{
public:
    
    enum State { 
        WAIT_FOR_START, 
        INIT_PLAY,
        PLAYING, 
        GAME_OVER 
    } state;
    
    void update();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseMoved(int x, int y);
    void windowResized(int x, int y);

    void setup();
    void setupWindow();
    void setupWaitForStart();
    void setupPlay();
    
    void draw();
    void drawCircles();
    void drawPolyLine();
    void drawBackground();
    void drawVideo();
    void drawDebugInfo();
    void drawWaitForStart();
    void drawPlaying();
    
    void createCircle(int x, int y);    
	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);
    void rotateScene(bool bRotate);
    void setState(State state);
        
    ofPoint getMouse();
    ofxSimpleOpenNI ni;
    VideoProcessing vid;
    ofxBox2d box;
    ofxBox2dPolygon boxUser;
    ofxBox2dRect boxStart;
    ofxBox2dCircle boxJet;
    ofxBox2dCircle boxDiamond;
    ofxIniSettings ini;
    ofImage imgVideo;
    ofPolyline polyline;
    ofxSprite bg,explosion,jet,moonbg,moonfg,start,diamond,donut,kleurexplosie;
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
    ofPoint startButtonPosition;
    ofPoint center;
    float windowScale;
    float scaledWidth;
    float scaledHeight;
    
    //kinect resolution
    static const int w = 640;
    static const int h = 480;
    
    //window width corrected for rotation, but unscaled
    int width,height; 
    
    unsigned char *rgb;
    unsigned char *rgba;
};
