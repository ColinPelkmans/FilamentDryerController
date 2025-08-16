#ifndef SENSORS_H
#define SENSORS_H

#include "globals.h"

void setupSensors();
float ky028ToCelsius(int raw);

// getChamberTemp() and getBedTemp() are declared in globals.h

#endif