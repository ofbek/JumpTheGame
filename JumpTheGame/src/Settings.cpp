#include "testApp.h"

void testApp::loadSettings() {
    ini.load("settings.ini");
    
    ofBackground(0);
    ofSetFrameRate(ini.get("frameRate",60));
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofSetFullscreen(ini.get("fullscreen",false));
    ofxSetCursor(ini.get("showCursor",false));
    ofxSetWindowRect(ini.get("window",ofRectangle(0,0,1280,768)));
    
    showBorders = ini.get("showBorders",false);
    showUserOutline = ini.get("showUserOutline",true);
    showRawVideo = ini.get("showRawVideo",false);
    bgScrollSpeed = ini.get("bgScrollSpeed",-10);
    videoScale = ini.get("video.scale",1.5f);
    showVideoOutline = ini.get("showVideoOutline",false);
    videoPosition = ini.get("video.position",ofPoint());
    startButtonPosition = ini.get("start.position",ofPoint());
    showDebug = ini.get("showDebug",false);
    beginTimeLeft = ini.get("beginTimeLeft",60.0f);
    beginScore = ini.get("beginScore",0);
    timeBarRect = ini.get("timeBarRect",ofRectangle(0,0,100,10));
    gameOverPosition = ini.get("gameOverPosition",ofPoint());
    timeBarColorBack = ini.get("timeBarColorBack",0xff00ff);
    timeBarColorFront = ini.get("timeBarColorFront",0xffff00);
    gameOverVisbibleTime = ini.get("gameOverVisbibleTime",15);
    timePerPoint = ini.get("timePerPoint",5);
    scorePoints = ini.get("scorePoints",10);
    maxScore = ini.get("maxScore",999);
    soundEnabled = ini.get("soundEnabled",true);
    
    //box2d
    box.init();
    box.setGravity(0,ini.get("box2d.gravity",20)); 
    box.setFPS(ini.get("box2d.frameRate",30));

}