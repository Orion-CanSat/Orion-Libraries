#include "Orion/Modules/CameraModules/Camera.hpp"

#include <stdio.h>

using namespace Orion::Modules::CameraModules;

Camera::Camera() { }

bool Camera::_pictureNamingFunction(char* output, uint32_t outputSize)
{
    snprintf(output, outputSize, "%d%s", this->_picturesTaken, (this->_fileType == NULL) ? "" : this->_fileType);
    return true;
}

void Camera::Update() { }

void Camera::Sleep() { }
void Camera::WakeUp() { }

Camera::~Camera() { }