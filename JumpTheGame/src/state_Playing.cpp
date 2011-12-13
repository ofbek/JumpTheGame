#include "testApp.h"

void testApp::setupPlay() {
    boxStart.setPosition(-1000,-1000); //temp, hide start button
    
    boxJet.setPhysics(1, .5, 2);        
    boxJet.setup(box.getWorld(),100,100,40);
    boxJet.setData(&jet); //moet na box setup
    diamond.setScale(1);
    diamond.center();
    boxDiamond.setPhysics(1, .5, 2);        
    boxDiamond.setup(box.getWorld(),100,100,50);
    boxDiamond.setData(&diamond); //moet na box setup
    nextState = PLAYING;
}

void testApp::drawPlaying() {
    ofNoFill();
    ofSetColor(255);
    
    if (boxDiamond.getPosition().y > height) {
        boxDiamond.setPosition(ofRandom(0,width), ofRandom(-100,0));
        boxDiamond.setVelocity(0,0);
    }
    
    diamond.setPosition(boxDiamond.getPosition());
    ofSetColor(255);
    diamond.draw();
    
    boxJet.addAttractionPoint(getMouse(), 10);
    jet.setPosition(boxJet.getPosition());
    jet.setRotation(ofxGetHeading2D(boxJet.getVelocity()));
    jet.draw();
    
    if (explosion.getIsPlaying()) {
        explosion.draw();   
    }
    
    drawUserOutline();
}
