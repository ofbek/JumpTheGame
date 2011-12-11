#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ini.load("settings.ini");

    ofBackground(0);
	ofSetFrameRate(ini.get("frameRate",60));
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
    if (ini.get("hideCursor",true)) ofHideCursor();
	ofSetFullscreen(ini.get("fullscreen",false));
    ofxSetWindowRect(ini.get("window",ofRectangle(0,0,1280,768)));
    aspectRatio = (float)ofGetScreenHeight()/ofGetScreenWidth();
          
    rotateScene(ini.get("isSceneRotated",false));
    showBorders = ini.get("showBorders",false);
    showRawVideo = ini.get("showRawVideo",false);
    bgScrollSpeed = ini.get("bgScrollSpeed",-10);
    videoScale = ini.get("video.cale",1.5f);
    showVideoOutline = ini.get("showVideoOutline",false);
    videoPosition = ini.get("video.position",ofPoint());
    
    
    w = 640;
	h = 480;
    
    rgb = new unsigned char[w*h*3];
	rgba = new unsigned char[w*h*4];
    	    
	box.init();
	box.setGravity(0,20);
    //box.createGround();
	box.setFPS(30.0);
	
	// setup openni
	ni.disableSkeleton();
	ni.disableDepth();	
    
    if (ini.get("useKinect",true)) {
        ni.initWithXML();
        if (ini.get("recordKinectData",false)) {
            ni.startRecordingWhenUserIsDetected();   
        }
    } else {
        if (!ofxFileExists("KinectRecording.oni")) {
            ofLogError("KinectRecording.oni file not found.\nUse useKinect=true in .ini file to use the Kinect camera.");
            std::exit(1);
        }
        ni.initWithRecording("KinectRecording.oni");
    }
    
    sound.loadSound("sound/explosion.wav");

    bg.load("bg/bg_%02d.png",5,1,"bg");
    explosie.load("explosie/%02d.png",5,1);
    jet.load("jet/%02d.png",3,1,"jet");

    moonbg.load("moonbg.png");
    moonfg.load("moonfg.png");
    
    explosie.center();
    jet.center();
    
    sprites.add(bg);
    sprites.add(explosie);
    sprites.add(jet);
        
    bg.setFrameRate(3);
    bg.play();
    
    bgScrollPos = 0;
    
}

//--------------------------------------------------------------
void testApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
	ni.update();    
	box.update();
    sprites.update();
    
    ni.getAllMergedUserPixels(rgb, rgba);
	
    if (circles.size() > 50) {
		circles.erase(circles.begin());
	}
    
}

//--------------------------------------------------------------
void testApp::draw() {
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2); //center
    
    if (isSceneRotated) {
        ofRotateZ(90 * isSceneRotated);  
    } else {
        ofScale(aspectRatio,aspectRatio);
    }
    
    ofTranslate(-width/2,-height/2); //set origin to left top
        
    drawBackground();
    
    moonbg.draw(0,height-moonbg.getHeight());
    drawVideo();
    moonfg.draw(0,height-moonfg.getHeight());
        
    float x = width/2 + width/2 * sin(ofGetElapsedTimef());
    float y = height/2 + height/2 * cos(ofGetElapsedTimef());
    
    ofSetColor(255);
    
    jet.setPosition(x,y);
    jet.draw();
    
    if (showBorders) {
        //border
        ofNoFill();
        ofSetColor(255);
        ofSetLineWidth(5);
        ofRect(0,0,width,height);
        //origin
        ofSetColor(255,0,0);
        ofSetLineWidth(1);
        ofFill();
        ofCircle(0,0,10);
        //center
        ofSetColor(0,255,0);
        ofCircle(width/2,height/2,5);
    }

}

void testApp::createCircle(int x, int y) {
    ofxBox2dCircle* circle = new ofxBox2dCircle();
    circle->setPhysics(1, 0.5, 0.5);
    circle->setup(box.getWorld(), x, y, 37.5);
    circles.push_back(circle);			    
}

void testApp::drawCircles() {
    for (int i=0; i<circles.size(); i++) {
        ofPushMatrix();
        ofSetColor(255);
        ofNoFill();
        ofTranslate(circles[i]->getPosition());
        ofRotate(circles[i]->getRotation());
        ofCircle(0,0,circles[i]->getRadius());
        //sprites["jet"].draw();
        ofPopMatrix();
    }
}

void testApp::drawBackground() {
    ofImage &bgImage = bg.getCurrentImage();
    
    bgScrollPos-=bgScrollSpeed;
            
    if (bgScrollPos<-bgImage.height) bgScrollPos=0;
    else if (bgScrollPos>0) bgScrollPos=-bgImage.height;
    
    ofSetColor(255);
    bgImage.draw(0,bgScrollPos);
    bgImage.draw(0,bgScrollPos+bgImage.getHeight());
}

void testApp::drawVideo() {
    ofPushMatrix();
    
    ofTranslate(width/2,height/2); //center of window
    ofScale(videoScale, videoScale); //resize video
    ofTranslate(-imgVideo.getWidth()/2,-imgVideo.getHeight()/2); //center of image
    ofTranslate(videoPosition); //offset for video
    
    ofSetColor(255);
	imgVideo.setFromPixels(rgba, w, h, OF_IMAGE_COLOR_ALPHA);
    imgVideo.draw(0,0);
    
    if (showRawVideo) {
        ni.drawImage();
    }

    if (vid.process(rgb, w,h)) {
        polyline = vid.getContour();
        polyline.simplify(3);
        poly.clear();
        polyline.addVertex(polyline[0]);
        poly.addVertexes(polyline);
        poly.create(box.getWorld());
    }
    
    if (showBorders) {
        
        //draw video rect border
        ofSetColor(255,255,0);
        ofSetLineWidth(2);
        ofNoFill();
        ofRect(0,0,imgVideo.getWidth(), imgVideo.getHeight());
        
        //draw outline
        ofSetColor(255);
        ofSetLineWidth(5);        
        polyline.draw();	
        
        poly.draw();
	}
    
    ofPopMatrix();
    ofSetColor(255);
}

void testApp::rotateScene(bool bRotate) {
    isSceneRotated = bRotate;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'r') rotateScene(!isSceneRotated);
	if (key == 'b') showBorders = !showBorders;
    if (key == 'f') ofToggleFullscreen();
    if (key == 'i') showRawVideo = !showRawVideo;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    createCircle(x,y);
    sound.play();
}

void testApp::mouseMoved(int x, int y) {
    videoScale = ofMap(x, 0, ofGetWidth(), 1, 2.5);
}

void testApp::windowResized(int w, int h) {
    //program runs in portrait mode
    //width and height are reversed
    width = h;
    height = w;
}
