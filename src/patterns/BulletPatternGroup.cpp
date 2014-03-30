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
}

void BulletPatternGroup::update(float deltatime) {
    for(vector<BulletPattern*>::iterator it = this->patterns.begin(); it != this->patterns.end(); ++it) {
        BulletPattern* current = (BulletPattern *)*it;
        current->update(deltatime);
    }
}

void BulletPatternGroup::draw() {
    for(vector<BulletPattern*>::iterator it = this->patterns.begin(); it != this->patterns.end(); ++it) {
        BulletPattern* current = (BulletPattern *)*it;
        current->draw();
    }
}

void BulletPatternGroup::addPattern(BulletPattern *pattern) {
    this->patterns.push_back(pattern);
}