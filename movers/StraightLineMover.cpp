#include "StraightLineMover.h"
#include "BulletPattern.h"

StraightLineMover::StraightLineMover()
{
}

StraightLineMover::StraightLineMover(BulletPattern *attached, ofVec2f direction) : Mover(attached), direction(direction)
{
}

void StraightLineMover::move(float timedelta) {
    this->attached->origin += direction;
}
