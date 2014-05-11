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
#include "Background.h"
#include "Mover.h"

Camera::Camera(ofVec2f size, ofVec2f zero_point) {
    this->background = NULL;
    this->group = NULL;
    this->size = size;
    this->zero_point = zero_point;
    this->origin = ofVec2f(0, 0);
    this->objects = vector<GameObject *>();
    
    this->ticks = vector<tick*>();
    this->ticks_count = 6;
    for (int i = 0; i < ticks_count; i++) {
        int offset = i*(this->size.y/ticks_count);
        tick *_tick = new tick();
        _tick->print_pos = offset;
        _tick->pos = offset-130;  // hack to close the weird gap between 0 and -whatever
        this->ticks.push_back(_tick);
    }
    
    this->scroll_direction = ofVec2f(0, -1);
    this->paused = false;
    this->last_scroll_direction = this->scroll_direction;
}

void Camera::setGroupReference(BulletPatternGroup *group) {
    this->group = group;
}

void Camera::setBackgroundReference(Background *background) {
    this->background = background;
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

void Camera::draw() {
    ofSetColor(255, 255, 255);
    for(vector<tick*>::iterator it = this->ticks.begin(); it != this->ticks.end(); ++it) {
        tick *current = (tick*)*it;
        ostringstream pos_stream;
        pos_stream << current->print_pos;
        ofDrawBitmapString(pos_stream.str(), ofGetWidth()-50, current->pos, 0);
    }
}

void Camera::move(ofVec2f dir) {
    if (dir.x == 0 && dir.y == 0) return;
    this->origin += dir;
    
    int lowest_tick = -1, highest_tick = -1;
    for(vector<tick*>::iterator it = this->ticks.begin(); it != this->ticks.end(); ++it) {
        tick *current = (tick*)*it;
        current->pos -= dir.y;
        if (current->pos < lowest_tick) {
            lowest_tick = current->pos;
        }
        if (current->pos > highest_tick) {
            highest_tick = current->pos;
        }
    }
    
    int stride = this->size.y/ticks_count;
    if (this->origin.y < lowest_tick - stride) {
        tick *_tick = new tick();
        _tick->print_pos = this->origin.y;
        _tick->pos = this->origin.y;
        this->ticks.push_back(_tick);
    }
    
    for(vector<BulletPattern*>::iterator it = this->group->patterns.begin(); it != this->group->patterns.end(); ++it) {
        BulletPattern* current_pattern = (BulletPattern *)*it;
        current_pattern->origin -= dir;
        for(vector<Mover *>::iterator it = current_pattern->movers.begin(); it != current_pattern->movers.end(); it++){
            Mover *mover = (Mover *)*it;
            mover->origin -= dir;
        }
        for(vector<Bullet>::iterator it2 = current_pattern->bullets.begin(); it2 != current_pattern->bullets.end(); ++it2) {
            Bullet* current_bullet = (Bullet *)(&(*it2));
            current_bullet->origin -= dir;
        }
    }
    background->origin -= dir;
}