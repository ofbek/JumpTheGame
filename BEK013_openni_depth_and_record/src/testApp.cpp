#include "testApp.h"

testApp::testApp() {
}

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofSetFullscreen(true);
	
	
	// setup box2d
	box.init();
	box.setGravity(0,20);
	box.createGround();
	box.setFPS(30.0);
	
	
	// setup openni
	bool record = false;
	ni.disableSkeleton();
	ni.disableDepth();	
	if(!record) {
		ni.initWithXML();
		//ni.startRecordingWhenUserIsDetected();
	}
	else {	
		ni.initWithRecording("KinectRecording.oni");
	}
	
	bg.loadImage("bg_01.png");
	ding.loadImage("rick.png");
	float s = 75	;
	ding.resize(s,s);
	ding.setAnchorPercent(0.5,0.5);
	release_on = ofGetElapsedTimeMillis() + ofRandom(300,1000);
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
	bg.draw(0,0);
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
			ding.draw(0,0);
		glPopMatrix();
		++it;
	}
	glColor3f(1,1,1);
	
	//ni.draw();
	ofImage img;
	int w = 640;
	int h = 480;
	unsigned char* rgb = new unsigned char[w*h*3];
	unsigned char* rgba = new unsigned char[w*h*4];
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
	
	delete[] rgb;
	delete[] rgba;
	
	if(ofGetFrameNum()%300 == 0) {
		ofSaveFrame();
	}

	// test.
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'r') {
		//ni.toggleRecording("screene.oni");
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	ofxBox2dCircle* c = new ofxBox2dCircle();
	c->setPhysics(1, 0.5, 0.5);
	c->setup(box.getWorld(), mouseX, mouseY, 10);
	circles.push_back(c);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}