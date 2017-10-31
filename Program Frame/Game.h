#pragma once
#include <SDL\SDL.h>
#include "Renderer.h"
#include <tchar.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <memory>
#include <Windows.h>
#include <SDL\SDL_syswm.h>
#include <algorithm>
#include <vector>
#include <SDL\SDL_ttf.h>
#include <functional>
#include "Input.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:

	MainGame();
	~MainGame();

	void run();

	std::string Key;
	std::vector<std::string> KeyList;

	const Uint8 *KeyState;
	HANDLE output_handle;
	CONSOLE_SCREEN_BUFFER_INFO screeninfo = {};

	SDL_Color TextColor = {0,0,0, 255};
	TTF_Font *Font;

	SDL_Rect rect1, rect2;
	SDL_Texture *Texture1, *Texture2;
	SDL_Surface *Surface;

	/* New Experimental renderer class*/
	Renderer RendererClass;
	Text* MainInsert;
	Box* InsertBox;

	Text* FpsMeter;
	
	Input* InputClass;
	/*New InputClass for handling clicks and inserts*/

	/*New WIP Class for handling and using tasks similar to Courotine*/

	int ExtractTime(Box* B);
	struct tm tmTime;
	struct tm EndLine;
	int diffseconds;
	bool FocusState;
	short columns;
	short rows;
	bool TimeCreated = false;

	void SetHandle(HWND Handle) { WindowsHandle = Handle; }
	
private:
	void processInput();
	void gameLoop();

	HWND hApp;

	HWND WindowsHandle;

	int TextureWidth;
	int TextureHeight;

	int _screenWidth = 240;
	int _screenHeight = 160;
	GameState _gameState;

	char c;
	bool Typing;
	std::string stream;

};

