#ifndef SSP_CONTROLLER_PRINTDEFINITIONS_H
#define SSP_CONTROLLER_PRINTDEFINITIONS_H

#define INIT 1
#define CTRL 2
#define PRSC 4
#define CTRL_PATH 8
// #define PRINT (INIT | CTRL | PRSC | CTRL_PATH)
#define PRINT 0

/// This file is used to define what to print in the file "graph.txt".
/// Options are:
/// INIT - initial graph edges;
/// CTRL - graph edges at each controller step;
/// PRSC - graph edges at each prescient step;
/// CTRL_PATH - controller policy (vertices).
/// For example, to print the initial graph edges and the controller policy, write above the following line:
/// #define PRINT (INIT & CTRL_PATH)


#endif //SSP_CONTROLLER_PRINTDEFINITIONS_H
