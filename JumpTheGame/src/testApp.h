#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"
#include "VideoProcessing.h"
#include "ofxBox2d.h"
#include "ofxSpriteManager.h"
#include "ofxIniSettings.h"

class testApp : public ofBaseApp {
public:
        
    //load
    void loadSettings();
    void loadImages();
    void loadSounds();
    
    //setup
    void setup();
    void setupHitTest();
    void setupVideo();
    void setupWindow();
    void setupWaitForStart();
    void setupPlay();
    
    //draw
    void draw();
    void drawUserOutline();
    void drawBackground();
    void drawVideo();
    void drawWaitForStart();
    void drawPlaying();
    void drawDebug();
    void drawBorders();
    void drawWarpCorners();
    void drawScore();
    
    //update
    void update();

	//hitTest
    void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);
    void hitGood();
    void hitBad();
    void hitStart();
    
    //mouse & keyboard
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseMoved(int x, int y);
    
    //mouse corrected for rotation
    ofPoint getMouse(); 
    
    //window
    void windowResized(int x, int y);
    
    //game logic
    enum State { WAIT_FOR_START, INIT_PLAY, PLAYING, GAME_OVER };
    State currentState;
    State nextState;
    void updateState();
    void setupScore();
    void updateScore();
    
    //objects
    ofxSimpleOpenNI ni;
    VideoProcessing vid;
    ofImage imgVideo;
    ofxBox2d box;
    ofxBox2dPolygon boxUser;
    ofxBox2dRect boxStart;
    ofxBox2dCircle boxJet;
    ofxBox2dCircle boxDiamond;
    ofxIniSettings ini;
    ofPolyline polyline;
    ofxSprite bg,explosion,jet,moonbg,moonfg,start;
    ofxSprite diamond,donut,kleurexplosie,infographic;
    ofxSprite cijfers;
    ofxSpriteManager sprites;
    ofxSoundAssets sounds;
    ofPoint videoPosition;
    ofPoint startButtonPosition;
    ofPoint center;
    ofFbo fbo;
    ofPoint corners[4];
    ofPoint *currentCorner;
    ofRectangle timeBarRect;
    ofPoint gameOverPosition;

    //variables
    float bgScrollPos;
    float bgScrollSpeed;
    float aspectRatio;
    bool showBorders;
    bool showUserOutline;
    bool showVideoOutline;
    bool showRawVideo;
    float videoScale;
    bool showDebug;
    float score, beginScore;
    float timeLeft,beginTimeLeft;
    int timeBarColorFront;
    int timeBarColorBack;
    float hitMinusPoints;
    float scorePoints;
    float timePerPoint;
    float gameOverVisbibleTime;
    float maxScore;
    bool soundEnabled;
    
    //kinect resolution
    static const int w = 640;
    static const int h = 480;
    
    //window width corrected for rotation, but unscaled
    int width,height; 
    
    unsigned char *rgb;
    unsigned char *rgba;
};
