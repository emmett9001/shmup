//
//  Marker.cpp
//  emptyExample
//
//  Created by Emmett Butler on 5/13/14.
//
//

#include "Marker.h"
#include "Stage.h"

StageMarker::StageMarker(ofVec2f origin) {
    this->origin = origin;
    this->is_active = false;
}

void StageMarker::start() {
    this->is_active = true;
    this->do_activation();
}

void StageMarker::stop() {
    this->is_active = false;
}

void StageMarker::update() {
    if (this->is_active) {
        this->do_active_update();
    }
}

void StageMarker::draw() {
    if (this->is_active) {
        ofSetColor(255, 0, 0);
    } else {
        ofSetColor(0, 0, 255);
    }
    ofRect(this->stage->zero_point.x+this->stage->screen_dimensions.x+10, this->origin.y, 20, 20);
}