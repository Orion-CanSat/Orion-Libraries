#include "Utilities/FlightController/PID.h"

using namespace Orion::Utilities::FlightController;

PID::PID(decPlace P, decPlace I, decPlace D)
{
    this->P = P;
    this->I = I;
    this->D = D;
    this->previousError = 0;
    this->integral = 0;
    this->output = 0;
}

void PID::Update(decPlace error, decPlace dt)
{
    // Calculate Proportional.
    decPlace proportional = error * P;

    // Calculate Derivative.
    decPlace derivative = this->D * (error - this->previousError) / dt;
    this->previousError = error;

    // Calculate Integral.
    this->integral += error * dt;
    
    // Set the output.
    this->output = proportional + (this->I * this->integral) + derivative;
}

decPlace PID::GetOutput() { return output; }