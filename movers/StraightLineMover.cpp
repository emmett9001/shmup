#include "StraightLineMover.h"
#include "BulletPattern.h"

StraightLineMover::StraightLineMover() : Mover()
{
}

StraightLineMover::StraightLineMover(ofVec2f direction) : Mover(), direction(direction)
{
}

StraightLineMover::StraightLineMover(BulletPattern *attached, ofVec2f direction) : Mover(attached), direction(direction)
{
}

void StraightLineMover::move(float timedelta) {
    this->attached->origin += direction;
}
