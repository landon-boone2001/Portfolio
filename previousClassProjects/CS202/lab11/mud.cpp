// mud.cpp
/* This program will read in a file of rooms provided on the command line. The program will then allocate memory
for an array the size of the total number of rooms created from the struct room that will store the information from the room file names roomArrayPtr.
Once each value from the Room file is stored to its respective location in the room array, ifstream will close. The program will then take inputs "q", "l", "n",
"e", "s", "w". "q" will provide the message "Quitting..." and exit the program. "l" will provide information on the current room: the room's title,
the room's description, and possible exits of the room. "n", "e", "s", and "w" will move the player to the room north, east, south, or west of the current room
respectively. If a room as no exit in a certain direction, the program will output <You can't go DIRECTION!> and ask for another input.
Otherwise, if a player is able to enter a room, upon the command, the program will output <"You moved DIRECTION."> and change the player's 
current room to the next room's index. When the program closes, the program will automatically delete the roomArrayPtr*/
// Landon Boone
// 5/08/22
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;

struct room {
    string title;
    string desc;
    int exitDir[4] = {0,0,0,0}; // N, E, S, W 
    int nextRoomIndex[4] = {-1,-1,-1,-1}; // ExitDir N, E, S, W 's room index - I set the default values to -1 as no room index can be below 0.
};

class Room {

    public:
    //I created the function totalRoomNum in order to find the total number of rooms in the given room file. I did this in order to find the size
    // of roomArrayPtr, as its space is dynamically allocated based on the total number of rooms returned by this function.
    int totalRoomNum(string inFile) {
        ifstream fin;
        int totalRooms;   
        int tildeCount = 0;
        string tildeCounter;
        string storeString;
        fin.open(inFile);
        // I used the getline function here in order to read the file line-by-line and temporarily store each line as the string
        // "tildeCounter". If the line is a ~ line, the tildeCount will rise by 1. This is done to get a total number of rooms.
        while (getline(fin,tildeCounter)) {
            if (tildeCounter.compare("~") == 0) {
                tildeCount++;
            }
        }
        totalRooms = tildeCount/3;
        fin.close();
        return totalRooms;
    }
    // I decided to create a separate function to store information to roomArrayPtr. I did this in order to prevent confusion on variables used
    // and to try and keep everything that is related to storage separate.
    void readTheRoom(string inFile, int totalRooms, room* roomArrayPtr) {
        ifstream fin;
        stringstream stringToInt;
        string tempString;
        int i = 0;  
        string storeString;
        char direction;
        int exitNum;
        fin.open(inFile);
        for (i = 0; i < totalRooms; i++) {
            while (getline(fin,storeString)) {
                if (storeString.compare("~") == 0) {
                    break;
                }
                else {
                    roomArrayPtr[i].title = storeString;
                }
            }
            while (getline(fin,storeString)) {
                if (storeString.compare("~") == 0) {
                    break;
                }
                else {
                    roomArrayPtr[i].desc += storeString + "\n";
                }
            }
            while (getline(fin,storeString)) {
                if (storeString.compare("~") == 0) {
                    break;
                }
                else {
                    tempString = storeString.substr(2,3);
                    exitNum = stoi(tempString);
                    direction = storeString[0];
                    switch(direction) {
                        case 'n' :
                            roomArrayPtr[i].exitDir[0] = 1;
                            roomArrayPtr[i].nextRoomIndex[0] = exitNum;
                            break;
                        case 'e' :
                            roomArrayPtr[i].exitDir[1] = 1;
                            roomArrayPtr[i].nextRoomIndex[1] = exitNum;                         
                            break;
                        case 's' :
                            roomArrayPtr[i].exitDir[2] = 1;
                            roomArrayPtr[i].nextRoomIndex[2] = exitNum;                          
                            break;        
                        case 'w' :
                            roomArrayPtr[i].exitDir[3] = 1;
                            roomArrayPtr[i].nextRoomIndex[3] = exitNum;                        
                            break;
                    }
                }
            }
        }
        fin.close();
    }
    /* I decided to create a separate function for the "l" command in order to both keep the main() as "tidy" as possible and to be able to 
        concisely take the roomArrayPtr and current room.*/
    void takeALook(room* roomArrayPtr, int currentRoom) {
        string exits;
        cout << roomArrayPtr[currentRoom].title << endl;
        cout << roomArrayPtr[currentRoom].desc << endl;
        if (roomArrayPtr[currentRoom].exitDir[0] == 1) {
            exits += "n " ;
        }
        if (roomArrayPtr[currentRoom].exitDir[1] == 1) {
            exits += "e " ;
        }
        if (roomArrayPtr[currentRoom].exitDir[2] == 1) {
            exits += "s " ;
        }
        if (roomArrayPtr[currentRoom].exitDir[3] == 1) {
            exits += "w " ;
        }                       
        cout << "Exits: " << exits << endl; 
    }
};
/*I decided to keep my movements in my main() in order to cut down on making more switch statements cluttering
 the programthan necessary. Likewise, creating a separate move function would be more difficult to implement, as keeping all the "index changes"
 of roomArrayPtr in the main() is easier to read and track personally*/
int main(int argc, char **argv) {
    Room obj;
    string inFile = argv[1] ;
    int totalRooms = obj.totalRoomNum(inFile);
    room* roomArrayPtr = new room[totalRooms];
    obj.readTheRoom(inFile,totalRooms, roomArrayPtr) ;
    int currentRoom = 0;
    bool running = true;
    char command;
    while (running) {
        cout  << "> " ;
        cin >> command; 
        switch (command) {
            case 'q' :
                cout << "Quitting..." << endl ;
                running = false; 
                break;
            case 'l' :
                obj.takeALook(roomArrayPtr, currentRoom) ;
                break;
            case 'n' :
                if (roomArrayPtr[currentRoom].exitDir[0] == 1) {
                    cout << "You moved NORTH." << endl ;
                    currentRoom = roomArrayPtr[currentRoom].nextRoomIndex[0];                  
                }
                else {
                    cout << "You can't go NORTH!" << endl;
                }
                break;
            case 'e' :
                if (roomArrayPtr[currentRoom].exitDir[1] == 1) {
                    cout << "You moved EAST." << endl ;
                    currentRoom = roomArrayPtr[currentRoom].nextRoomIndex[1];   
                }
                else {
                    cout << "You can't go EAST!" << endl;
                }
                break;
            case 's' :
                if (roomArrayPtr[currentRoom].exitDir[2] == 1) {
                    cout << "You moved SOUTH." << endl ;
                    currentRoom = roomArrayPtr[currentRoom].nextRoomIndex[2];
                }
                else {
                    cout << "You can't go SOUTH!" << endl;
                }
                break;        
            case 'w' :
                if (roomArrayPtr[currentRoom].exitDir[3] == 1) {
                    cout << "You moved WEST." << endl ;
                    currentRoom = roomArrayPtr[currentRoom].nextRoomIndex[3];     
                }
                else {
                    cout << "You can't go WEST!" << endl;
                }
                break;
                    
        }
    }
    delete[] roomArrayPtr;
    return 0;
}
