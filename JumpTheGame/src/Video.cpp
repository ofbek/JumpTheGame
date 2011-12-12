#include "testApp.h"

void testApp::setupVideo() {

    //setup textures
    rgb = new unsigned char[w*h*3];
    rgba = new unsigned char[w*h*4];
    
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
}

void testApp::drawVideo() {
    ofPushMatrix();
    
    ofTranslate(width/2,height/2); //center of window   //replace by 'center'
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
            v+=ofPoint(width/2,height/2); //replace by 'center'
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

void testApp::drawUserOutline() {
    ofPushMatrix();
    ofSetColor(255);
    ofSetLineWidth(3);   
    polyline.draw();
    ofPopMatrix();
}