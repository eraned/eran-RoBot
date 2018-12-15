/** The Game module represents the management of the main mechanism of the game.
 *  Is the module that links between Map and Robot and provides the functionality required.
 *  Every game has two maps and two vectors containing robot objects.
 *  In addition, the module provides the user a menu that displays the functionality of the module and allows
 *  the user to choose the desired action.
**/

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "Game.h"

/**
 * Default constructor
 * Initializes both game maps with data provided
 */
Game::Game() {
    int FirstmapArray [7][7] = {
            /* CURRECT MAP VALUE */
            {1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1, 0, 1},
            {0, 0, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1}
    };

    int SecondmapArray [7][7]= {
            /* CURRECT MAP VALUES */
            {1, 1, 1, 0, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 1},
            {0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 0, 1, 1}
    };
    FirstMap.SetMap(FirstmapArray, 1);
    SecondMap.SetMap(SecondmapArray, 2);
    NumOfRobots = 1;
}

Game::~Game()
{
}

/**
 * A method that prints the list of robots on a particular map including "Lost robots".
 * The method uses an iterator that scans the robots in the general Vector and prints them only if their
 * MapNumber member matches the param.
 * @param mapnum A number representing the desires map number.
 */
/* Printing method for the operator << */
void Game::PrintMapRobots(int mapnum)
{
    vector<Robot>::iterator lostRobotIterator;
    for (lostRobotIterator=LostRobots.begin(); lostRobotIterator!=LostRobots.end(); ++lostRobotIterator){
        Robot tmp = *lostRobotIterator;
        if (tmp.GetMapNumber() == mapnum)
        {
            cout<<"Robot:";
            cout<<tmp;
        }
    }

    vector<Robot>::iterator it;
    for (it=RobotsArray.begin(); it!=RobotsArray.end(); ++it){
        Robot tmp = *it;
        if (tmp.GetMapNumber() == mapnum)
        {
            cout<<"Robot:";
            cout<<tmp;
        }
    }
    cout<<endl;
}

/**
 * In this Function we get a command from the user to add a robot, in order to add the robot
 * we need two data from the user. The number of the map where he wants to add the
 * robot and the second where the starting position to place the robot on the map.Then
 * the function checks whether the location is valid, We create a new robot with the
 * data thst we received and insert the new robot to the vector of robots.
 * Print the new robot Data  and raise the number of robots in the system
 * in order to keep the number of robots intact later on.
 * @param Mapnumber - A map number that represents which map the robot should be added to
 * @param Coordinates - Array that represent the new location the new robot should be located
 **/
void Game::AddRobot(int Mapnumber,int Coordinates [2]) {
    if (Mapnumber == 1 && FirstMap.locationIsValid(Coordinates[1], Coordinates[0]))
    {
        Robot newRobot = Robot(Mapnumber, Coordinates, NumOfRobots);
        RobotsArray.push_back(newRobot);
        cout<<"New Robot:";
        cout<<newRobot;
        NumOfRobots++;
        return;
    }
    if (Mapnumber == 2 && SecondMap.locationIsValid(Coordinates[1], Coordinates[0]))
    {
        Robot newRobot = Robot(Mapnumber, Coordinates, NumOfRobots);
        RobotsArray.push_back(newRobot);
        cout<<"New Robot:";
        cout<<newRobot;
        NumOfRobots++;
        return;
    }
    cout << "Invalid location\n";
}
/**
 * This method updates the robots belong to the map after it has been modified by an operator action
 * @param map - The modified map.
 */
void Game::UpdateRobots(const Map& map) {
    vector<Robot>::iterator it;
    for (it=RobotsArray.begin(); it!=RobotsArray.end();){
        Robot tmp;
        tmp=*it;
        if (tmp.GetMapNumber() == map.GetNum())
        {
            const int* tmpCoords = tmp.GetCoords();
            if (!map.locationIsValid(tmpCoords[1],tmpCoords[0]))
            {
                RobotsArray.erase(it);
            }
            else
                ++it;
        }
    }
}

/**
 * This method defines how robots are compared.
 * This method helps in printing robots in ascending order.
 * @param r1 - robot1 to compare.
 * @param r2 - robot2 to compare.
 * @return - true if r1<r2, false otherwise.
 */
bool CompareRobots(const Robot& r1, const Robot& r2) {
    if (r1.Coordinates[0] < r2.Coordinates[0])
        return true;
    else if (r1.Coordinates[0] == r2.Coordinates[0]) {
        if (r1.Coordinates[1] < r2.Coordinates[1])
            return true;
        else if (r1.Coordinates[1] == r2.Coordinates[1])
            return (r1.ID < r2.ID);
        else
            return false;
    }
    else
        return false;
}

