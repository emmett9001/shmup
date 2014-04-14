//
//  CyclicEllipseBulletPattern.h
//  shmup
//
//  Created by Emmett Butler on 1/13/14.
//
//

#ifndef __shmup__CyclicEllipseBulletPattern__
#define __shmup__CyclicEllipseBulletPattern__

#include <iostream>
#include "BulletPattern.h"

#endif /* defined(__shmup__CyclicEllipseBulletPattern__) */

class CyclicEllipseBulletPattern : public BulletPattern{
public:
    static const string SLUG;
    CyclicEllipseBulletPattern();
    CyclicEllipseBulletPattern(int count, ofVec2f origin);
    CyclicEllipseBulletPattern(int count, ofVec2f origin, float bulletspeed, float volley_timeout);
    void volley();
    string describe();
private:
    REGISTER_DEC_TYPE(CyclicEllipseBulletPattern);
};
