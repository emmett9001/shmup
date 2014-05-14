//
//  BulletPatternGroup.h
//  emptyExample
//
//  Created by Emmett Butler on 3/29/14.
//
//

#ifndef __emptyExample__BulletPatternGroup__
#define __emptyExample__BulletPatternGroup__

#include <iostream>
#include "ofMain.h"
#include "BulletPattern.h"

#endif /* defined(__emptyExample__BulletPatternGroup__) */

class Stage;

class BulletPatternGroup {
public:
    vector<BulletPattern *> patterns;
    bool paused;
    Stage *stage;

    BulletPatternGroup(Stage *stage);

    void update(float deltatime);
    void draw();
    float prepare();
    void addPattern(BulletPattern *pattern);
    void destroyAllBullets();
    void pause();
};
