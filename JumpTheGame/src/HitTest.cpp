#include "testApp.h"

void testApp::setupHitTest() {
    ofAddListener(box.contactStartEvents, this, &testApp::contactStart);
    ofAddListener(box.contactEndEvents, this, &testApp::contactEnd);
}

void testApp::hitStart() {
    
    cout << "HIT START" << endl;
    
    if (currentState==WAIT_FOR_START) {
        ofBackground(255,255,0); 
        
        cout << "in START" << endl;
        
        nextState = INIT_PLAY;
        
        if (soundEnabled) sounds["sounds/start.wav"];
    }
}

void testApp::hitGood() {
    
    explosion.setPosition(diamond.getPosition());
    explosion.play();
    
    score+=hitMinusPoints;
    if (score>maxScore) score=maxScore;
    
    ofBackground(0, 255, 0);
    
    if (soundEnabled) sounds["sounds/good.wav"].play();    
}

void testApp::hitBad() {
    score-=hitMinusPoints;
    if (score<0) score=0;
    
    explosion.setPosition(jet.getPosition());
    explosion.play();
    
    ofBackground(255, 0, 0);
    
    if (soundEnabled) sounds["sounds/bad.wav"].play();    
}


//--------------------------------------------------------------
void testApp::contactStart(ofxBox2dContactArgs &e) {
    ofBackground(255,0,255);
    
    if(e.a != NULL && e.b != NULL) { 
        
        if (e.a->GetType() == b2Shape::e_polygon || e.b->GetType() == b2Shape::e_polygon) {
        
            
            ofxSprite *a = (ofxSprite*)e.a->GetBody()->GetUserData();
            ofxSprite *b = (ofxSprite*)e.b->GetBody()->GetUserData();
            
            if ((a==&start || b==&start)) { //&& (e.a->GetBody()==&boxUser || e.b->GetBody()==&boxUser.)) {                
            
                cout << "user hit start??? " << e.a->GetBody() << " " << e.b->GetBody() << " " << &start << " " << &boxUser << endl;
                
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
