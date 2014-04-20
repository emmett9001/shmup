//
//  BulletPattern.cpp
//  emptyExample
//
//  Created by Nina Freeman on 1/12/14.
//
//

#include "BulletPattern.h"
#include "StraightLineMover.h"
#include "Player.h"

map_type *BulletPatternFactory::creator_map;
const string BulletPattern::SLUG = "GENERIC";

BulletPattern::BulletPattern(){
    this->init(30, ofVec2f(0,0), 5, .6, -1, .5);
}

BulletPattern::BulletPattern(int count) {
    this->init(count, ofVec2f(0,0), .1, .6, -1, .5);
}

BulletPattern::BulletPattern(int count, ofVec2f origin) {
    this->init(count, origin, .1, .6, -1, .5);
}

BulletPattern::BulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout){
    this->init(count, origin, bulletspeed, volley_timeout, -1, .5);
}

BulletPattern::BulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout, float period, float duty){
    this->init(count, origin, bulletspeed, volley_timeout, period, duty);
}

void BulletPattern::init(int count, ofVec2f origin, float bulletspeed, float volley_timeout, float period, float duty) {
    this->volley_timeout = volley_timeout;
    this->count = count;
    this->bulletspeed = bulletspeed;
    this->origin = origin;
    this->last_volley = 0;
    this->frame_lifetime = 0;
    this->isrunning = false;
    this->period = period;
    this->duty = duty;
    this->movers = vector<Mover*>();
    this->start();
}

void BulletPattern::start(){
    this->isrunning = true;
}

void BulletPattern::setPlayersReference(vector<Player*>* players) {
    this->players = players;
}

void BulletPattern::addMover(Mover *mover) {
    if (this->movers.size() > 0) {
        ((Mover *)(this->movers.front()))->next = mover;
    }
    mover->attached = this;
    this->movers.push_back(mover);
}

void BulletPattern::update(float deltatime){
    vector<Bullet>::iterator it = bullets.begin();
    while(it != bullets.end()){
        it->update(deltatime);
        if (!it->is_onscreen()) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }

    float boundary = this->period*this->duty;
    if (this->isrunning) {
        boundary = this->period-(this->period*this->duty);
    }
    if (this->period != -1 && this->frame_lifetime > this->period_switch+boundary) {
        this->period_switch = this->frame_lifetime;
        this->isrunning = !this->isrunning;
    }

    this->frame_lifetime += deltatime;
    if (!this->isrunning) {
        return;
    }

    if (this->frame_lifetime > this->last_volley+this->volley_timeout) {
        this->last_volley = this->frame_lifetime;
        this->volley();
    }

    for(vector<Mover *>::iterator it = this->movers.begin(); it != this->movers.end(); it++){
        Mover *mover = (Mover *)*it;
        mover->update(deltatime);
    }
}

void BulletPattern::draw(){
    for(vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++){
        it->draw();
    }
}
