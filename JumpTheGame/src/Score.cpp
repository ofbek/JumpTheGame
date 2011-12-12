#include "testApp.h"

void testApp::setupScore() {
    score = beginScore;
    timeLeft = beginTimeLeft;
}

void testApp::updateScore() {
    if (currentState==PLAYING) {
        timeLeft -= 1.0/ofGetFrameRate();
    
        if (timeLeft<=0) {
            nextState = GAME_OVER;
        }
    }
}

void testApp::drawScore() {
    infographic.draw(0, 0);
    
    ofSetColor(0,255,0);
    ofFill();
    
    ofSetHexColor(timeBarColorBack);
    ofRect(timeBarRect);
    ofRectangle timeBarFrontRect = timeBarRect;
    timeBarFrontRect.width = ofMap(timeLeft,0,beginTimeLeft,0,timeBarRect.width);
    ofSetHexColor(timeBarColorBack);
    ofRect(timeBarFrontRect);
}