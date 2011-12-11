#include "VideoProcessing.h"
#include <iostream>

VideoProcessing::VideoProcessing() {
	color_image.allocate(640,480);
	gray_image.allocate(640,480);
}

// returns true when it found a contour.
bool VideoProcessing::process(unsigned char* pixels, int w, int h) {
	color_image.setFromPixels(pixels, w, h);
	gray_image = color_image;
	contour_finder.findContours(gray_image, 10,w*h, 1, false);
	return (contour_finder.nBlobs > 0);
}

void VideoProcessing::draw(float x, float y, float width, float height) {
	gray_image.draw(x,y,width,height);
	contour_finder.draw(x,y);
	//color_image.draw(x,y,width,height);
}

vector<ofPoint>& VideoProcessing::getContour() {
	return contour_finder.blobs[0].pts;
}