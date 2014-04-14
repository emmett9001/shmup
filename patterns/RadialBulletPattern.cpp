//
//  RadialBulletPattern.cpp
//  emptyExample
//
//  Created by Nina Freeman on 1/12/14.
//
//

#include "RadialBulletPattern.h"

REGISTER_DEF_TYPE(RadialBulletPattern);
const string RadialBulletPattern::SLUG = "RadialBulletPattern";

RadialBulletPattern::RadialBulletPattern()
: BulletPattern(0, ofVec2f(0, 0), 10, .085)
{
}

RadialBulletPattern::RadialBulletPattern(int count, ofVec2f origin)
    : BulletPattern(count, origin)
{
}

RadialBulletPattern::RadialBulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout)
: BulletPattern(count, origin, bulletspeed, volley_timeout)
{
}

void RadialBulletPattern::volley(){
    static float angle = 1;
    float radius = 20;
    float speed_multiplier;

    for(int i = 0; i < this->count; i++){
        ofVec2f thispos = ofVec2f(radius*sin(angle),radius*cos(angle));
        speed_multiplier = this->bulletspeed*.01;
        Bullet *b = new Bullet(this->origin+thispos, thispos*speed_multiplier);
        bullets.push_back(*b);
        angle += (2*PI)/this->count;
    }
    angle += 2;
}

string RadialBulletPattern::describe() {
    ostringstream stream;
    stream << RadialBulletPattern::SLUG << ":" << this->origin.x << "," << this->origin.y;
    stream << ":" << this->count;
    return stream.str();
}
