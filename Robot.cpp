//
// Created by ERAN EDRI on 02/01/2018.
//
#include <iostream>
#include "Robot.h"

/**
 * Default CONSTRUCTOR
 */
Robot::Robot() {
}

/**
 * second CONSTRUCTOR
 * create new Robot object Initialized with MapNumber and first location on the map ans set new Id for the new Robot
 */

Robot::Robot(int mapnumber, int  coordintes [2], int id) {
    ID=id;
    MapNumber=mapnumber;
    Coordinates[0]=coordintes[0];
    Coordinates[1]=coordintes[1];
}

/**
 * DESTRUCTOR
 */
Robot::~Robot() {

}

int Robot::GetMapNumber(){
    return MapNumber;
};


/* Prints robot in format:<ID>_MAP:<NapNumber>_GPS:<X coord>,<Y coord> */
ostream& operator<<(ostream& out, const Robot& r)
{
    out<<r.ID<<" "<<"Map:"<<r.MapNumber<<" GPS:"<<r.Coordinates[0]<<","<<r.Coordinates[1]<<endl;
    return out;
}

const int *Robot::GetCoords() {
    return Coordinates;
}

int Robot::GetId() {
    return ID;
}

void Robot::SetCoords(int x, int y) {
    Coordinates[0] = x;
    Coordinates[1] = y;
}

void Robot::SetId(int x) {
    ID = x;
}

void Robot::SetMapNumber(int x) {
    MapNumber = x;
}






