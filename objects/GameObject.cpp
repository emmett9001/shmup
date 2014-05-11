//
//  GameObject.cpp
//  emptyExample
//
//  Created by Nina Freeman on 1/12/14.
//
//

#include "GameObject.h"
#include "Stage.h"
#include "Camera.h"

void GameObject::update(float deltatime){
    // scale the movement by the number of MIN_DELTAs in deltatime
    // to account for slower framerates
    float scale = ceil(deltatime/MIN_DELTA);
    this->origin += this->dir*scale;
    this->frame_lifetime += deltatime;
}

bool GameObject::is_onscreen(){
    return (this->origin.x <= ofGetWidth() && this->origin.x >= 0 &&
            this->origin.y <= ofGetHeight() && this->origin.y >= 0);
}

bool GameObject::is_onscreen(Stage *stage){
    return (this->origin.x >= stage->camera->zero_point.x
            && this->origin.x <= stage->camera->zero_point.x+stage->camera->size.x
            && this->origin.y <= stage->camera->zero_point.y+stage->camera->size.y
            && this->origin.y >= stage->camera->zero_point.y
            );
}

ofVec2f GameObject::originRelativeToStage(Stage *stage) {
    return this->origin - stage->zero_point;
}

void GameObject::keyPressed(int key){
}

void GameObject::keyReleased(int key){
}

void GameObject::mouseMoved(int x, int y){
}