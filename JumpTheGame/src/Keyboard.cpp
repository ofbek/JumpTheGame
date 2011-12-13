#include "testApp.h"

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'b') showBorders = !showBorders;
    if (key == 'f') ofToggleFullscreen();
    if (key == 'i') showRawVideo = !showRawVideo;
    if (key == 'v') videoScale*=1.025;
    if (key == 'V') videoScale/=1.025;
    if (key == 'd' || key=='r') showDebug = !showDebug;
    if (key == 'o') showUserOutline = !showUserOutline;
}