/**
 * In this function we receive a command from the user to move a certain robot on the
 * map, the data we receive from the user is the id of the robot and which
 * direction it should move on, first we must search for the robot in order to move it and
 * check the possibility of its movement, if the new location is on the map and free of walls we update the new robot to move there
 * using update the location field. If the robot need to move to location that containes walls
 * he stay in place, if the robot need to move outside the map, it is defined as a robot that
 * leaves the map and pushed to a vector of robots that have left the map.
 * @param id - Robot id to move
 * @param direction - char parameter from the user that represent which direction the robot should move
 **/
void Game::MoveRobot(int id, char direction) {
    int Xcor;
    int Ycor;
    int MapNum = 0;
    vector<Robot>::iterator MoveIterator;
    for (MoveIterator=RobotsArray.begin(); MoveIterator != RobotsArray.end(); ++MoveIterator) {
        if (MoveIterator.base()->GetId() == id) {
            Xcor = MoveIterator.base()->GetCoords()[0];
            Ycor = MoveIterator.base()->GetCoords()[1];
            MapNum = MoveIterator.base()->GetMapNumber();
            break;
        }
    }
    if (MoveIterator.base()->GetId() != id){
        cout<<"Requested robot num do not found"<<endl;
        return;
    }
    Map RobotsMap;
    if (MapNum == 1)
        RobotsMap = FirstMap;
    else if (MapNum == 2)
        RobotsMap = SecondMap;

        if (direction == 'U')
            Ycor = Ycor-MOVE_LENGTH;
        if (direction == 'D')
            Ycor = Ycor+MOVE_LENGTH;
        if (direction == 'L')
            Xcor = Xcor-MOVE_LENGTH;
        if (direction == 'R')
            Xcor = Xcor+MOVE_LENGTH;

        /* If the step removed the robot from the perimeter of the array */
    if (!RobotsMap.locationIsInArray(Xcor, Ycor)){
        MoveIterator.base()->SetCoords(-1, -1);
        LostRobots.push_back(*MoveIterator);
        RobotsArray.erase(MoveIterator);
    }
        /* The move is legal and the new location is available */
    else if (RobotsMap.locationIsValid(Xcor,Ycor)){
        MoveIterator.base()->SetCoords(Xcor, Ycor);
        cout<<"Robot:"<<*MoveIterator.base()<<endl;
    }
        /* The move is legal but the new location is not available */
    else
        cout<<"Robot:"<<*MoveIterator.base()<<endl;
}

/**
 * In this function we get a command from the user to delete one of the robots,we get his ID
 * Then we go over the robots vector and search for the robot. Once we find it, we
 * actually delete it from the vector and print the robot data that we erased.
 * @param id - Robots id to Delete.
 **/
void Game::DeleteRobot(int id) {

    vector <Robot>::iterator it= RobotsArray.begin();
    for(RobotsArray.begin();it != RobotsArray.end();++it){
        if(it.base()->GetId()==id){
            cout<<"Robot deleted:"<<*it.base()<<endl;
            RobotsArray.erase(it);
            return;
        }
    }
    cout << "Robot number do not exist or cannot be deleted (lost robot)" << endl;
}

