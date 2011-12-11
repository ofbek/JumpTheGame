#include "ofxSpriteManager.h"

ofxSprite& ofxSpriteManager::loadSprite(string filename, int numFrames, int start, string id) {
    ofxSprite sprite;
    
    sprite.id = id;
    
    for (int i=start; i<numFrames+start; i++) {
        sprite.addFile(ofVAArgsToString(filename.c_str(), i));
    }
    
    push_back(sprite);
    
    return back();  //be sure return the copy that was made by push_back instead of the local instance
}

void ofxSpriteManager::update() {
    for (int i=0; i<size(); i++) {
        at(i).update();
    }
}

ofxSprite& ofxSpriteManager::operator[](string id) {
    for (int i=0; i<size(); i++) {
        if (at(i).id==id) return at(i);
    }
    assert(false); //default if id not found
    return at(0);
}