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
}

void StageMarker::stop() {
    this->is_active = false;
}

void StageMarker::update() {
    if (this->is_active) {
        // do my thing
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