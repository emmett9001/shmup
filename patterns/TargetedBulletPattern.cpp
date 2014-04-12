//
//  TargetedBulletPattern.cpp
//  emptyExample
//
//  Created by Emmett Butler on 3/29/14.
//
//

#include "TargetedBulletPattern.h"
#include "Player.h"

const string TargetedBulletPattern::SLUG = "TARGETED";

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
    return TargetedBulletPattern::SLUG;
}