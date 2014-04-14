//
//  FanOutBulletPattern.cpp
//  shmup
//
//  Created by Emmett Butler on 1/13/14.
//
//

#include "FanOutBulletPattern.h"

REGISTER_DEF_TYPE(FanOutBulletPattern);
const string FanOutBulletPattern::SLUG = "FanOutBulletPattern";

FanOutBulletPattern::FanOutBulletPattern()
    : BulletPattern(10, origin, 5, .2, 1, .5), width(PI/2), direction(ofVec2f(0, 1)), rotation_speed(0)
{
}

FanOutBulletPattern::FanOutBulletPattern(float width, ofVec2f direction)
    : BulletPattern(30, ofVec2f(0,0), .1, .2), width(width), direction(direction), rotation_speed(0)
{
}

FanOutBulletPattern::FanOutBulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout, float width, ofVec2f direction)
    : BulletPattern(count, origin, bulletspeed, volley_timeout), width(width), direction(direction), rotation_speed(0)
{
}

FanOutBulletPattern::FanOutBulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout, float width,
                                         ofVec2f direction, float rotation_speed)
: BulletPattern(count, origin, bulletspeed, volley_timeout), width(width), direction(direction), rotation_speed(rotation_speed)
{
}

FanOutBulletPattern::FanOutBulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout, float width,
                                         ofVec2f direction, float rotation_speed, float period, float duty)
: BulletPattern(count, origin, bulletspeed, volley_timeout, period, duty), width(width), direction(direction), rotation_speed(rotation_speed)
{
}


void FanOutBulletPattern::volley() {
    this->direction.normalize();
    float base_angle = acos(ofVec2f(0,1).dot(this->direction));
    if (this->direction.x < 0) {
        base_angle = 2*PI - base_angle;
    }
    float angle = base_angle - this->width/2.0 + (this->width/this->count)/2;
    float speed_multiplier = this->bulletspeed*.5;
    for(int i = 0; i < this->count; i++) {
        ofVec2f thispos = ofVec2f(sin(angle), cos(angle));
        Bullet *b = new Bullet(origin+thispos, thispos*speed_multiplier);
        bullets.push_back(*b);
        angle += this->width/this->count;
    }
    this->direction.rotate(this->rotation_speed*180/PI);
}

string FanOutBulletPattern::describe() {
    ostringstream stream;
    stream << FanOutBulletPattern::SLUG << ":" << this->origin.x << "," << this->origin.y;
    stream << ":" << this->count;
    return stream.str();
}
