#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ini.load("settings.ini");
    
    ofBackground(0);
    ofSetFrameRate(ini.get("frameRate",60));
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofSetFullscreen(ini.get("fullscreen",false));
    ofxSetCursor(ini.get("showCursor",false));
    ofxSetWindowRect(ini.get("window",ofRectangle(0,0,1280,768)));
    
    rotateScene(ini.get("isSceneRotated",false));
    showBorders = ini.get("showBorders",false);
    showRawVideo = ini.get("showRawVideo",false);
    bgScrollSpeed = ini.get("bgScrollSpeed",-10);
    videoScale = ini.get("video.scale",1.5f);
    showVideoOutline = ini.get("showVideoOutline",false);
    videoPosition = ini.get("video.position",ofPoint());
    startButtonPosition = ini.get("start.position",ofPoint());
    
    // register the listener so that we get the events
    ofAddListener(box.contactStartEvents, this, &testApp::contactStart);
    ofAddListener(box.contactEndEvents, this, &testApp::contactEnd);
    
    windowResized(ofGetScreenHeight(), ofGetScreenWidth());
    
    rgb = new unsigned char[w*h*3];
    rgba = new unsigned char[w*h*4];
    
    box.init();
    box.setGravity(0,25); 
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
    explosion.load("explosie/%02d.png",5,1);
    jet.load("jet/%02d.png",3,1,"jet");
    moonbg.load("moonbg.png");
    moonfg.load("moonfg.png");
    start.load("start/start_%02d.png",2,1);
    diamond.load("diamant.png");
    donut.load("donut.png");
    kleurexplosie.load("kleurexplosie.png");
    
    sprites.add(bg);
    sprites.add(explosion);
    sprites.add(jet);
    sprites.add(moonbg);
    sprites.add(moonfg);
    sprites.add(start);
    sprites.add(diamond);
    sprites.add(donut);
    sprites.add(kleurexplosie);
    
    explosion.play();
    explosion.center();
    jet.center();
    
    start.center();
    start.play();
    start.setFrameRate(5);
    
    bg.setFrameRate(3);
    bg.play();
    
    bgScrollPos = 0;
    
    setState(WAIT_FOR_START);
}

void testApp::setState(State newState) {
    switch (state = newState) {
        case WAIT_FOR_START: setupWaitForStart(); break;
        case INIT_PLAY: setupPlay(); break;
        case PLAYING: break;
        case GAME_OVER: break;       
        default: break;
    }    
}

void testApp::setupWaitForStart() {
    //
}

void testApp::setupPlay() {
    boxJet.setPhysics(1, .5, 2);        
    boxJet.setup(box.getWorld(),100,100,40);
    boxJet.setData(&jet);
    boxDiamond.setData(&diamond);
    diamond.setScale(1);
    diamond.center();
    boxDiamond.setPhysics(1, .5, 2);        
    boxDiamond.setup(box.getWorld(),100,100,50);
    setState(PLAYING);
}

//--------------------------------------------------------------
void testApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    ni.update();    
    box.update();
    sprites.update();
    
    ni.getAllMergedUserPixels(rgb, rgba);
}

//--------------------------------------------------------------
void testApp::draw() {
    setupWindow();
    
    drawBackground();
    
    //draw moon & video
    ofSetColor(255);
    moonbg.draw(0,height-moonbg.getHeight());
    drawVideo();
    ofSetColor(255);
    
    switch (state) {
        case WAIT_FOR_START: drawWaitForStart(); break;
        case PLAYING: drawPlaying(); break;        
        default: break;
    }    
    
    ofSetColor(255);
    moonfg.draw(0,height-moonfg.getHeight());
    
    //boxJet.draw();
    
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
        ofCircle(center,5);
    }
    
    //draw all box2d opbjects
    //box.draw();
    
    drawDebugInfo();
}

void testApp::drawPlaying() {
    explosion.draw(getMouse().x,getMouse().y);
    
    ofNoFill();
    ofSetColor(255);
    //boxDiamond.setPosition(getMouse().x, getMouse().y);
    
    if (boxDiamond.getPosition().y > height) {
        boxDiamond.setPosition(ofRandom(0,width), ofRandom(-100,0));
        boxDiamond.setVelocity(0,0);
    }
    
    diamond.setPosition(boxDiamond.getPosition());
    boxDiamond.draw();
    ofSetColor(255);
    diamond.draw();
    
    boxJet.addAttractionPoint(getMouse(), 10);
    jet.setPosition(boxJet.getPosition());
    jet.setRotation(ofxGetHeading2D(boxJet.getVelocity()));
    jet.draw();
    
    drawCircles();
    drawPolyLine();
}

