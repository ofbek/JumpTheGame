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
    
    //setup
    void setup();
    void setupHitTest();
    void setupVideo();
    void setupWindow();
    void setupPlay();
    void setupScore();

    //update
    void update();
    void updateVideo();
    void updateScore();
    
    //draw
    void draw();
    void drawBackground();
    void drawVideo();
    void drawWaitForStart();
    void drawPlaying();
    void drawDebug();
    void drawBorders();
    void drawWarpCorners();
    void drawScore();
    void drawStartButton();
    
    //play
    void playGoodExplosion();
    void playBadExplosion();
    
  	//hitTest
    void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);
    void hitGood();
    void hitBad();
    
    //sound
    void playSound(string name);
    
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
    void increaseScore();
    void decreaseScore();
    void createNewGoodItem();
    void createNewBadItem();

    //states
    enum State { WAIT_FOR_START, PLAYING, GAME_OVER };
    void setState(State state) { nextState=state; };
    bool getState(State state) { return currentState==state; };
    State currentState, nextState;

    void state_WaitForStart_begin();
    void state_WaitForStart_update();
    void state_WaitForStart_draw();
    void state_WaitForStart_end();

    void state_Playing_begin();
    void state_Playing_update();
    void state_Playing_draw();
    void state_Playing_end();
    
    void state_GameOver_begin();
    void state_GameOver_update();
    void state_GameOver_draw();
    void state_GameOver_end();
    
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
    ofxSprite bg,explosion,jet,moonbg,moonfg,startButton;
    ofxSprite diamond,donut,kleurexplosie,infographic;
    ofxSprite cijfers,gameover;
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
    ofPoint jetStartPosition;
    ofPoint jetAttractorPosition;

    //variables
    float bgScrollPos;
    float bgScrollSpeed;
    float aspectRatio;
    bool showBorders;
    bool showUserOutline;
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
    float maxScore;
    bool soundEnabled;
    int debugMaskColor;
    int debugMaskAlpha;
    bool flagHitGood;
    bool flagHitBad;
    float jetAttractorAmount;
    float jetRadius;
    
    //kinect resolution
    static const int w = 640;
    static const int h = 480;
    
    //window width corrected for rotation, but unscaled
    int width,height; 
    
    unsigned char *rgb;
    unsigned char *rgba;
};
