#include <iostream>
#include "Game.h"
#include <map>
#include <vector>
#include "utilities.h"
using namespace std;



int main(int argc, char** argv)
{
	vector<string> ID_List;
	ID_List.push_back("juttu");
	Get_it(ID_List, "juttu");

	MainGame game;
	/*game.run();*/
	return 0;
}
