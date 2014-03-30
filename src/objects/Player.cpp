//
//  Player.cpp
//  shmup
//
//  Created by Emmett Butler on 1/13/14.
//
//

#include "Player.h"

Player::Player(controlType control_type) {
    this->pos = ofVec2f(200, 200);
    this->speed = 2;
    if (control_type == kControlTypeJoystick) {
        this->speed = 3;
    }
    this->control_type = control_type;
}

void Player::mouseMoved(int x, int y) {
    if (this->control_type != kControlTypeMouse) { return; }
    this->pos = ofVec2f(x, y);
}

void Player::update(float deltatime) {
    GameObject::update(deltatime);
}

void Player::keyPressed(int key){
    if (this->control_type != kControlTypeKeyboard){ return; }
    if (key == 356) {  // left
        this->dir.x = -speed;
    }
    if (key == 358) {  // right
        this->dir.x = speed;
    }
    if (key == 357) {  // up
        this->dir.y = -speed;
    }
    if (key == 359) {  // down
        this->dir.y = speed;
    }
}

void Player::keyReleased(int key){
    if (this->control_type != kControlTypeKeyboard) { return; }
    if (key == 356 || key == 358) {
        this->dir.x = 0;
    }
    if (key == 357 || key == 359) {
        this->dir.y = 0;
    }
}

void Player::axisChanged(ofxGamepadAxisEvent& e)
{
    if (this->control_type != kControlTypeJoystick) return;
    if (e.axis == 2) {
        cout << "axis 2 " << ofToString(e.value) << endl;
        this->dir.x = speed*e.value;
    } else if (e.axis == 3) {
        cout << "axis 3 " << ofToString(e.value) << endl;
        this->dir.y = speed*e.value;
    }
}

void Player::buttonPressed(ofxGamepadButtonEvent& e)
{
    if (this->control_type != kControlTypeJoystick) return;
	cout << "BUTTON " << e.button << " PRESSED" << endl;
}

void Player::buttonReleased(ofxGamepadButtonEvent& e)
{
    if (this->control_type != kControlTypeJoystick) return;
	cout << "BUTTON " << e.button << " RELEASED" << endl;
}

void Player::draw() {
    ofCircle(this->pos.x, this->pos.y, 5);
}