void testApp::drawWaitForStart() {
    start.draw(center + videoPosition + startButtonPosition);
    
    //boxStart.setPosition(start.getPosition());
    ofSetColor(0, 0, 255);
    boxStart.draw();
}

void testApp::drawDebugInfo() {
    if (!isSceneRotated) {
        float x=0;
        float y=100;
        ofSetupScreen();
        ofSetColor(255,255,0); 
        ofDrawBitmapString("state: " + ofToString(state), x, y+=15);
        ofDrawBitmapString("videoScale: " + ofToString(videoScale), x, y+=15);
        ofDrawBitmapString("start button pos: " + ofToString(start.getPosition()), x, y+=15);
        ofDrawBitmapString("start button size: " + ofToString(start.getSize()), x, y+=15);
    }
}

void testApp::setupWindow() {
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2); //center
    if (isSceneRotated) ofRotateZ(90);  // rotate
    else ofScale(windowScale,windowScale); // scale down to draw portait window on landscape screen
    ofTranslate(-center); //set origin to left top
}

ofPoint testApp::getMouse() {
    ofPoint mouse;
    if (isSceneRotated) {
        mouse.x = mouseY;
        mouse.y = height-mouseX;
    } else {
        float minMouseX = ofGetWidth()/2 - scaledWidth/2;
        float maxMouseX = ofGetWidth()/2 + scaledWidth/2;
        mouse.x = ofMap(ofGetMouseX(), minMouseX, maxMouseX, 0, width, false);
        mouse.y = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, height, false);
    }
    return mouse;
}

void testApp::createCircle(int x, int y) {
    ofxBox2dCircle* circle = new ofxBox2dCircle();
    circle->setPhysics(1, .75, 0.25);
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
        ofPopMatrix();
    }
}

void testApp::drawPolyLine() {
    ofPushMatrix();
    ofSetColor(255);
    ofSetLineWidth(3);   
    polyline.draw();
    ofPopMatrix();
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
    ofTranslate(-w/2,-h/2); //center of image
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
        polyline.addVertex(polyline[0]); //close polyline
        
        for (int i=0; i<polyline.getVertices().size(); i++) {
            ofVec3f &v = polyline.getVertices()[i];
            v+=videoPosition;
            v*=videoScale;
            v+=ofPoint(width/2,height/2);
            v-=ofPoint(w/2,h/2) * videoScale;
        }
        
        //copy vertices to box2d and add to world
        boxUser.clear(); //first clear box2d poly
        boxUser.addVertexes(polyline); //than copy in new vertices from simplyfied shape
        boxUser.create(box.getWorld()); //add to world
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
        //polyline.draw();	
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
    
    if (key == 'v') videoScale*=1.025;
    if (key == 'V') videoScale/=1.025;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
    ofPoint mouse = getMouse();
    createCircle(mouse.x, mouse.y);
    sound.play();
    
    if (state==WAIT_FOR_START) setState(INIT_PLAY);
    
}

void testApp::mouseMoved(int x, int y) {
    //videoScale = ofMap(x, 0, ofGetWidth(), 1, 2.5);
}

void testApp::windowResized(int w, int h) {
    //program runs always in portrait mode. width and height are reversed
    //if program is displayed on landscape screen than window is scaled down by the aspect ratio
    
    aspectRatio = (float)h/w;
    windowScale = isSceneRotated ? 1 : aspectRatio;
    
    width = h;
    height = w;
    
    center.set(width/2,height/2);
    
    scaledWidth = width * windowScale;
    scaledHeight = height * windowScale;
    
    //cout << "window resized: width:" << width << " height:" << height << endl;
    
}


//--------------------------------------------------------------
void testApp::contactStart(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) { 
        
        if (e.a->GetType() == b2Shape::e_polygon || e.b->GetType() == b2Shape::e_polygon) {
            
            ofxSprite *a = (ofxSprite*)e.a->GetBody()->GetUserData();
            ofxSprite *b = (ofxSprite*)e.b->GetBody()->GetUserData();
            
            if (a==&jet || b==&jet) {
                ofBackground(255, 0, 0);
            }
            
            if (a==&diamond || b==&diamond) { 
                cout << "SCORE!!!" << endl;
                ofBackground(0, 255, 0);
            }
            
        }
        
    }
}

//--------------------------------------------------------------
void testApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) { 
        
        //ofxSprite *a = (ofxSprite*)e.a->GetBody()->GetUserData();
        //ofxSprite *b = (ofxSprite*)e.b->GetBody()->GetUserData();
        
        ofBackground(0);
        
    }
}


