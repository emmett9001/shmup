//
//  TargetedBulletPattern.cpp
//  emptyExample
//
//  Created by Emmett Butler on 3/29/14.
//
//

#include "TargetedBulletPattern.h"
#include "Player.h"

REGISTER_DEF_TYPE(TargetedBulletPattern);
const string TargetedBulletPattern::SLUG = "TargetedBulletPattern";

TargetedBulletPattern::TargetedBulletPattern()
: BulletPattern(0, ofVec2f(0, 0), 5, .1, 2, .5)
{
}

TargetedBulletPattern::TargetedBulletPattern(int count, ofVec2f origin)
: BulletPattern(count, origin)
{
}

TargetedBulletPattern::TargetedBulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout)
: BulletPattern(count, origin, bulletspeed, volley_timeout)
{
}

TargetedBulletPattern::TargetedBulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout, float period, float duty)
: BulletPattern(count, origin, bulletspeed, volley_timeout, period, duty)
{
}

void TargetedBulletPattern::volley(){
    Player *player = (*(this->players)).front();

    for (int i = 0; i < this->count; i++) {
        ofVec2f velocity = player->pos - this->origin;
        velocity = velocity.normalize()*this->bulletspeed;
        Bullet *b = new Bullet(this->origin, velocity);
        bullets.push_back(*b);
    }
}

string TargetedBulletPattern::describe() {
    ostringstream stream;
    stream << TargetedBulletPattern::SLUG << ":" << this->origin.x << "," << this->origin.y;
    stream << ":" << this->count;
    return stream.str();
}
