#include "testApp.h"

void testApp::setupHitTest() {
    ofAddListener(box.contactStartEvents, this, &testApp::contactStart);
    ofAddListener(box.contactEndEvents, this, &testApp::contactEnd);
}

void testApp::hitGood() {
    
    playGoodExplosion();
    playSound("good");
    
    increaseScore();
    
    createNewGoodItem();
    
    //flash green
    debugMaskColor = 0x00ff00;
    
    //reset flag
    flagHitGood = false;
}

void testApp::hitBad() {
    
    playBadExplosion();
    playSound("bad");
    
    decreaseScore();

    createNewBadItem();
    
    //flash red
    debugMaskColor = 0xff0000;

    //reset flag
    flagHitBad = false;
}


//--------------------------------------------------------------
void testApp::contactStart(ofxBox2dContactArgs &e) {
    ofBackground(255,0,255);
    
    if(e.a != NULL && e.b != NULL) { 
        
        if (e.a->GetType() == b2Shape::e_polygon || e.b->GetType() == b2Shape::e_polygon) {
        
            ofxSprite *a = (ofxSprite*)e.a->GetBody()->GetUserData();
            ofxSprite *b = (ofxSprite*)e.b->GetBody()->GetUserData();
            
            if ((a==&startButton || b==&startButton)) {
                
                if (getState(WAIT_FOR_START)) {
                    setState(PLAYING);
                    debugMaskColor = 0xffff00;
                }
            }
            
            if (a==&jet || b==&jet) {
                if (getState(PLAYING)) {
                    flagHitBad = true;               
                }
            }
            
            if (a==&diamond || b==&diamond) { 
                if (getState(PLAYING)) {
                    flagHitGood = true;
                }
            }
            
        }
        
    }
}

//--------------------------------------------------------------
void testApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) { 

        debugMaskColor = 0x000000;

    }
}


