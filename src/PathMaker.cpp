#include "Orion/Utilities/FlightController/PathMaker.hpp"

using namespace Orion::Utilities::FlightController;

PathMaker::PathMaker(decPlace refrenceX, decPlace refrenceY, decPlace radius, int circleSteps, decPlace changeDistance)
{
    this->refrenceX = refrenceX;
    this->refrenceY = refrenceY;
    this->radius = radius;
    this->circleSteps = circleSteps;
    this->changeDistance = changeDistance;
}

decPlace PathMaker::getRefrenceX() { return this->refrenceX; }
decPlace PathMaker::getRefrenceY() { return this->refrenceY; }
decPlace PathMaker::getRadius() { return this->radius; }
int PathMaker::getCircleSteps() { return this->circleSteps; }
int PathMaker::getCurrentCircleSteps() { return this->currentCircleStep; }

void PathMaker::updateRefrence(decPlace refrenceX, decPlace refrenceY)
{
    this->refrenceX = refrenceX;
    this->refrenceY = refrenceY;
}

PathPoint PathMaker::getCurrentPoint()
{
    decPlace angle = (2 * PI) * ((decPlace)this->currentCircleStep / (decPlace)this->circleSteps);
    return PathPoint(cos(angle) * this->radius, sin(angle) * this->radius);
}

PathPoint PathMaker::updatePoint(decPlace distance)
{
    if (distance >= this->changeDistance)
        this->currentCircleStep = (this->currentCircleStep + 1) % this->circleSteps;
    return this->getCurrentPoint();
}