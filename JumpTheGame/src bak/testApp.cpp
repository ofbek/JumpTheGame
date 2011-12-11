#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofBackground(0);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofSetFullscreen(false);
    
    w = 640;
	h = 480;
    
    rgb = new unsigned char[w*h*3];
	rgba = new unsigned char[w*h*4];
    	
    ini.load("settings.ini");
    
	box.init();
	box.setGravity(0,0); //20
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
    
	release_on = ofGetElapsedTimeMillis() + ofRandom(300,1000);
    
    
    
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
    sprite.setLoop(true);
    sprite.play();
    
    ofxSprite &jet = sprites.loadSprite("jet/%02d.png",3,1,"jet");
    jet.setAnchorPercent(.5,.5);
    jet.setFrameRate(10);
    jet.setLoop(true);
    jet.setScale(.5);
    jet.play();
    
}

//--------------------------------------------------------------
void testApp::update(){
	ni.update();
	box.update();
	if(circles.size() > 50) {
		circles.erase(circles.begin());
	}
}

//--------------------------------------------------------------
void testApp::draw(){	
    
    sprites.update();
    
    ofImage &bgImage = sprites["bg"].getCurrentImage();
    
    bgScrollValue++;
    
    ofPushMatrix();
    ofTranslate(0,-bgScrollValue);
    bgImage.draw(0,0);
    bgImage.draw(0,bgImage.getHeight());
    ofPopMatrix();
    
    //sprites["jet"].setPosition(mouseX, mouseY);
    
    for (int i=0; i<sprites.size(); i++) {
        //if (!sprites[i].getIsPlaying()) sprites[i].visible = false;
        sprites[i].draw();
    }
    
	//bg.draw(0,0);
	float now = ofGetElapsedTimeMillis();
	if(now >= release_on) {
		release_on = ofGetElapsedTimeMillis() + ofRandom(1000,3000);
		int n = 10;
		float s = 200;
		float xx = 200;
		for(int i = 0; i < n; ++i) {
			ofxBox2dCircle* c = new ofxBox2dCircle();
			c->setPhysics(1, 0.5, 0.5);
			c->setup(box.getWorld(), ofRandom(xx-s,xx+s),0,  37.5);
			circles.push_back(c);			
		}
	}
	vector<ofxBox2dCircle*>::iterator it = circles.begin();
	while(it != circles.end()) {	
        //		ofSetHexColor(0xc0dd3b);
		glColor3f(1,1,1);
		//(*it)->draw();
		glPushMatrix();
        
        glTranslatef((*it)->getPosition().x, (*it)->getPosition().y,0);
        glRotatef((*it)->getRotation(),0,0,1);
        sprites["jet"].draw();
        //ding.draw(0,0);
		glPopMatrix();
		++it;
	}
	glColor3f(1,1,1);
	
	//ni.draw();
	ofImage img;
    
	ni.getAllMergedUserPixels(rgb, rgba);
	if(vid.process(rgb, w,h)) {
		vector<ofPoint>& pts = vid.getContour();
		ofPolyline polyline(pts);
		polyline.simplify(5.5);
		//polyline.draw();	
		//		glColor3f(1,1,1);
		
		poly.clear();
		polyline.addVertex(polyline[0]);
		poly.addVertexes(polyline);
		poly.create(box.getWorld());
		//		poly.draw();
	}
	
	img.setFromPixels(rgba, 640, 480,OF_IMAGE_COLOR_ALPHA);
	img.update();
	img.draw(0,0);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'r') {
		//ni.toggleRecording("screene.oni");
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	ofxBox2dCircle* c = new ofxBox2dCircle();
	c->setPhysics(1, 0.5, 0.5);
	c->setup(box.getWorld(), mouseX, mouseY, 10);
	circles.push_back(c);
    
    sound.play();
}
