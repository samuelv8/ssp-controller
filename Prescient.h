#ifndef SSP_CONTROLLER_PRESCIENT_H
#define SSP_CONTROLLER_PRESCIENT_H

#include "Plant.h"
#include "PrintDefinitions.h"

/// Algorithm to find the best solution (shortest path) for a given plant edges realization by a breadth-first search.
/// Returns the total cost of this path.
double prescient(int u, int dest, Plant &plant, ofstream &fs);

#endif //SSP_CONTROLLER_PRESCIENT_H
