/** The Map module represents the environment in which the robots move.
    The Map is represented by a two-dimensional array of 1's and 0's, And its size
    is constant (7X7) and is not expected to be change at runtime.
    The meaning 0's and 1's in array cells is to indicate whether a robot can be placed in this cell.
    "1" represents a wall meaning that a robot can not be placed. And "0" represents a cell where a robot can be placed.
**/

#include <iostream>
#include "Map.h"

Map::Map() {
}

Map::~Map() {
}
/**
 *  The method initializes the two-dimensional array cells according to an array obtained as a parameter.
 *  In addition, initialize the map number according to the int given to it.
 *  @param Array - The array according to which the Map's array cells values are determined.
 *  @param number - The number by which the map number will be initialized.
 **/
void Map::SetMap(int Array[7][7], int number) {
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            m_intArray[i][j]=Array[i][j];
        }
    }
    m_number = number;
}

/**
 *  The method summarized two maps, No future use of the new map. The two maps between which the connection
 *  operation is performed will remain unchanged. The value of the cells of the new map is determined by
 *  an OR operation between between the values of the two arrays respectively.
 *  @param other - a reference to const Map that on the right to the operator +
 *  @return A map that is a result of the operator+ between 2 maps.
 **/
Map Map::operator+(const Map& other)const
{
    Map temp;
    int i;
    int j;
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 7; j++)
        {
            if ((this->m_intArray[i][j]==1) || (other.m_intArray[i][j]==1))
                temp.m_intArray[i][j]=1;
            else
                temp.m_intArray[i][j]=0;
        }
    }
    return temp;
}

/**
 *  The method summarized two maps, and makes placement of the received map to the map which called the method.
 *  The accepted map as a parameter performed will remain unchanged..
 *  @param other - a reference to const Map that on the right to the operator +=
 **/
void Map::operator+=(const Map &other)
{
    int i;
    int j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            if (other.m_intArray[i][j] == 1)
                this->m_intArray[i][j] = 1;
        }
    }
}

/**
 *  The Map that calls this method becomes a deep copy of the param other.
 *  The accepted map as a parameter performed will remain unchanged..
 *  @param other - a reference to const Map that on the right to the operator =
 *  @return A reference to the map that called the method, this map has been changed to be a deep copy of other.
 **/
Map &Map::operator=(const Map &other) {
    int i;
    int j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            m_intArray[i][j] = other.m_intArray[i][j];
        }
    }
}

/**
 *  The method returns true if the maps are with the exactly same passes and walls location.
 *  The map that calls the method as well as the map accepted as a parameter will remain unchanged.
 *  @param other - A reference to const Map that on the right to the operator ==
 *  @return bool - True if both maps are exactly the same, False otherwise.
 **/
bool Map::operator==(const Map &other) const {
    int i;
    int j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            if(m_intArray[i][j] != other.m_intArray[i][j])
                return false;
        }
    }
    return true;
}

/**
 *  The method defines the correct form of printing for a Map object.
 *  The map accepted as a parameter will remain unchanged.
 *  @param m - A reference to const Map to be printed
 *  @return osteram - Will allow threading of prints.
 **/
ostream& operator<<(ostream& out, const Map& m)
{
    int i;
    int j;
    for (i = 0; i < 7; i++)
    {
        out<<'[';
        for (j = 0; j < 6; j++)
        {
            out << m.m_intArray[i][j] << " ";
        }
        out << m.m_intArray[i][6] << "]" << endl;
    }
    out<<endl;
    return out;
}

/**
 *  The method checks whether the given indexes are within the array boundaries.
 *  The map that calls the method wil remain unchanged.
 *  @param x - Refers to the array columns
 *  @param y - Refers to the array rows
 *  @return bool - True if the indexes are within the array boundaries. False otherwise.
 **/
bool Map::locationIsInArray(int x, int y) const {
    if (x < 0 || x > 6 || y <0 || y > 6)
        return false;
    return true;
}

/**
 *  Method to check if there is 0 (pass) or 1 (wall) in specific index.
 *  The map that calls the method wil remain unchanged.
 *  @param x - Refers to the array columns
 *  @param y - Refers to the array rows
 *  @return bool - True if the appropriate cell is free to position a robot. False otherwise.
 **/
bool Map::locationIsValid(int x, int y)const {
    if (!locationIsInArray(x, y))
        return false;
    if ((m_intArray[x][y] != 0) || !locationIsInArray(x, y))
        return false;
    return true;
}

/**
 * Simple get method
 */
int Map::GetNum() const {
    return m_number;
}



