//
// Created by ERAN EDRI on 02/01/2018.
//
#ifndef ASS3_GAME_H
#define ASS3_GAME_H
#include <vector>
#include "Robot.h"
#include "Map.h"

#define MOVE_LENGTH 1

class Game {

private:
    vector<Robot> RobotsArray;
    vector<Robot> LostRobots;
    Map FirstMap;
    Map SecondMap;
    int NumOfRobots;


public:
     Game();
    ~Game();
    void Start();
    void PrintMapRobots(int MapNum);
    void AddRobot(int Mapnumber, int Coordinats [2]);
    void DeleteRobot(int id);
    void MoveRobot(int id, char direction);
    void UpdateRobots(const Map& map);
};


#endif //ASS3_GAME_H