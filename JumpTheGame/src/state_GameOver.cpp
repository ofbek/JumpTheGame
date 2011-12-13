#include "testApp.h"

float gameOverVisibleTime;

void testApp::state_GameOver_begin() {
    gameover.visible = true;    
    gameOverVisibleTime = ini.get("gameOverVisibleTime",15.0f);
}

void testApp::state_GameOver_update() {
    gameOverVisibleTime -= 1.0/ofGetFrameRate();
    
    if (gameOverVisibleTime<0) {
        setState(WAIT_FOR_START);
    }
}

void testApp::state_GameOver_draw() {
    ofPushMatrix();
    ofTranslate(center);
    ofTranslate(ini.get("gameOverPosition",ofPoint()));
    ofSetColor(255);
    gameover.draw();
    
    //draw digits
    ofTranslate(ini.get("gameOverScorePosition",ofPoint()));
    string digits = ofxFormatString("%03d", score);
    for (int i=0; i<3; i++) {
        cijfers.setCurrentFrame(digits.at(i)-'0');
        cijfers.draw((i-1)*cijfers.getWidth(),0);
    }
    
    ofPopMatrix();
}

void testApp::state_GameOver_end() {
    gameover.visible = false;
}