#include "ofxSprite.h"

ofxImageAssets ofxSprite::assets; // create static instance

ofxSprite::ofxSprite() {
    isPlaying = false;
    speed = 1;
    pos = 0;
    loop = true;
    visible = true;
}

void ofxSprite::setFrameRate(int frameRate) {
    this->frameRate = frameRate;
}

void ofxSprite::setSpeed(float speed) {
    this->speed = speed;
}

void ofxSprite::addFile(string filename) {
    filenames.push_back(filename);
    assets.add(filename);
    totalFrames = filenames.size();
}

int ofxSprite::getTotalFrames() {
    return totalFrames;
}

void ofxSprite::setCurrentFrame(float frame) {
    pos = frame;

    if (pos<0) if (loop) { pos += totalFrames; } else stop();
    if (pos>=totalFrames) if (loop) { pos -= totalFrames;  } else { pos = totalFrames-.00001f; isPlaying=false; }
}

float ofxSprite::getProgress() {
    return pos / totalFrames;
}

void ofxSprite::setLoop(bool loop) {
    this->loop = loop;
}

void ofxSprite::update() {
    if (!isPlaying) return;
    
    setCurrentFrame(pos + speed * frameRate / ofGetFrameRate());
}

int ofxSprite::getCurrentFrame() {
    return (int)pos;
}

void ofxSprite::previousFrame() {
    setCurrentFrame(pos-1);
}

void ofxSprite::nextFrame() {
    setCurrentFrame(pos+1);
}

void ofxSprite::setAnchorPercent(float xPct, float yPct) {
    anchorPoint.set(xPct*getImageAtFrame(0).getWidth(),yPct*getImageAtFrame(0).getHeight());
}

void ofxSprite::setPosition(float x, float y) {
    ofNode::setPosition(x,y,0);
}

void ofxSprite::play() {
    visible = true;
    isPlaying = true;
    cout << "play" << endl;
}

void ofxSprite::stop() {
    pos = 0;
    isPlaying = false;
}

void ofxSprite::pause() {
    isPlaying = false;
}

bool ofxSprite::getIsPlaying() {
    return isPlaying;
}

void ofxSprite::customDraw() {
    if (!visible) return;
    getImageAtFrame(getCurrentFrame()).draw(-anchorPoint);
}

ofImage& ofxSprite::getImageAtFrame(int frame) {
    assert(totalFrames);
    if (frame<=totalFrames) return assets[filenames[frame]];
    else return assets[filenames[0]];
}

ofImage& ofxSprite::getCurrentImage() {
    return getImageAtFrame(getCurrentFrame());
}
