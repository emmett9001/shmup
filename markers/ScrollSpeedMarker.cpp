//
//  ScrollSpeedMarker.cpp
//  emptyExample
//
//  Created by Emmett Butler on 5/13/14.
//
//

#include "ScrollSpeedMarker.h"
#include "Camera.h"
#include "Stage.h"

REGISTER_DEF_TYPE(ScrollSpeedMarker);
const string ScrollSpeedMarker::SLUG = "ScrollSpeedMarker";

ScrollSpeedMarker::ScrollSpeedMarker()
    : StageMarker(ofVec2f(0, 0))
{
    this->y_delta = -1;
}

ScrollSpeedMarker::ScrollSpeedMarker(ofVec2f origin, ofVec2f scroll_direction)
    : StageMarker(origin)
{
    this->scroll_direction = scroll_direction;
    this->y_delta = 0;
}

ScrollSpeedMarker::ScrollSpeedMarker(ofVec2f origin, float delta)
: StageMarker(origin)
{
    this->y_delta = delta;
}

void ScrollSpeedMarker::do_activation() {
    if (this->y_delta != 0) {
        this->stage->camera->scroll_direction.y += y_delta;
    } else {
        this->stage->camera->scroll_direction = this->scroll_direction;
    }
}

void ScrollSpeedMarker::do_active_update() {

}

string ScrollSpeedMarker::describe() {
    return StageMarker::_describe(ScrollSpeedMarker::SLUG);
}
