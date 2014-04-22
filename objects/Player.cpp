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
    this->hitbox_radius = 5;
    this->colliding = false;
    this->respawned = false;
    this->speed = 2;
    this->color = ofColor(0, 255, 0);
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

    if (this->colliding) {
        if (this->frame_lifetime > .5 + this->collide_time) {
            this->respawn_time = this->frame_lifetime;
            this->color = ofColor(0, 255, 255);
            this->colliding = false;
            this->respawned = true;
        }
    }

    if (this->respawned) {
        if (this->frame_lifetime > 1 + this->respawn_time) {
            this->color = ofColor(0, 255, 0);
            this->respawned = false;
        }
    }
}

void Player::collided(GameObject *obj) {
    if (!this->respawned) {
        this->color = ofColor(0, 0, 255);
        this->colliding = true;
        this->collide_time = this->frame_lifetime;
    }
}

void Player::keyPressed(int key){
    if (this->control_type != kControlTypeKeyboard){ return; }
    if (key == 356) {  // left
        this->dir.x = -speed;
        this->keys.left = true;
    }
    if (key == 358) {  // right
        this->dir.x = speed;
        this->keys.right = true;
    }
    if (key == 357) {  // up
        this->dir.y = -speed;
        this->keys.up = true;
    }
    if (key == 359) {  // down
        this->keys.down = true;
        this->dir.y = speed;
    }
}

void Player::keyReleased(int key){
    if (this->control_type != kControlTypeKeyboard) { return; }
    if (key == 356) {
        if (!this->keys.right) {
            this->dir.x = 0;
        }
        this->keys.left = false;
    } if (key == 358) {
        if (!this->keys.left) {
            this->dir.x = 0;
        }
        this->keys.right = false;
    }
    if (key == 357){
        if (!this->keys.down) {
            this->dir.y = 0;
        }
        this->keys.up = false;
    } if (key == 359) {
        if (!this->keys.up) {
            this->dir.y = 0;
        }
        this->keys.down = false;
    }
}

void Player::axisChanged(ofxGamepadAxisEvent& e)
{
    if (this->control_type != kControlTypeJoystick) return;
    float value = abs(e.value) < .2 ? 0 : e.value;
    if (e.axis == 2) {
        this->dir.x = speed*value;
    }
    if (e.axis == 3) {
        this->dir.y = speed*value;
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
    ofSetColor(this->color);
    ofCircle(this->pos.x, this->pos.y, 20);
    ofSetColor(256, 0, 0);
    ofCircle(this->pos.x, this->pos.y, this->hitbox_radius);
}
