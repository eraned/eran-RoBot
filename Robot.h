//
// Created by ERAN EDRI on 02/01/2018.
//

#ifndef ASS3_ROBOT_H
#define ASS3_ROBOT_H
using namespace std;
#include <iostream>
/**
 * Class robot represent an object that can be controled by the user with the game interface,
 * Robots object are located on the maps and they move on the maps coordinates according the map rulles.
 **/

class Robot {
    /**
        * every robot Object has three fields, His ID to separate him from the other robots
        * A one-dimensional array called Coordinates to represent its position on a map
        * A field MapNumber that represents the Map is located on.
     */
private:

    int ID;
    int Coordinates [2];
    int MapNumber;


public:
    Robot();
    Robot(int mapnumber, int coordintes[2], int id);
    ~Robot();
    friend ostream& operator<<(ostream& out, const Robot& r);
    void SetCoords(int x, int y);
    void SetId(int x);
    void SetMapNumber(int x);
    int GetMapNumber();
    int GetId();
    const int* GetCoords();
    friend bool CompareRobots(const Robot& r1,const Robot& r2);

};


#endif //ASS3_ROBOT_H