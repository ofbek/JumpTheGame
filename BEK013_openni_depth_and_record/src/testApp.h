#pragma once

#include "ofMain.h"

#include "ofxOpenNI.h"
#include "VideoProcessing.h"
#include "ofxBox2d.h"
class testApp : public ofBaseApp{

	public:
		testApp();
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		ofxSimpleOpenNI ni;
		VideoProcessing vid;
		ofxBox2d box;
		ofxBox2dPolygon poly;
		ofImage bg; // tmp
		vector <ofxBox2dCircle*>		circles;
		float release_on;
		ofImage ding;
};
