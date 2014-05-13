#include "testApp.h"
#include "Player.h"
#include "PatternEditor.h"
#include "BulletPatternGroup.h"
#include "BoardPartition.h"
#include "Camera.h"
#include "Stage.h"
#include "ScrollSpeedMarker.h"

#include "CyclicEllipseBulletPattern.h"
#include "RadialBulletPattern.h"
#include "FanOutBulletPattern.h"
#include "OscillatingFanOutBulletPattern.h"
#include "TargetedBulletPattern.h"

vector<BulletPatternGroup*> groups;
vector<BulletPatternGroup*>::iterator cur_group;
vector<Player*> players;
PatternEditor *editor;
Player *player;
Camera *camera;
Stage *stage;
BoardPartition *board_partition;

//--------------------------------------------------------------
void testApp::setup(){
    ofxGamepadHandler::get()->enableHotplug();

    controlType control_type = kControlTypeKeyboard;
	if(ofxGamepadHandler::get()->getNumPads()>0){
        ofxGamepad* pad = ofxGamepadHandler::get()->getGamepad(0);
        ofAddListener(pad->onAxisChanged, this, &testApp::axisChanged);
        ofAddListener(pad->onButtonPressed, this, &testApp::buttonPressed);
        ofAddListener(pad->onButtonReleased, this, &testApp::buttonReleased);

        control_type = kControlTypeJoystick;
	}

    ofVec2f origin = ofVec2f(230,200);
    player = new Player(control_type);

    stage = new Stage();
    
    BulletPatternGroup *group;
    
    // blank group for editing
    group = new BulletPatternGroup(stage);
    groups.push_back(group);
    
    cur_group = groups.begin();

    stage->setGroupReference(*cur_group);
    
    // test only - these should be added from file
    ScrollSpeedMarker *testMarker = new ScrollSpeedMarker(ofVec2f(69, -200), -1.01);
    stage->addMarker(testMarker);

    editor = new PatternEditor(*cur_group, stage);
    
    board_partition = new BoardPartition(stage);

    players.push_back(player);

    board_partition->setPlayersReference(&players);
    board_partition->setGroupReference(*cur_group);
    board_partition->setDelegate(this);
    for(vector<BulletPatternGroup*>::iterator it = groups.begin(); it != groups.end(); ++it) {
        BulletPatternGroup* currentGroup = (BulletPatternGroup *)*it;
        for(vector<BulletPattern*>::iterator it2 = currentGroup->patterns.begin(); it2 != currentGroup->patterns.end(); ++it2) {
            BulletPattern* currentPattern = (BulletPattern *)*it2;
            currentPattern->setPlayersReference(&players);
        }
    }

    editor->setPlayersReference(&players);
    stage->players = &players;
}

void testApp::collided(GameObject *obj) {
}

//--------------------------------------------------------------
void testApp::update(){
    float deltatime = ofGetLastFrameTime();
    (*cur_group)->update(deltatime);
    player->update(deltatime);
    board_partition->update(deltatime);
    stage->update(deltatime);
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255, 255, 255);

    stage->draw();

    board_partition->draw();

    player->draw();
    (*cur_group)->draw();
    
    stage->drawLetterbox();
    
    editor->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    player->keyPressed(key);
    if (key == ' ') {
        if (cur_group == groups.end() - 1) {
            cur_group = groups.begin();
        } else {
            cur_group++;
        }
        board_partition->setGroupReference(*cur_group);
        editor->group = *cur_group;
    }
    editor->keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    player->keyReleased(key);
    editor->keyReleased(key);
}

void testApp::mouseReleased(int x, int y, int button){
    editor->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    player->mouseMoved(x, y);
    editor->mouseMoved(x, y);
}

void testApp::axisChanged(ofxGamepadAxisEvent& e)
{
	player->axisChanged(e);
}

void testApp::buttonPressed(ofxGamepadButtonEvent& e)
{
	player->buttonPressed(e);
}

void testApp::buttonReleased(ofxGamepadButtonEvent& e)
{
	player->buttonReleased(e);
    if (cur_group == groups.end() - 1) {
        cur_group = groups.begin();
    } else {
        cur_group++;
    }
    board_partition->setGroupReference(*cur_group);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    editor->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    editor->mousePressed(x, y, button);
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
