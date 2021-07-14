#ifndef SSP_CONTROLLER_CONTROLLER_H
#define SSP_CONTROLLER_CONTROLLER_H

#include "Plant.h"

/// Controller algorithm.
/// Receives the current vertex 'u', the destination 'dest' and a Plant 'plant' to return the next vertex to go (policy)
/// and changes the cost 'w' (by reference) of the step
int controller(int u, int dest, Plant &plant, double &w);

#endif //SSP_CONTROLLER_CONTROLLER_H
