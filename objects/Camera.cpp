//
//  Camera.cpp
//  emptyExample
//
//  Created by Emmett Butler on 5/5/14.
//
//

#include "Camera.h"
#include "BulletPatternGroup.h"
#include "GameObject.h"

Camera::Camera() {
    this->group = NULL;
    this->objects = vector<GameObject *>();
    this->scroll_direction = ofVec2f(0, -1);
    this->paused = false;
    this->last_scroll_direction = this->scroll_direction;
}

void Camera::setGroupReference(BulletPatternGroup *group) {
    this->group = group;
}

void Camera::update(float deltatime) {
    this->move(this->scroll_direction);
}

void Camera::startScrolling(ofVec2f dir) {
    this->scroll_direction = dir;
}

void Camera::stopScrolling() {
    this->scroll_direction = ofVec2f(0, 0);
}

bool Camera::isScrolling() {
    return this->scroll_direction.x != 0 || this->scroll_direction.y != 0;
}

void Camera::pause() {
    this->paused = !this->paused;
    if (this->paused) {
        this->last_scroll_direction = this->scroll_direction;
        this->scroll_direction = ofVec2f(0, 0);
    } else {
        this->scroll_direction = this->last_scroll_direction;
    }
    
}

void Camera::move(ofVec2f dir) {
    for(vector<BulletPattern*>::iterator it = this->group->patterns.begin(); it != this->group->patterns.end(); ++it) {
        BulletPattern* current_pattern = (BulletPattern *)*it;
        current_pattern->origin -= dir;
        for(vector<Bullet>::iterator it2 = current_pattern->bullets.begin(); it2 != current_pattern->bullets.end(); ++it2) {
            Bullet* current_bullet = (Bullet *)(&(*it2));
            current_bullet->pos -= dir;
        }
    }
}