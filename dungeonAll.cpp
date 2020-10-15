//MOST RECENT SAVE
//Dungeon Crawler main file

//todo:
	//Restart option
	//3 files working properly


//#include "dunctions.h"
#include <iostream>
#include <conio.h> //for getch
#include <cstdlib> // for std::rand()
#include <string> // for strings
#include <time.h> //for time
#include <stdlib.h> //for null?

using namespace std;

//variables
static int steps = 0;
bool play = true;
string user;
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
hState hero = ALIVE;

/*********************************************/
//print number of keys, health, and resources
void printStats() {
	cout << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << endl;
	cout << "Keys: " << keys << endl;
	cout << "Steps: " << steps << endl;
	cout << "Health: " << health << endl;
	cout << "Resources: " << endl;
	if (match == 1) {
		cout << char(9) << "1 match" << endl;
	}
	else if (match > 2) {
		cout << char(9) << match << " matches" << endl;
	}
	else {
		cout << endl;
	}

	if (knife == 1) {
		cout << char(9) << "1 damaged knife" << endl;
	}
	else if (knife > 1) {
		cout << char(9) << knife << " damaged knives" << endl;
	}
	else {
		cout << endl;
	}
	cout << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << endl;
}

//set variables to defaults 
void resetStats() {
	currentY = yBorder - 1;
	currentX = xBorder - 1;
	match = 0;
	knife = 0;
	HPotion = 0;
	health = 30;
	keys = 0;
	hero = ALIVE;
}

//restart or exit the game after winning or losing
void gameOver() {
	string user;
	bool fourhead = true;
	cout << "Type 'replay' or 'exit'. " << endl;
	cin >> user;

	if (user == "replay" || user == "REPLAY" || user == "Replay") {
		cout << "This should be working....." << endl;
		fourhead = false;
	}
	else if (user == "exit" || user == "EXIT" || user == "Exit") {
		fourhead = false;
		play = false;
		exit(3);
	}

	while (fourhead) {
		cout << "Type 'replay' or 'exit', fourhead." << endl;
		cin >> user;
		if (user == "replay" || user == "REPLAY" || user == "Replay") {
			cout << "This should be working....." << endl;
			fourhead = false;
		}
		else if (user == "exit" || user == "EXIT" || user == "Exit") {
			fourhead = false;
			play = false;
		}
	}

}

//print number of keys left
void keysLeft() {
	int left = 3 - keys;
	if (left < 0) {
		cout << "You have enough to escape; find the exit!" << endl;

	}
	else {
		cout << left << " more to go!" << endl;
	}

}

//given good random variable, do something good
void goodLuck() {
	srand(time(NULL));
	int r = (rand() % 100 + 1);
	if (r % 4 == 0 || r % 5 == 0) {
		keys++;
		cout << "You found a key!" << endl;
		keysLeft();
	}
	if (r % 2 == 0) {
		match++;
		cout << "You found a match on the floor." << endl;
		cout << endl;

	}
	else if (r % 3 == 0) {
		HPotion++;
		cout << "You found a health potion. " << endl;
		cout << endl;
		health = health + 5;
	}
	else {
		cout << "You found an old knife on the ground. Maybe this will come in handy." << endl;
		cout << endl;
		knife++;
	}
}

//given good random variable, do something bad
void badLuck() {
	srand(time(NULL));
	int r = (rand() % 100 + 1);
	if (r % 5 || r % 4) { //knife
		if (knife >= 1) {
			cout << "You stumble upon a tripwire. You use your knife to be safe, but it isn't usable anymore." << endl;
			cout << endl;
			mapNum[currentY][currentX] = 84; // ascii for 'T'
			knife--;
		}
		else if (r % 2 == 0) {
			cout << "You trip on something in the darkness. A pile of boulders falls from the ceiling onto your back." << endl;
			cout << endl;
			health = health - 5;
			mapNum[currentY][currentX] = 84; // ascii for 'T'
		}
		else {
			cout << "You stumble on something in the darkness." << endl;
			cout << "You feel a sharp pain as an arrow is shot into your back." << endl;
			health = health - 7;
			mapNum[currentY][currentX] = 84; // ascii for 'T'
		}
	}
	else { //match
		if (match >= 1) {
			if (r % 2 == 0) {
				cout << "You hear a rustling in the darkness and light a match to see better." << endl;
				cout << "Whatever it was, it must be afraid of the ..." << endl;
				match--;
			}
			else if (r % 3 == 0) {
				cout << "You use a match to gather your surroundings." << endl;
				cout << "Lucky you did. You almost stepped in what looks like quicksand!" << endl;
				match--;
			}
			else {
				cout << "You use a match to gather your surroundings." << endl;
				cout << "Before you step, you see the glimmer of broken glass. Good thing you saw that!" << endl;
				match--;
			}

		}
		else if (r % 2 == 0) {
			cout << "You hear a rustling in the darkness and feel a sharp pain in your ankle." << endl;
			cout << "You shake off the beast that bit you, but the bite looks pretty deep..." << endl;
			health = health - 3;
			mapNum[currentY][currentX] = 84; // ascii for 'T'
		}
		else if (r % 3) {
			cout << "Your foot sinks into something soft. You start to fall deeper." << endl;
			cout << "Quicksand! Use as much strength as you can to climb out!" << endl;
			health = health - 10;
		}
		else {
			cout << "You look down to find your foot covered in blood, surrounded by broken glass." << endl;
			cout << "Hopefully the blood loss isn't too severe." << endl;
			health = health - 2;
		}
	}
}

