#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    bgScrollPos = 0;
    currentCorner = 0;
        
    loadSettings();
    loadImages();
    loadSounds();
    
    setupHitTest();
    setupVideo();
    setupScore();
    
    windowResized(ofGetScreenHeight(), ofGetScreenWidth());
    
    nextState = WAIT_FOR_START;
}

void testApp::updateState() {
    currentState = nextState;
    
    switch (currentState) {
        case WAIT_FOR_START: setupWaitForStart(); break;
        case INIT_PLAY: setupPlay(); break;
        case PLAYING: break;
        case GAME_OVER: break;       
        default: break;
    }    
}

//--------------------------------------------------------------
void testApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    updateState();
    updateScore();
    
    ni.update();    
    ni.getAllMergedUserPixels(rgb, rgba);
    sprites.update();
    box.update();
}

//--------------------------------------------------------------
void testApp::draw() {
    fbo.begin();
    
    setupWindow();
    
    drawBackground();
    
    //draw moon & video
    ofSetColor(255);
    moonbg.draw(0,height-moonbg.getHeight());
    drawVideo();
    ofSetColor(255);
    
    switch (currentState) {
        case WAIT_FOR_START: drawWaitForStart(); break;
        case PLAYING: drawPlaying(); break;        
        default: break;
    }
    
    ofSetColor(255);
    moonfg.draw(0,height-moonfg.getHeight());
    
    drawScore();
    drawBorders();
    
    fbo.end();
    
    ofxQuadWarp(fbo, corners[0], corners[1], corners[2], corners[3], 6, 6);
    
    drawWarpCorners();
    drawDebug();
}

void testApp::drawBackground() {
    ofImage &bgImage = bg.getCurrentImage();
    
    bgScrollPos-=bgScrollSpeed;
    
    if (bgScrollPos<-bgImage.height) bgScrollPos=0;
    else if (bgScrollPos>0) bgScrollPos=-bgImage.height;
    
    ofSetColor(255);
    bgImage.draw(0,bgScrollPos);
    bgImage.draw(0,bgScrollPos+bgImage.getHeight());
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'b') showBorders = !showBorders;
    if (key == 'f') ofToggleFullscreen();
    if (key == 'i') showRawVideo = !showRawVideo;
    if (key == 'v') videoScale*=1.025;
    if (key == 'V') videoScale/=1.025;
    if (key == 'd' || key=='r') showDebug = !showDebug;
    if (key == 'o') showUserOutline = !showUserOutline;
}


