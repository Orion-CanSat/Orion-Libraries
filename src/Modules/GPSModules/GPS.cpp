#include "Modules/GPSModules/GPS.hpp"

using namespace Orion::Modules::GPSModules;

decPlace GPS::GetDistance(Coordinates& a, Coordinates& b)
{
    const uint64_t R = 6371e3;

    const decPlace phi1 = a._latitude * PI / 180;
    const decPlace phi2 = b._latitude * PI / 180;

    const decPlace deltaPhi = (b._latitude - a._latitude) * PI / 180;
    const decPlace deltaLambda = (b._longitude - a._longitude) * PI / 180;

    const decPlace alpha = pow(sin(deltaPhi / 2), 2.0) + cos(phi1) * cos(phi2) * pow(sin(deltaLambda / 2), 2.0);
    const decPlace c = 2 * atan2f(sqrtf(alpha), sqrtf(1 - alpha));

    return R * c;
}

bool GPS::HasDataType(uint32_t type)
{
    switch (type)
    {
        case __LATITUDE__:
        case __LONGITUDE__:
        case __ALTITUDE__:
            return true;
        default:
            return false;
    }
}

decPlace GPS::GetData(uint32_t type)
{
    switch (type)
    {
        case __LATITUDE__:
            return _coordinates._latitude;
        case __LONGITUDE__:
            return _coordinates._longitude;
        case __ALTITUDE__:
            return _coordinates._altitude;
        default:
            return NAN;
    }
}