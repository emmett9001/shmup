#include "Stage.h"
#include "Background.h"
#include "Camera.h"
#include "BulletPattern.h"
#include "BulletPatternGroup.h"
#include "Mover.h"
#include "Marker.h"
#include "Player.h"

Stage::Stage()
{
    this->screen_dimensions = ofVec2f(700, 880);
    this->zero_point = ofVec2f((ofGetWidth()-this->screen_dimensions.x)/2, 0);
    this->background = new Background(this->screen_dimensions, this->zero_point);
    this->camera = new Camera(this->screen_dimensions, this->zero_point);
    this->camera->setBackgroundReference(this->background);
    this->group = NULL;
    this->edit_mode = false;
    
    this->markers = vector<StageMarker *>();
}

void Stage::setGroupReference(BulletPatternGroup *group) {
    this->camera->setGroupReference(group);
    this->group = group;
}

void Stage::update(float deltatime) {
    this->camera->update(deltatime);
    this->background->update(deltatime);
    
    for(vector<StageMarker *>::iterator it = this->markers.begin(); it != this->markers.end(); ++it) {
        StageMarker *current = (StageMarker *)*it;
        if (abs(this->camera->size.y/2 - this->camera->positionInFrame(current).y) < 3) {
            current->start();
        }
        current->update();
    }
}

void Stage::prepare() {
    this->group->prepare();
    for(vector<BulletPattern*>::iterator it = this->group->patterns.begin(); it != this->group->patterns.end(); ++it) {
        BulletPattern* current_pattern = (BulletPattern *)*it;
        current_pattern->origin += this->zero_point;
        for(vector<Mover *>::iterator it = current_pattern->movers.begin(); it != current_pattern->movers.end(); it++){
            Mover *mover = (Mover *)*it;
            mover->origin += this->zero_point;
            mover->stage = current_pattern->stage;
        }
        for(vector<Bullet>::iterator it2 = current_pattern->bullets.begin(); it2 != current_pattern->bullets.end(); ++it2) {
            Bullet* current_bullet = (Bullet *)(&(*it2));
            current_bullet->origin += this->zero_point;
        }
    }
}

void Stage::addPattern(BulletPattern *pattern) {
    pattern->stage = this;
    this->group->addPattern(pattern);
}

void Stage::addMarker(StageMarker *marker) {
    marker->stage = this;
    this->camera->addObject(marker);
    this->markers.push_back(marker);
}

void Stage::toggleEditMode() {
    this->edit_mode = !this->edit_mode;
}

void Stage::draw() {
    this->background->draw();
}

void Stage::drawLetterbox() {
    ofSetColor(0, 0, 0);
    ofRect(0, 0, this->zero_point.x, ofGetHeight());
    ofRect(this->zero_point.x+this->screen_dimensions.x, 0, this->zero_point.x, ofGetHeight());
    
    for(vector<StageMarker *>::iterator it = this->markers.begin(); it != this->markers.end(); ++it) {
        StageMarker *current = (StageMarker *)*it;
        current->draw();
    }
    
    this->camera->draw();
}

void Stage::pause() {
    this->camera->pause();
    this->toggleEditMode();
}

bool Stage::isScrolling() {
    return this->camera->isScrolling();
}

void Stage::stopScrolling() {
    this->camera->stopScrolling();
}

void Stage::startScrolling(ofVec2f direction) {
    this->camera->startScrolling(direction);
}
