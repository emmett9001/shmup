//
//  BoardQuadrant.cpp
//  emptyExample
//
//  Created by Emmett Butler on 3/30/14.
//
//

#include "BoardQuadrant.h"
#include "BulletPattern.h"
#include "BulletPatternGroup.h"
#include "Player.h"

BoardQuadrant::BoardQuadrant(ofRectangle rect) {
    this->rect = rect;
    this->color = ofColor(ofRandom(256), ofRandom(256), ofRandom(256));
}

void BoardQuadrant::draw() {
    ofSetColor(this->color);
    ofRect(this->rect);
}

void BoardQuadrant::update(float deltatime) {
    for(vector<Player*>::iterator it = (*(this->players)).begin(); it != (*(this->players)).end(); ++it) {
        Player* player = (Player *)*it;
        this->contains_player = this->rect.inside(player->pos);
        if (this->contains_player) { break; }
    }
    
    if (this->contains_player) {
        for(vector<BulletPattern*>::iterator it = this->pattern_group->patterns.begin(); it != this->pattern_group->patterns.end(); ++it) {
            BulletPattern* current = (BulletPattern *)*it;
            for(vector<Bullet>::iterator it2 = current->bullets.begin(); it2 != current->bullets.end(); ++it2) {
                Bullet* current = (Bullet *)(&(*it2));
                if (this->rect.inside(current->pos)) {
                    for(vector<Player*>::iterator it3 = (*(this->players)).begin(); it3 != (*(this->players)).end(); ++it3) {
                        Player* player = (Player *)*it3;
                        if ((player->pos-current->pos).length() < player->hitbox_radius) {
                            cout << "touch " << ofRandom(10) << endl;
                            this->delegate->collided(current);
                        }
                    }
                }
            }
        }
    }
}

void BoardQuadrant::setPlayersReference(vector<Player*>* players) {
    this->players = players;
}

void BoardQuadrant::setGroupReference(BulletPatternGroup *pattern_group) {
    this->pattern_group = pattern_group;
}