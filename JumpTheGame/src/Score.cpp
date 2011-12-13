#include "testApp.h"

void testApp::setupScore() {
    timeLeft = beginTimeLeft;
    score = beginScore;
}

void testApp::updateScore() {
    
    if (getState(PLAYING)) {
        timeLeft -= 1.0/ofGetFrameRate();
    
        if (timeLeft<=0) {
            setState(GAME_OVER);
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
    ofSetHexColor(timeBarColorFront);
    ofRect(timeBarFrontRect);
    
    ofSetColor(255);
}

void testApp::increaseScore() {
    score+=scorePoints;
    if (score>maxScore) score=maxScore;
}

void testApp::decreaseScore() {
    score-=hitMinusPoints;
    if (score<0) score=0;
}
