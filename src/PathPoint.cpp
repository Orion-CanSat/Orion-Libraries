#include "Orion/Utilities/FlightController/PathPoint.hpp"

using namespace Orion::Utilities::FlightController;

PathPoint::PathPoint(decPlace x, decPlace y)
{
    this->x = x;
    this->y = y;
}

decPlace PathPoint::getX() { return this->x; }
decPlace PathPoint::getY() { return this->y; }
decPlace PathPoint::getPolarAngle() { return atan2(this->y, this->x); }

decPlace PathPoint::getPolarAngleTo(PathPoint point)
{ 
    decPlace dx = point.getX() - this->x;
    decPlace dy = point.getY() - this->y;
    return atan2(dy, dx);
}