#include "testApp.h"

void testApp::state_WaitForStart_begin() {
    
    cout << "state_WaitForStart_begin" << endl;
    
    //init startButton
    boxStart.setPhysics(1, .5, 2);        
    boxStart.setup(box.getWorld(), center.x, center.y, 100,30);
    boxStart.setData(&startButton);
    boxStart.dead = false; //make undead...
    
    setupScore();
}

void testApp::state_WaitForStart_update() {
    //
}

void testApp::state_WaitForStart_draw() {
    boxStart.setPosition(center + videoPosition + startButtonPosition); //fixed pos

    drawStartButton();
}

void testApp::state_WaitForStart_end() {
    //pull start button upwards when game starts
    boxStart.addAttractionPoint(ofVec2f(center.x,-500), 1000);
}

void testApp::drawStartButton() {
    if (boxStart.dead) return;

    //remove after it left the screen
    if (boxStart.getPosition().y<0) {
        boxStart.destroy();
        return;
    }
    
    //draw image
    startButton.setPosition(boxStart.getPosition());
    startButton.draw();
    
    //start button outline
    if (showBorders) {
        ofNoFill();
        ofSetColor(0,255,0);
        boxStart.draw();
    }
}