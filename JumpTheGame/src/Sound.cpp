#include "testApp.h"

void testApp::playSound(string name) {
    sounds[ini.get("sounds."+name,name+".wav")];
}