#include "CyclicBoundedStraightLineMover.h"
#include "BulletPattern.h"

REGISTER_DEF_TYPE(CyclicBoundedStraightLineMover);
const string CyclicBoundedStraightLineMover::SLUG = "CyclicBoundedStraightLineMover";

CyclicBoundedStraightLineMover::CyclicBoundedStraightLineMover() : StraightLineMover()
{
}

CyclicBoundedStraightLineMover::CyclicBoundedStraightLineMover(ofVec2f direction, float wavelength)
    : StraightLineMover(direction, wavelength)
{
}

CyclicBoundedStraightLineMover::CyclicBoundedStraightLineMover(BulletPattern *attached, ofVec2f direction, float wavelength)
    : StraightLineMover(attached, direction, wavelength)
{
}

void CyclicBoundedStraightLineMover::move(float timedelta) {
    if ((this->attached->origin - this->origin).length() > this->wavelength) {
        this->direction *= -1;
    }
    this->attached->origin += this->direction;
}

string CyclicBoundedStraightLineMover::describe() {
    return Mover::_describe(CyclicBoundedStraightLineMover::SLUG);
}
