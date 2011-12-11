#pragma once

#include "ofMain.h"
#include "ofxAssets.h"

class ofxSprite : public ofNode {
public:
    
    ofxSprite();
    
    void customDraw();
    
    void setAnchorPercent(float xPct, float yPct);
    void setFrameRate(int frameRate);
    void setSpeed(float speed);
    void setProgress(float pct);
    void setPosition(float x, float y);
    void addFile(string filename);
    void setCurrentFrame(float frame);
    void setLoop(bool loop);
    void nextFrame();
    void previousFrame();
    
    void play();
    void pause();
    void stop();
    void update();
    
    float getProgress(); // 0..1
    int getTotalFrames();
    int getCurrentFrame();
    bool getIsPlaying();

    ofImage& getImageAtFrame(int frame);
    ofImage& getCurrentImage();
    
    string id;
    bool visible;
    
private:
    int totalFrames;
    int frameRate;
    bool loop;
    float speed;
    float pos;
    bool isPlaying;
    ofPoint anchorPoint;
    vector<string> filenames;
    static ofxImageAssets assets;
};
