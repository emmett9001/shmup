//
//  Bullet.cpp
//  emptyExample
//
//  Created by Nina Freeman on 1/12/14.
//
//

#include "Bullet.h"

Bullet::Bullet(ofVec2f pos, ofVec2f dir){
    this->pos = pos;
    this->dir = dir;
    this->color = ofColor(0, 0, 0);
    this->alpha = 255;
    this->radius = 8;
    this->hasfired = false;
    
    this->fire();
}

void Bullet::draw(){
    ofSetColor(this->color, this->alpha);
    ofCircle(this->pos.x, this->pos.y, this->radius);
}

void Bullet::fire(){
    this->hasfired = true;
}

void Bullet::mouseMoved(int x, int y) {}

void Bullet::update(float deltatime){
    if(this->hasfired){
        GameObject::update(deltatime);
    }
}

void Bullet::highlight() {
    this->alpha = 255;
}

void Bullet::unhighlight() {
    this->alpha = 100;
}

void Bullet::makeActiveForCollisionFiltering() {
    this->color = ofColor(255, 255, 0);
}

void Bullet::makeInactiveForCollisionFiltering() {
    this->color = ofColor(0, 0, 0);
}