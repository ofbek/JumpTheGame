#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    ofBackground(0);
    
    sound.loadSound("sound/explosion.wav");
    
    ofxSprite &bg = sprites.loadSprite("bg/bg_%02d.png",5,1,"bg");
    bg.setFrameRate(3);
    bg.play();
    bg.visible = false;
    
    bgScrollValue = 0;
    
    ofxSprite &sprite = sprites.loadSprite("explosie/%02d.png",5,1);
    sprite.setPosition(ofGetWidth()/2, ofGetHeight()/2);
    sprite.setAnchorPercent(.5,.5);
    sprite.setFrameRate(10);
    sprite.setScale(.5);
    sprite.setLoop(false);
    sprite.play();
    
}

//--------------------------------------------------------------
void testApp::draw() {
    sprites.update();
    
    ofImage &bgImage = sprites["bg"].getCurrentImage();

    bgScrollValue++;
    
    ofPushMatrix();
    ofTranslate(0,-bgScrollValue);
    bgImage.draw(0,0);
    bgImage.draw(0,bgImage.getHeight());
    ofPopMatrix();
    
    

    for (int i=0; i<sprites.size(); i++) {
        //if (!sprites[i].getIsPlaying()) sprites[i].visible = false;
        sprites[i].draw();
    }
}

void testApp::mousePressed(int x, int y, int button) {
    sound.play();
    
    sprites.push_back(sprites.back());
    sprites.back().setPosition(mouseX,mouseY);
    sprites.back().play();
}
