//MOST RECENT SAVE
//Dungeon Crawler main file

//todo:
	//Restart option
	//3 files working properly



#include <iostream>
#include <conio.h> //for getch
#include <cstdlib> // for std::rand()
#include <string> // for strings
#include <time.h> //for time
#include <stdlib.h> //for null?
#include "function.h"
//0 = entrance
//1, 2, 3 = dirt
// 4, 5 = HPotion (+10 HP)
//6, 7, = Small trap (-5 HP)
//

using namespace std;

//variables
bool play = true;
string user = "";
const int yDim = 17;
const int xDim = 23;
const int yBorder = yDim + 2;
const int xBorder = xDim + 2;

int currentX = 0; //hero x position
int currentY = 0; //hero y position
int match = 0;
int knife = 0;
int HPotion = 0;
int health = 30;
int keys = 0;

char map[yBorder][xBorder];
int mapNum[yBorder][xBorder];
enum tile { ENTRANCE, DIRT, HPOTION, TRAP, KEY, EXIT };
enum hState { ALIVE, DEAD };
//hState hero = ALIVE;


int main() {
	while (play) {
		printInstructions();
		playGame();
		resetStats();

	}
}



