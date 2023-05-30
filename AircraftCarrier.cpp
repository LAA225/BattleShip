#include "ship.h"
#include "ship.cpp"

using namespace std;

#ifndef AIRCRAFTCARRIER_CPP
#define AIRCRAFTCARRIER_CPP

class AircraftCarrier : public Ship
{
    vector<coordinate> hShape;
    vector<coordinate> vShape;
    char currentShape;

public:
    AircraftCarrier() : Ship("Aircraft Carrier", 'A', 5){}

    void defineShape(){
        hShape.push_back(coordinate(0, 0));
        hShape.push_back(coordinate(0, 1));
        hShape.push_back(coordinate(0, 2));
        hShape.push_back(coordinate(1, 1));
        hShape.push_back(coordinate(2, 1));

        vShape.push_back(coordinate(0, 2));
        vShape.push_back(coordinate(1, 2));
        vShape.push_back(coordinate(2, 2));
        vShape.push_back(coordinate(1, 0));
        vShape.push_back(coordinate(1, 1));

        shape = hShape;
        currentShape = 'h';
    }

    void changeOrientation()
    {
        if (currentShape == 'h')
        {
            shape = vShape;
            currentShape = 'v';
        }
        else
        {
            shape = hShape;
            currentShape = 'h';
        }
    }
};

#endif