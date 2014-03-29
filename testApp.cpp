#include "testApp.h"
#include "CyclicEllipseBulletPattern.h"
#include "RadialBulletPattern.h"
#include "FanOutBulletPattern.h"
#include "OscillatingFanOutBulletPattern.h"
#include "TargetedBulletPattern.h"
#include "Player.h"

bool moving = false;
vector<BulletPattern*> patterns;
vector<BulletPattern*>::iterator cur_pattern;
vector<Player*> players;
Player *player;

//--------------------------------------------------------------
void testApp::setup(){
    ofVec2f origin = ofVec2f(400,200);
    player = new Player(kControlTypeKeyboard);
    patterns.push_back(new CyclicEllipseBulletPattern(30, origin, 5, .3));
    patterns.push_back(new RadialBulletPattern(20, origin, 10, .085));
    patterns.push_back(new TargetedBulletPattern(1, origin, 5, .1, 2, .5));
    patterns.push_back(new FanOutBulletPattern(10, origin, 5, .2, PI/2, ofVec2f(0, 1)));
    patterns.push_back(new OscillatingFanOutBulletPattern(10, origin, 5, .2, ofVec2f(0, 1)));
    cur_pattern = patterns.begin();
    
    players.push_back(player);
    
    for(vector<BulletPattern*>::iterator it = patterns.begin(); it != patterns.end(); ++it) {
        BulletPattern* current = (BulletPattern *)*it;
        current->setPlayersReference(&players);
    }
}

//--------------------------------------------------------------
void testApp::update(){
    float deltatime = ofGetLastFrameTime();
    (*cur_pattern)->update(deltatime);
    if (moving) {
        (*cur_pattern)->origin.x = 400+100*sin(ofGetElapsedTimef());
    }
    player->update(deltatime);
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255, 255, 255);
    int r = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
    int g = ofMap(mouseY, 0, ofGetHeight(), 0, 255);
    int b = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
    ofSetColor(r, g, b);
    ofFill();
    (*cur_pattern)->draw();
    player->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    player->keyPressed(key);
    if (key == ' ') {
        if (cur_pattern == patterns.end() - 1) {
            cur_pattern = patterns.begin();
        } else {
            cur_pattern++;
        }
    } else if (key == 'z') {
        moving = moving ? false : true;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    player->keyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    player->mouseMoved(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}