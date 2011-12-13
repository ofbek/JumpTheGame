#include "testApp.h"

void testApp::setupWaitForStart() {
    boxStart.setPhysics(1, .5, 2);        
    boxStart.setup(box.getWorld(), 0,1000,100,30);
    boxStart.setData(&start); //moet na setup
}

void testApp::drawWaitForStart() {
    start.setPosition(center + videoPosition + startButtonPosition);
    boxStart.setPosition(start.getPosition());
        
    start.draw();
    
    ofNoFill();
    ofSetColor(0,255,0);
    boxStart.draw();
    
    drawUserOutline();
}
