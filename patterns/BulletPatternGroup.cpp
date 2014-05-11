//
//  BulletPatternGroup.cpp
//  emptyExample
//
//  Created by Emmett Butler on 3/29/14.
//
//

#include "BulletPatternGroup.h"
#include "Stage.h"

BulletPatternGroup::BulletPatternGroup(Stage *stage) {
    this->patterns = vector<BulletPattern *>();
    this->paused = false;
    this->stage = stage;
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
    pattern->stage = this->stage;
}

void BulletPatternGroup::destroyAllBullets() {
    for(vector<BulletPattern*>::iterator it = this->patterns.begin(); it != this->patterns.end(); ++it) {
        BulletPattern* current = (BulletPattern *)*it;
        if (current->is_onscreen(this->stage)) {
            current->destroyAllBullets();
        }
    }
}

void BulletPatternGroup::pause() {
    this->paused = !this->paused;
    for(vector<BulletPattern*>::iterator it = this->patterns.begin(); it != this->patterns.end(); ++it) {
        BulletPattern* current = (BulletPattern *)*it;
        current->pause();
    }
}

void BulletPatternGroup::prepare() {
    float greatest_y = 0;
    for(vector<BulletPattern*>::iterator it = this->patterns.begin(); it != this->patterns.end(); ++it) {
        BulletPattern* current = (BulletPattern *)*it;
        if (current->origin.y > greatest_y) {
            greatest_y = current->origin.y;
        }
    }
    for(vector<BulletPattern*>::iterator it = this->patterns.begin(); it != this->patterns.end(); ++it) {
        BulletPattern* current = (BulletPattern *)*it;
        current->setOrigin(ofVec2f(current->origin.x, current->origin.y-greatest_y));
    }
}
