//
//  BulletPatternGroup.cpp
//  emptyExample
//
//  Created by Emmett Butler on 3/29/14.
//
//

#include "BulletPatternGroup.h"

BulletPatternGroup::BulletPatternGroup() {
    this->patterns = vector<BulletPattern *>();
    this->paused = false;
}

void BulletPatternGroup::update(float deltatime) {
    for(vector<BulletPattern*>::iterator it = this->patterns.begin(); it != this->patterns.end(); ++it) {
        BulletPattern* current = (BulletPattern *)*it;
        if (current->is_onscreen()) {
            current->update(deltatime);
        }
    }
}

void BulletPatternGroup::draw() {
    for(vector<BulletPattern*>::iterator it = this->patterns.begin(); it != this->patterns.end(); ++it) {
        BulletPattern* current = (BulletPattern *)*it;
        if (current->is_onscreen()) {
            current->draw();
        }
    }
}

void BulletPatternGroup::addPattern(BulletPattern *pattern) {
    this->patterns.push_back(pattern);
    for(vector<BulletPattern*>::iterator it = this->patterns.begin(); it != this->patterns.end(); ++it) {
        BulletPattern* current = (BulletPattern *)*it;
    }
}

void BulletPatternGroup::pause() {
    this->paused = !this->paused;
    for(vector<BulletPattern*>::iterator it = this->patterns.begin(); it != this->patterns.end(); ++it) {
        BulletPattern* current = (BulletPattern *)*it;
        current->pause();
    }
}
