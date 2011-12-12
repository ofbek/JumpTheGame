#include "testApp.h"

void testApp::loadImages() {
    
    bg.load("bg/bg_%02d.png",5,1);
    explosion.load("explosie/%02d.png",5,1);
    jet.load("jet/%02d.png",3,1,"jet");
    moonbg.load("images/moonbg.png");
    moonfg.load("images/moonfg.png");
    start.load("start/start_%02d.png",2,1);
    diamond.load("images/diamant.png");
    donut.load("images/donut.png");
    kleurexplosie.load("images/kleurexplosie.png");
    infographic.load("images/top_infographic.png");
    cijfers.load("cijfers/%02d_w70h100.png",10,0);
    
    sprites.add(bg);
    sprites.add(explosion);
    sprites.add(jet);
    sprites.add(moonbg);
    sprites.add(moonfg);
    sprites.add(start);
    sprites.add(diamond);
    sprites.add(donut);
    sprites.add(kleurexplosie);
    sprites.add(infographic);
    sprites.add(cijfers);
    
    explosion.play();
    explosion.center();
    explosion.setLoop(false);
    
    jet.center();
    
    start.center();
    start.play();
    start.setFrameRate(5);
    
    bg.setFrameRate(3);
    bg.play();

}