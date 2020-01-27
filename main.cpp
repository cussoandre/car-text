#include <iostream>
using namespace std;

#define WIDTH 10
#define HEIGHT 32

#define CHANCE 3

#define NUMOBST 5

#define ROAD 46
#define CAR 94
#define CLEAR 0

const char obscodes[NUMOBST] = {'X','Z','L','O','M'};

struct map {
	char charmap[HEIGHT][WIDTH];
};

struct obst {
	char charmap[WIDTH];
};

typedef map *pointmap;

char screen[WIDTH][HEIGHT];

map initScreen()
{
	map newScreen = *(new map);
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			newScreen.charmap[i][j] = ROAD;
		}
	}
	return newScreen;

}

obst newRandomObst ()
{
	int obstcode = CLEAR;
	obst *tmp = new obst;

	for (int j = 0; j < WIDTH; j++)
	{
		obstcode = rand()%(NUMOBST*CHANCE);
		if (obstcode%CHANCE != 0) tmp->charmap[j] = obstcode % CHANCE;
		obstcode = CLEAR;
	}
	return *tmp;
}

map updateScreen(map actualScreen, obst obstacles, int carW, int carH)
{
	map tmpScreen = actualScreen;
	for (int i = 1; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			tmpScreen.charmap[i-1][j] = actualScreen.charmap[i][j];
			//newScreen.charmap[i][j] = ROAD;
			if ((i == carH) && (j == carW)) tmpScreen.charmap[i][j] = CAR;
		}
	
	}

	for (int j = 0; j < WIDTH; j++)
	{
		if (obstacles.charmap[j] != CLEAR) tmpScreen.charmap[HEIGHT-1][j] = obstacles.charmap[j];
	}
	return tmpScreen;

}


void prntScr (map scr)
{
	
	for (int i = 0; i < HEIGHT+3; i++)
	{
	//	cout << i << "\t";
		
		cout << "\33[2K";
		cout << "\033[A";
		
		cout << "\33[2K";
	//	cout << "\n";
	}

//	cout << "\33[2J";

	for (int i = 0; i < HEIGHT; i++)
	{
		cout << i << "\t";
		
		for (int j = 0; j < WIDTH; j++)
		{
			cout << scr.charmap[i][j];
		}
		
		cout << "\n";
	}

}

int main()
{
	while (true)
	{
		map testMap;
		obst testObst;
	
		testMap = initScreen();
		testObst = newRandomObst();
	
		testMap = updateScreen(testMap, testObst, 3, 4);
	
		if (clock() % 500 == 0)
		{
			prntScr (testMap);
			cout << "\n \n \n";
	
		}
	}


}

