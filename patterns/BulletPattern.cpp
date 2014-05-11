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
#include "Stage.h"
#include "Camera.h"

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
    this->highlighted = true;
    this->isrunning = false;
    this->period = period;
    this->duty = duty;
    this->paused = false;
    this->movers = vector<Mover*>();
    this->stage = NULL;
    this->start();
}

void BulletPattern::start(){
    this->isrunning = true;
}

void BulletPattern::pause() {
    this->paused = !this->paused;
}

void BulletPattern::setPlayersReference(vector<Player*>* players) {
    this->players = players;
}

void BulletPattern::addMover(Mover *mover) {
    if (this->movers.size() > 0) {
        ((Mover *)(this->movers.front()))->next = mover;
    }
    mover->attach(this);
    this->movers.push_back(mover);
}

void BulletPattern::clearMovers() {
    this->movers.clear();
}

void BulletPattern::destroyAllBullets() {
    vector<Bullet>::iterator it = bullets.begin();
    while(it != bullets.end()){
        it = bullets.erase(it);
    }
}

void BulletPattern::update(float deltatime){
    if (this->paused) return;

    vector<Bullet>::iterator it = bullets.begin();
    while(it != bullets.end()){
        it->update(deltatime);
        if (this->highlighted) {
            it->highlight();
        } else {
            it->unhighlight();
        }
        if (!it->is_onscreen(this->stage)) {
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

    for(vector<Mover *>::iterator it = this->movers.begin(); it != this->movers.end(); it++){
        Mover *mover = (Mover *)*it;
        mover->update(deltatime);
    }

    this->frame_lifetime += deltatime;
    if (!this->isrunning) {
        return;
    }

    if (this->frame_lifetime > this->last_volley+this->volley_timeout) {
        this->last_volley = this->frame_lifetime;
        this->volley();
    }
}

bool BulletPattern::is_onscreen(Stage *stage){
    return (this->origin.x >= stage->camera->zero_point.x
            && this->origin.x <= stage->camera->zero_point.x+stage->camera->size.x
            && this->origin.y <= stage->camera->zero_point.y+stage->camera->size.y
            && this->origin.y >= stage->camera->zero_point.y
            );
}

void BulletPattern::setOrigin(ofVec2f origin) {
    this->origin = origin;
    for(vector<Mover *>::iterator it = this->movers.begin(); it != this->movers.end(); it++){
        Mover *mover = (Mover *)*it;
        mover->origin = origin;
    }
}

void BulletPattern::draw(){
    for(vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++){
        it->draw();
    }
}

void BulletPattern::highlight() {
    this->highlighted = true;
    for(vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++){
        it->highlight();
    }
}

void BulletPattern::unhighlight() {
    this->highlighted = false;
    for(vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++){
        it->unhighlight();
    }
}

string BulletPattern::_describe(string slug) {
    char* str = new char[30];
    ostringstream stream;
    sprintf(str, "%.2f", this->origin.x);
    stream << slug << ":" << str << ",";
    sprintf(str, "%.2f", this->origin.y);
    stream << str << ":" << this->count << ":" << this->volley_timeout << endl;
    for(vector<Mover *>::iterator it = this->movers.begin(); it != this->movers.end(); it++){
        Mover *mover = (Mover *)*it;
        stream << mover->describe() << endl;
    }
    return stream.str();
}
