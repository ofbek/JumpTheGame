#include "testApp.h"
#include "ofAppGlutWindow.h"

int main( ){
    ofAppGlutWindow window;
    window.setGlutDisplayString("rgba double samples>=4 depth");
	ofSetupOpenGL(&window, 800,750, OF_WINDOW);
	ofRunApp(new testApp());
}
