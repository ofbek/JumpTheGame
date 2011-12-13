#include "testApp.h"

void testApp::state_Playing_begin() {    
    playSound("start");
    
    //jet
    boxJet.setPhysics(1, .5, 2);
    boxJet.setup(box.getWorld(),jetStartPosition.x, jetStartPosition.y, jetRadius);
    boxJet.setData(&jet); //moet na box setup
    
    //diamond
    diamond.setScale(1);
    diamond.center();
    boxDiamond.setPhysics(1, .5, 2);        
    boxDiamond.setup(box.getWorld(),100,100,50);
    boxDiamond.setData(&diamond); //moet na box setup
    
}

void testApp::state_Playing_update() {
    //
}

void testApp::state_Playing_draw() {    
    ofNoFill();
    ofSetColor(255);
    
    //score
    updateScore();
    
    //check for hits
    if (flagHitGood) hitGood();
    if (flagHitBad) hitBad();
    
    //if missed diamond, create a new one
    if (boxDiamond.getPosition().y > height) {
        createNewGoodItem();
    }

    //if missed diamond, create a new one
    if (boxDiamond.getPosition().y > height) {
        createNewGoodItem();
    }

    //if jet misses target create a new one
    //......
    //......
    
    drawStartButton();
    
    //draw diamond
    ofSetColor(255);
    diamond.setPosition(boxDiamond.getPosition());
    diamond.draw();
    //boxDiamond.draw();
    
    //draw jet
    ofSetColor(255);
    boxJet.addAttractionPoint(jetAttractorPosition, jetAttractorAmount);
    jet.setPosition(boxJet.getPosition());
    jet.setRotation(ofxGetHeading2D(boxJet.getVelocity()));
    jet.draw();
    
    if (showBorders) {
        boxJet.draw();
        ofSetColor(255,0,0);
        ofCircle(jetAttractorPosition,jetAttractorAmount);
        ofSetColor(255);
    }
    
    //only draw explosion while playing
    if (explosion.getIsPlaying()) {
        explosion.draw();   
    }
    
    if (timeLeft<=0) {
        setState(GAME_OVER);   
    }
    
}

void testApp::state_Playing_end() {    
    //
}

void testApp::playGoodExplosion() {
    ofSetColor(255);
    explosion.setPosition(diamond.getPosition());
    explosion.play();
}

void testApp::playBadExplosion() {
    ofSetColor(255);
    explosion.setPosition(jet.getPosition());
    explosion.play();
}

void testApp::createNewGoodItem() { 
    //new random pos
    boxDiamond.setPosition(ofRandom(0,width), ofRandom(-100,0));
    boxDiamond.setVelocity(0,0);
}

void testApp::createNewBadItem() { 
    //new random pos 
    ofPoint pos(ofRandom(-5000,-1000), ofRandom(0,height));
    if (ofRandomuf()<.5) pos.x*=-1;
    
    boxJet.setPosition(pos);
    boxJet.setVelocity(0,0);
}

