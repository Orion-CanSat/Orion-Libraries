#ifndef __ORION_MODULES_CAMERAMODULE_CAMERA_H__
#define __ORION_MODULES_CAMERAMODULE_CAMERA_H__

#include "Orion.h"
#include "Modules/Module.hpp"

#include <stdint.h>
#include <math.h>

namespace Orion
{
    namespace Modules
    {
        namespace CameraModules
        {
            class Camera : virtual public Module
            {
                protected:
                    const char* _fileType = "";
                    uint16_t _picturesTaken = 0;

                public:
                    Camera();

                    virtual bool _pictureNamingFunction(char*, uint32_t);

                    virtual void Update();

                    virtual void Sleep();
                    virtual void WakeUp();
                    
                    ~Camera();
            };
        }
    }
}

#endif//__ORION_MODULES_CAMERAMODULE_CAMERA_H__