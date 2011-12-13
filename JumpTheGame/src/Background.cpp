#include "testApp.h"

void testApp::drawBackground() {
    ofImage &bgImage = bg.getCurrentImage();
    
    bgScrollPos-=bgScrollSpeed;
    
    if (bgScrollPos<-bgImage.height) bgScrollPos=0;
    else if (bgScrollPos>0) bgScrollPos=-bgImage.height;
    
    ofSetColor(255);
    bgImage.draw(0,bgScrollPos);
    bgImage.draw(0,bgScrollPos+bgImage.getHeight());
}


