#include "testApp.h"

void testApp::setupHitTest() {
    ofAddListener(box.contactStartEvents, this, &testApp::contactStart);
    ofAddListener(box.contactEndEvents, this, &testApp::contactEnd);
}

void testApp::hitStart() {
    if (currentState==WAIT_FOR_START) {
        ofBackground(255,255,0); 
        
        nextState = INIT_PLAY;
        
        sounds["sounds/start.wav"];
    }
}

void testApp::hitGood() {
    
    explosion.setPosition(diamond.getPosition());
    explosion.play();
    
    score+=hitMinusPoints;
    
    ofBackground(0, 255, 0);
    
    sounds["sounds/good.wav"].play();    
}

void testApp::hitBad() {
    score-=hitMinusPoints;
    
    explosion.setPosition(jet.getPosition());
    explosion.play();
    
    ofBackground(255, 0, 0);
    
    sounds["sounds/bad.wav"].play();    
}


//--------------------------------------------------------------
void testApp::contactStart(ofxBox2dContactArgs &e) {
    ofBackground(255,0,255);
    
    if(e.a != NULL && e.b != NULL) { 
        
        if (e.a->GetType() == b2Shape::e_polygon || e.b->GetType() == b2Shape::e_polygon) {
            
            ofxSprite *a = (ofxSprite*)e.a->GetBody()->GetUserData();
            ofxSprite *b = (ofxSprite*)e.b->GetBody()->GetUserData();
            
            if (a==&start || b==&start) {
                
                hitStart();
                
            }
            
            if (a==&jet || b==&jet) {
                
                hitBad();
               
            }
            
            if (a==&diamond || b==&diamond) { 
               
                hitGood();
            }
            
        }
        
    }
}

//--------------------------------------------------------------
void testApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) { 
        
        //ofxSprite *a = (ofxSprite*)e.a->GetBody()->GetUserData();
        //ofxSprite *b = (ofxSprite*)e.b->GetBody()->GetUserData();
        
        //ofBackground(0);
        
    }
}
