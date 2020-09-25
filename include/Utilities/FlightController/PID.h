#include "Orion.h"

namespace Orion
{
    namespace Utilities
    {
        namespace FlightController
        {
            class PID
            {
            public:
                PID(decPlace P, decPlace I, decPlace D);
                void Update(decPlace error, decPlace dt);
                decPlace GetOutput();
            private:
                decPlace P, I, D;
                decPlace previousError;
                decPlace integral;
                decPlace output;
            };
        }
    }
}