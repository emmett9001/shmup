#include "Stage.h"
#include "Background.h"
#include "Camera.h"
#include "BulletPatternGroup.h"

Stage::Stage()
{
    this->screen_dimensions = ofVec2f(700, 880);
    this->background = new Background(this->screen_dimensions);
    this->camera = new Camera();
    this->camera->setBackgroundReference(this->background);
    this->group = NULL;
}

void Stage::setGroupReference(BulletPatternGroup *group) {
    this->camera->setGroupReference(group);
    this->group = group;
}

void Stage::update(float deltatime) {
    this->camera->update(deltatime);
    this->background->update(deltatime);
}

void Stage::draw() {
    this->background->draw();
}

void Stage::pause() {
    this->camera->pause();
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
