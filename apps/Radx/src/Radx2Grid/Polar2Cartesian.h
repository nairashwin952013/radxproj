
#ifndef Polar2Cartesian_h
#define Polar2Cartesian_h

#include "PolarDataStream.h"

class Polar2Cartesian
{
public:
    // constructor & destructor
    Polar2Cartesian(Repository* store);
    ~Polar2Cartesian();


    void calculateHeight();
    void calculateRoI();

    // this function called from outside
    void calculateCartesianCoords();


    // setter, getter
    float* getGateX();
    float* getGateY();
    float* getGateZ();
    float* getGateRoI();


private:
    Repository* _store;


};

#endif

