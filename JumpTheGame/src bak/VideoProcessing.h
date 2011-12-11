#ifndef VIDEOPROCESSINGH
#define VIDEOPROCESSINGH

#include "ofxOpenCv.h"

class VideoProcessing {
public:
	VideoProcessing();
	bool process(unsigned char* pixels, int w, int h);
	void draw(float x, float y, float width, float height);
	vector<ofPoint>& getContour();
private:
	ofxCvColorImage color_image;
	ofxCvGrayscaleImage gray_image;
	ofxCvContourFinder contour_finder;
};

#endif
