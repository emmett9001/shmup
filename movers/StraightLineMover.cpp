#include "StraightLineMover.h"
#include "BulletPattern.h"

const string StraightLineMover::SLUG = "StraightLineMover";

StraightLineMover::StraightLineMover() : Mover()
{
}

StraightLineMover::StraightLineMover(ofVec2f direction)
    : Mover(), direction(direction)
{
}

StraightLineMover::StraightLineMover(BulletPattern *attached, ofVec2f direction)
    : Mover(attached), direction(direction)
{
}

void StraightLineMover::move(float timedelta) {
    this->attached->origin += this->direction;
}

string StraightLineMover::describe() {
    return Mover::_describe(StraightLineMover::SLUG);
}
