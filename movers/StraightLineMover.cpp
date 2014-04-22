#include "StraightLineMover.h"
#include "BulletPattern.h"

REGISTER_DEF_TYPE(StraightLineMover);
const string StraightLineMover::SLUG = "StraightLineMover";

StraightLineMover::StraightLineMover() : Mover()
{
}

StraightLineMover::StraightLineMover(ofVec2f direction)
    : Mover(direction, -1)
{
}

StraightLineMover::StraightLineMover(ofVec2f direction, float wavelength)
    : Mover(direction, wavelength)
{
}

StraightLineMover::StraightLineMover(BulletPattern *attached, ofVec2f direction, float wavelength)
    : Mover(attached, direction, wavelength)
{
}

void StraightLineMover::move(float timedelta) {
    this->attached->origin += this->direction;
}

string StraightLineMover::describe() {
    return Mover::_describe(StraightLineMover::SLUG);
}