void Game::Start() {
    bool gameOn = true;
    while (gameOn) {
        int Option;
        bool StilPlaying = true;
        while (StilPlaying) {
            cout << "Robot control menu:\n";
            cout << "1. Add robot\n";
            cout << "2. Delete Robot\n";
            cout << "3. Move Robot\n";
            cout << "4. Operator +\n";
            cout << "5. Operator +=\n";
            cout << "6. Operator =\n";
            cout << "7. Operator ==\n";
            cout << "8. Operator <<\n";
            cout << "9. Quit\n";
            cout << "Input your option:";

            cin >> (Option);

            switch (Option) {
                //Add robot
                case 1: {
                    int number;
                    int Xcor;
                    int Ycor;
                    int coordinates[2];
                    cout << "Enter MAP number:";
                    cin >> number;
                    while ((number!=1)&&(number!=2)){
                        cout << "Invalid map number:\n";
                        cout << "Please enter MAP number:";
                        cin >> number;
                    }
                    cout << "Enter coordinates (X,Y):";
                    cin >> Xcor;
                    cin >> Ycor;
                    while ((Xcor<0 || Xcor>6) || (Ycor<0 || Ycor>6)){
                        cout << "Invalid coords value:\n";
                        cout << "Please enter coordinated (X,Y):";
                        cin >> Xcor;
                        cin >> Ycor;
                    }
                    coordinates[0] = Xcor;
                    coordinates[1] = Ycor;
                    AddRobot(number, coordinates);
                    break;
                }

                    //Delete Robot
                case 2: {
                    int robotChoice;
                    cout << "Enter Robot number:";
                    cin >> robotChoice;
                    while (robotChoice<1) {
                        cout << "Invalid Robot number:\n";
                        cout << "Please enter Robot number:";
                        cin >> robotChoice;
                    }
                        DeleteRobot(robotChoice);
                    break;
                }


                    //Move Robot
                case 3:{
                    char Direction;
                    int id;
                    cout << "Enter Robot number:";
                    cin >> id;
                    cout << "Enter direction:";
                    cin >> Direction;
                    MoveRobot(id,Direction);
                    break;
                }

                    //Operator +
                case 4: {
                    Map tmp;
                    tmp = (FirstMap + SecondMap);
                    cout << tmp; // the result of sum
                    vector<Robot>::iterator it;
                    for (it = RobotsArray.begin(); it!=RobotsArray.end(); ++it) {
                        Robot tmpRobot = *it;
                        const int *tmpCoords = tmpRobot.GetCoords();
                        if (tmp.locationIsValid(tmpCoords[1], tmpCoords[0]))
                            cout << (*(it));
                    }
                        break;
                }

                    //Operator +=
                    case 5: {
                        int firstChoice;
                        int secondChoice;
                        cout << "Please enter MAP number on the left to the operator (1 or 2 is possible):";
                        cin >> firstChoice;
                        while ((firstChoice!=1)&&(firstChoice!=2)){
                            cout << "Invalid map number:\n";
                            cout << "Please enter MAP number:";
                            cin >> firstChoice;
                        }
                        cout << "Please enter MAP number on the right to the operator (1 or 2 is possible):";
                        cin >> secondChoice;
                        while ((secondChoice!=1)&&(secondChoice!=2)){
                            cout << "Invalid map number:\n";
                            cout << "Please enter MAP number:";
                            cin >> secondChoice;
                        }
                        if ((firstChoice == 1 && secondChoice == 1) || (firstChoice == 2 && secondChoice == 2))
                            break;
                        else if (firstChoice == 1 && secondChoice == 2) {
                            FirstMap += SecondMap;
                            UpdateRobots(FirstMap);
                        } else if (firstChoice == 2 && secondChoice == 1) {
                            SecondMap += FirstMap;
                            UpdateRobots(SecondMap);
                        } else
                            cout << "Not a Valid Option. \n";
                        break;
                    }

                    //Operator =
                    case 6: {
                        int firstChoice;
                        int secondChoice;
                        cout << "Please enter MAP number on the left to the operator (1 or 2 is possible):";
                        cin >> firstChoice;
                        while ((firstChoice!=1)&&(firstChoice!=2)){
                            cout << "Invalid map number:\n";
                            cout << "Please enter MAP number:";
                            cin >> firstChoice;
                        }
                        cout << "Please enter MAP number on the right to the operator (1 or 2 is possible):";
                        cin >> secondChoice;
                        while ((secondChoice!=1)&&(secondChoice!=2)){
                            cout << "Invalid map number:\n";
                            cout << "Please enter MAP number:";
                            cin >> secondChoice;
                        }
                        if ((firstChoice == 1 && secondChoice == 1) || (firstChoice == 2 && secondChoice == 2))
                            break;
                        else if (firstChoice == 1 && secondChoice == 2) {
                            FirstMap = SecondMap;
                            UpdateRobots(FirstMap);
                        } else if (firstChoice == 2 && secondChoice == 1) {
                            SecondMap = FirstMap;
                            UpdateRobots(SecondMap);
                        } else
                            cout << "Not a Valid Option. \n";
                        break;
                    }

                    //Operator ==
                    case 7: {
                        if (FirstMap == SecondMap)
                            cout << "TRUE";
                        else
                            cout << "FALSE";
                        break;
                    }

                    //Operator <<
                    case 8: {
                        std::sort(LostRobots.begin(), LostRobots.end(), CompareRobots);
                        std::sort(RobotsArray.begin(), RobotsArray.end(), CompareRobots);
                        int mapChoice;
                        cout << "Please enter MAP number: ";
                        cin >> mapChoice;
                        while ((mapChoice!=1)&&(mapChoice!=2)){
                            cout << "Invalid map number:\n";
                            cout << "Please enter MAP number:";
                            cin >> mapChoice;
                        }
                        cout << endl;
                        if (mapChoice == 1) {
                            cout << "MAP" << mapChoice << endl << endl;
                            cout << FirstMap;
                            PrintMapRobots(1);
                        }
                        else if (mapChoice == 2) {
                            cout << "MAP" << mapChoice << endl << endl;
                            cout << SecondMap;
                            PrintMapRobots(2);
                            cout<<endl;
                        }
                        else {
                            cout << "Not a Valid Option. \n";
                            break;
                        }
                        break;
                    }

                    //Quit game
                    case 9: {
                        StilPlaying = false;
                        gameOn = false;
                        break;
                    }

                    default: {
                        cout << "Not a Valid Option. \n";
                        cout << "Please choose again.\n\n";
                        usleep(2000000);
                        break;
                    }
                }
            }
        }
    }




