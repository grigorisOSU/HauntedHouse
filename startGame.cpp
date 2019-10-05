/************************************************************
**Author: Sarkis Grigorian
**Email: grigoris@oregonstate.edu
**Username: grigoris
**CS 162 - Final
**Date: 6/11/2019
**Description: This is the startGame file that creates
**6 spaces and sets connected directions of each of the spaces.
**This file also prints out the users current status after
**every interaction/move is complete. It also checks to see
**if the user is alive or dead.
*************************************************************/

#include <iostream>
#include "Player.hpp"
#include "Space.hpp"
#include "Lobby.hpp"
#include "Kitchen.hpp"
#include "Elevator.hpp"
#include "Hallway.hpp"
#include "Bar.hpp"
#include "HotelRoom.hpp"
#include "startGame.hpp"
#include "inputVal.hpp"

using std::cout;
using std::cin;
using std::endl;


//creates and starts the game
void startGame()
{

    bool alive = true;
    bool newGame = true;
    bool sameRoom = true;

    //creates user object
    Player ply;

    //user location
    Space * playerLoc;

    //user space locations
    Space * lobby = new Lobby;
    Space * kitchen = new Kitchen;
    Space * elevator = new Elevator;
    Space * bar = new Bar;
    Space * hallway = new Hallway;
    Space * hotelroom = new HotelRoom;

    Space * NL = NULL;


    //sets the directions for each space
    //Order: Top, Left, Right, Bottom
    bar->setLocations(NL, NL, lobby, kitchen);
    lobby->setLocations(hallway, bar, elevator, NL);
    elevator ->setLocations(NL, lobby, NL, NL);
    hallway->setLocations(hotelroom, NL, NL, lobby);
    hotelroom ->setLocations(NL, NL, NL, hallway);
    kitchen->setLocations(NL, NL, NL, bar);



    //does following while user is alive and has not won
    while (alive && !ply.getWinStatus())
    {

        //displays following message if new game.
        if (newGame)
        {
            playerLoc = bar;
            playerLoc->story(ply);

            newGame = false;
        }

        //prints user stats
        cout << endl << endl;
        cout << "*******************************************\n";
        cout << "              CURRENT STATS                \n";
        cout << "PLAYER : " << ply.getName() << endl;
        cout << "CURRENT LOCATION: " << playerLoc->getspaceName() << endl;
        cout << "HEALTH REMAINING: " << ply.getHealth() << endl;
        cout << "*******************************************\n\n";

        cout << endl << "What would you like to do?" << endl;
        playerLoc->printInteraction();

        char direc = direction();

        /*The following switch statement allows the takes in the users
        //directional input. If user inputs 'b' then their backpack contents
        //will be printed. If user inputs directional keys (w,a,s,d) if the
        //corresponding space is a location, it moves the character. If the
        //directional input is not a space/NULL it interacts with the room
        //that the user is currently in*/
        switch(direc)
        {
        case 'w': case 'W':
            {
            if (playerLoc->top == NULL)
            {
                playerLoc->roomInteract('w', ply);
                sameRoom = true;
            }

            else
            {
                playerLoc = playerLoc ->top;
                sameRoom = false;
                ply.takeHealth(5);
            }
            }
            break;
        case 'a': case 'A':
            {
            if (playerLoc->left == NULL)
            {
                playerLoc->roomInteract('a', ply);
                sameRoom = true;
            }
            else
            {
                playerLoc = playerLoc -> left;
                sameRoom = false;
                ply.takeHealth(5);
            }
            }
            break;
        case 'd': case 'D':
            {
            if (playerLoc->right == NULL)
            {
                playerLoc->roomInteract('d', ply);
                sameRoom = true;
            }
            else
            {
                playerLoc = playerLoc -> right;
                sameRoom = false;
                ply.takeHealth(5);
            }
            }
            break;
        case 's': case 'S':
            {
            if (playerLoc->bottom == NULL)
            {
                playerLoc->roomInteract('s', ply);
                sameRoom = true;
            }
            else
            {
                playerLoc = playerLoc -> bottom;
                sameRoom = false;
                ply.takeHealth(5);
            }
            }
            break;

        case 'b': case 'B':
            {
                ply.checkBag();
                sameRoom = true;
            }
            break;
        }

        //if user has just entered the room start story
        if (!sameRoom)
        {
        playerLoc ->story(ply);
        }

        //if users health drops below 0, user dies.
        if (ply.getHealth() <= 0)
        {
            alive = false;
        }
    }

    //if user has died prints the following message.
    if (!alive && !ply.getWinStatus())
    {
        cout << endl << endl << endl << endl;
        cout << "************************************************\n"
                "             *YOU HAVE DIED*                    \n";
        cout << "Better luck next time, " << ply.getName() << "  \n";
       cout <<  "************************************************\n";

    }

    //if player wins/escapes displays the following message
    if (ply.getWinStatus())
    {
        cout << endl << endl << endl << "Congrats on finishing the game!" << endl;
    }

    //sets space pointers to NULL and deletes spaces
    bar->setLocations(NL, NL, NL, NL);
    lobby->setLocations(NL, NL, NL, NL);
    elevator ->setLocations(NL, NL, NL, NL);
    hallway->setLocations(NL, NL, NL, NL);
    hotelroom ->setLocations(NL, NL, NL, NL);
    kitchen -> setLocations(NL,NL,NL,NL);

    delete bar;
    delete lobby;
    delete elevator;
    delete hallway;
    delete hotelroom;
    delete kitchen;

}