//print the map, fourhead
void printMap() {

	printStats();

	for (int i = 0; i <= yBorder; i++) {
		for (int j = 0; j <= xBorder; j++) {
			cout << char(mapNum[i][j]);
			if ((i == 0 || i == yBorder) && j != xBorder) {
				cout << char(196);
			}
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}
}

//generate random variable for every move (WASD)
void generateRandom() { //generate random number and luck based on number
	system("CLS");
	int r = (rand() % 100 + 1);

	if (r % 9 == 0) {
		badLuck();
	}
	else if (r % 8 == 0) {
		goodLuck();
	}
	else {
		cout << endl;
		cout << endl;
	}

	if (health <= 0) {
		cout << endl;
		hero = DEAD;
	}
}

//if hero hits a wall, don't let them move
void hitWall() {
	system("CLS");
	cout << "You hit a wall. Try moving a different direction." << endl;
	cout << endl;
}

//move up
void moveW() { //move up if possible
	if (currentY <= 1) {
		currentY = 1;
		/**/
		hitWall();
		printMap();

	}
	else {
		mapNum[currentY][currentX] = 32; //remove 'H' from old spot
		currentY--;
		mapNum[currentY][currentX] = 72; // add 'H' to new spot
		/**/
		generateRandom();
		printMap();

	}

}

//move down
void moveS() { //move down if possible
	if (currentY >= yBorder - 1) {
		currentY = yBorder - 1;
		/**/
		hitWall();
		printMap();
	}
	else {
		mapNum[currentY][currentX] = 32; //remove 'H' from old spot
		currentY++;
		mapNum[currentY][currentX] = 72; // add 'H' to new spot
		/**/
		generateRandom();
		printMap();
	}
}


//move left
void moveA() { //move left if possible
	if (currentX <= 1) {
		currentX = 1;
		/**/
		hitWall();
		printMap();
	}
	else {
		mapNum[currentY][currentX] = 32; //remove 'H' from old spot
		currentX--;
		mapNum[currentY][currentX] = 72; // add 'H' to new spot
		/**/
		generateRandom();
		printMap();
	}

}

//move right
void moveD() { //move right if possible
	if (currentX >= xBorder - 1) {
		currentX = xBorder - 1;
		/**/
		hitWall();
		printMap();
	}
	else {
		mapNum[currentY][currentX] = 32; //remove 'H' from old spot
		currentX++;
		mapNum[currentY][currentX] = 72; // add 'H' to new spot
		/**/
		generateRandom();
		printMap();
	}
}

//fill tiles with defaults (borders and spaces
void fillTiles() { //fills mapNum array with blank map and borders

	//fill with numbers

	for (int i = 1; i <= yDim + 1; i++) { //0 = left border, yDim + 2 = right border
		for (int j = 1; j <= xDim + 1; j++) { //0 = top, xDim+2 = bottom
			//mapNum[i][j] = rand(seed) % 100 + 1;
			mapNum[i][j] = 32;
		}
	}

	//set edge boundaries
	for (int i = 0; i <= yBorder; i++) {
		for (int j = 0; j <= xBorder; j++) {
			if (i == 0 || i == yBorder) {
				mapNum[i][j] = 196; //horiz border
			}
			else if (j == 0 || j == xBorder) {
				mapNum[i][j] = 179; //vert border
			}
		}
	}

	//set corners
	mapNum[0][0] = 218; //ascii code for top-left
	mapNum[0][xBorder] = 191; //ascii code for top-right
	mapNum[yBorder][0] = 192; //ascii code for bottom-left
	mapNum[yBorder][xBorder] = 217; //ascii code for bottom-right
	mapNum[yBorder - 1][xBorder - 1] = 72; //ascii value for 'H'


}

//start the game: set defaults, call fillTiles() and printMap()
void startGame() { //fill map, set Hero position to bottom left, give instructions, print map
	hero = ALIVE;
	fillTiles();
	currentY = yBorder - 1;
	currentX = xBorder - 1;
	system("CLS");
	cout << "Move your hero using WASD." << endl;
	cout << endl;
	printMap();
}

//play the game (this used to be just my main but I was playing with the while loop)
void playGame() {
	hState hero = ALIVE;
	cout << "Type 'start' to begin..." << endl;
	cin >> user;
	if (user == "start" || user == "START" || user == "Start") {
		startGame();
	}

	while (hero == ALIVE) {
		if (_kbhit()) {
			char u = _getch(); //getchar

			switch (u) {
			case 'W':
			case 'w':
				steps++;
				moveW();
				break;
			case 'A':
			case 'a':
				steps++;
				moveA();
				break;
			case 'S':
			case 's':
				steps++;
				moveS();
				break;
			case 'D':
			case 'd':
				steps++;
				moveD();
				break;
			}
		}
		if (keys >= 3 && currentX == 1 && currentY == 1) {
			cout << "You won!" << endl;
			gameOver(); //restart or exit
		}
		else if (health <= 0) {
			hero = DEAD;
		}
	}
	cout << "You died!" << endl;
	gameOver();
}

//print the instructions I haven't written
void printInstructions() {

	cout << "You enter the dungeon from the bottom-right corner." << endl;
	cout << "The corner is in the top-left corner, but the door is locked." << endl;
	cout << "Find 3 keys scattered around the room in order to unlock the door." << endl;
	cout << "After finding 3 keys, get to the exit alive!" << endl;
}

int main() {
	while (play) {

		printInstructions();
		resetStats();
		playGame();

	}
}




