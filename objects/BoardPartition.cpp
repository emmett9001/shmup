//
//  BoardPartition.cpp
//  emptyExample
//
//  Created by Emmett Butler on 3/30/14.
//
//

#include "BoardPartition.h"
#include "Player.h"
#include "Stage.h"
#include "Camera.h"
#include "BoardQuadrant.h"

BoardPartition::BoardPartition(Stage *stage) {
    this->quads = vector<BoardQuadrant *>();
    this->stage = stage;
    this->quads.push_back(new BoardQuadrant(ofRectangle(stage->zero_point.x, stage->zero_point.y,
                                                        stage->camera->size.x/2, stage->camera->size.y/3)));
    this->quads.push_back(new BoardQuadrant(ofRectangle(stage->zero_point.x+stage->camera->size.x/2, stage->zero_point.y,
                                                        stage->camera->size.x/2, stage->camera->size.y/3)));
    this->quads.push_back(new BoardQuadrant(ofRectangle(stage->zero_point.x, stage->camera->size.y/3,
                                                        stage->camera->size.x/2, stage->camera->size.y/3)));
    this->quads.push_back(new BoardQuadrant(ofRectangle(stage->zero_point.x+stage->camera->size.x/2, stage->camera->size.y/3,
                                                        stage->camera->size.x/2, stage->camera->size.y/3)));
    this->quads.push_back(new BoardQuadrant(ofRectangle(stage->zero_point.x, 2*(stage->camera->size.y/3),
                                                        stage->camera->size.x/2, stage->camera->size.y/3)));
    this->quads.push_back(new BoardQuadrant(ofRectangle(stage->zero_point.x+stage->camera->size.x/2, 2*(stage->camera->size.y/3),
                                                        stage->camera->size.x/2, stage->camera->size.y/3)));
}

void BoardPartition::draw() {
    for(vector<BoardQuadrant*>::iterator it = this->quads.begin(); it != this->quads.end(); ++it) {
        BoardQuadrant *quad = (BoardQuadrant *)*it;
        quad->draw();
    }
}

void BoardPartition::update(float deltatime) {
    for(vector<BoardQuadrant*>::iterator it = this->quads.begin(); it != this->quads.end(); ++it) {
        BoardQuadrant *quad = (BoardQuadrant *)*it;
        quad->update(deltatime);
    }
}

void BoardPartition::setPlayersReference(vector<Player*>* players) {
    for(vector<BoardQuadrant*>::iterator it = this->quads.begin(); it != this->quads.end(); ++it) {
        BoardQuadrant *quad = (BoardQuadrant *)*it;
        quad->setPlayersReference(players);
    }
}

void BoardPartition::setGroupReference(BulletPatternGroup *pattern_group) {
    for(vector<BoardQuadrant*>::iterator it = this->quads.begin(); it != this->quads.end(); ++it) {
        BoardQuadrant *quad = (BoardQuadrant *)*it;
        quad->setGroupReference(pattern_group);
    }
}

void BoardPartition::setDelegate(BoardQuadrantCollisionDelegate *delegate) {
    for(vector<BoardQuadrant*>::iterator it = this->quads.begin(); it != this->quads.end(); ++it) {
        BoardQuadrant *quad = (BoardQuadrant *)*it;
        quad->collisionSubscribers.push_back(delegate);
    }
}
