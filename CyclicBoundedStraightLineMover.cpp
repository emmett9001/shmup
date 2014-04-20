#include "CyclicBoundedStraightLineMover.h"
#include "BulletPattern.h"

CyclicBoundedStraightLineMover::CyclicBoundedStraightLineMover() : StraightLineMover()
{
}

CyclicBoundedStraightLineMover::CyclicBoundedStraightLineMover(ofVec2f direction, float wavelength)
    : StraightLineMover(direction), wavelength(wavelength)
{
}

CyclicBoundedStraightLineMover::CyclicBoundedStraightLineMover(BulletPattern *attached, ofVec2f direction, float wavelength)
    : StraightLineMover(attached, direction), wavelength(wavelength)
{
}

void CyclicBoundedStraightLineMover::move(float timedelta) {
    if ((this->attached->origin - this->origin).length() > this->wavelength) {
        this->direction *= -1;
    }
    this->attached->origin += this->direction;
}
