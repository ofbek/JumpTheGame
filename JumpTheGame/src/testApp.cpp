#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    bgScrollPos = 0;
    currentCorner = 0;
        
    flagHitGood = false;
    flagHitBad = false;
        
    loadSettings();
    loadImages();
    
    setupHitTest();
    setupVideo();
    
    windowResized(ofGetScreenHeight(), ofGetScreenWidth());
    
    state_WaitForStart_begin(); //manually call this one
}

//--------------------------------------------------------------
void testApp::update() {
        
    //if new state
    if (currentState != nextState) {
        
        //call state end on previous state
        switch (currentState) {
            case WAIT_FOR_START : state_WaitForStart_end() ; break;
            case PLAYING        : state_Playing_end()      ; break;
            case GAME_OVER      : state_GameOver_end()     ; break;
        }
        
        currentState = nextState;

        //call state begin on next state
        switch (nextState) {
            case WAIT_FOR_START : state_WaitForStart_begin() ; break;
            case PLAYING        : state_Playing_begin()      ; break;
            case GAME_OVER      : state_GameOver_begin()     ; break;
        }
    }
    
    //common update commands
    updateVideo();
    sprites.update();
    box.update();

    //state specific update
    switch (currentState) {
        case WAIT_FOR_START : state_WaitForStart_update() ; break;
        case PLAYING        : state_Playing_update()      ; break;
        case GAME_OVER      : state_GameOver_update()     ; break;
    }
}

//--------------------------------------------------------------
void testApp::draw() {
    
    //pre-state-specific drawing commands
    fbo.begin();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2); //center
    ofRotateZ(90);  // rotate
    ofTranslate(-center); //set origin to left top
    drawBackground();
    ofSetColor(255);
    moonbg.draw(0,height-moonbg.getHeight());
    drawVideo();
    
    //state specific draw
    switch (currentState) {
        case WAIT_FOR_START : state_WaitForStart_draw() ; break;
        case PLAYING        : state_Playing_draw()      ; break;
        case GAME_OVER      : state_GameOver_draw()     ; break;
    }
    
    //post-state-specific drawing commands
    ofSetColor(255);
    moonfg.draw(0,height-moonfg.getHeight());    
    drawScore();
    drawBorders();
    fbo.end();
    ofxQuadWarp(fbo, corners[0], corners[1], corners[2], corners[3], 6, 6);
    drawWarpCorners();
    drawDebug();
}

