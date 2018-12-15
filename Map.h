#ifndef ASS3_MAP_H
#define ASS3_MAP_H

using namespace std;
#include <iostream>

/** The Map module represents the environment in which the robots move.
    The Map is represented by a two-dimensional array of 1's and 0's, And its size
    is constant (7X7) and is not expected to be change at runtime.
    The meaning 0's and 1's in array cells is to indicate whether a robot can be placed in this cell.
    "1" represents a wall meaning that a robot can not be placed. And "0" represents a cell where a robot can be placed.
**/
class Map {

private:
    int m_number;

public:
    int m_intArray[7][7];
    Map();
    ~Map();

    /**
 *  The method initializes the two-dimensional array cells according to an array obtained as a parameter.
 *  In addition, initialize the map number according to the int given to it.
    **/
    void SetMap(int Array[7][7], int number);

    /**
 *  The method summarized two maps, No future use of the new map. The two maps between which the connection
 *  operation is performed will remain unchanged. The value of the cells of the new map is determined by
 *  an OR operation between between the values of the two arrays respectively.
     **/
    Map operator+(const Map& other)const;

    /**
 *  The method summarized two maps, and makes placement of the received map to the map which called the method.
 *  The accepted map as a parameter performed will remain unchanged..
    **/
    void operator+=(const Map& other);

    /**
 *  The Map that calls this method becomes a deep copy of the param other.
 *  The accepted map as a parameter performed will remain unchanged..
    **/
    Map& operator=(const Map& other);

    /**
 *  The method returns true if the maps are with the exactly same passes and walls location.
 *  The map that calls the method as well as the map accepted as a parameter will remain unchanged.
    **/
    bool operator==(const Map& other)const;

    /**
 *  The function defines the correct form of printing for a Map object.
 *  The map accepted as a parameter will remain unchanged.
    **/
    friend ostream& operator<<(ostream& out, const Map& m);

    /**
 *  The method checks whether the given indexes are within the array boundaries.
 *  The map that calls the method wil remain unchanged.
    **/
    bool locationIsInArray(int x, int y)const;

    /**
 *  Method to check if there is 0 (pass) or 1 (wall) in specific index.
 *  The map that calls the method wil remain unchanged.
    **/
    bool locationIsValid(int x, int y)const;

/**
 * Simple get method
 */
    int GetNum() const;

};


#endif //ASS3_MAP_H