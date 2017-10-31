#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>
#include <iostream>
#include <chrono>

using std::vector;
using std::cout;
using std::string;

enum TextureType
{
	TextType,
	SolidType,
	BoxType,
	CheckBoxType,
};


enum Boxtype
{
	Filled,
	Empty,
	Insert,
	Button,
};

class Texture
{
public:

	string Name;
	SDL_Rect Rect;
	SDL_Renderer* RenderObject;
	SDL_Window* WindowObject;

	Texture(){}
	virtual ~Texture() { }
	Texture(SDL_Renderer* _RenderObject, SDL_Window* _WindowObject, TextureType Type) { RenderObject = _RenderObject; WindowObject = _WindowObject; _Type = Type; }

	SDL_Surface* Surface() { return _Surface; }
	void Surface(SDL_Surface* Surface) { _Surface = Surface; }

	SDL_Texture* TextureData() { return _Texture; }
	void TextureData(SDL_Texture* Texture) { _Texture = Texture; }

	virtual void Update(){}

	TextureType GetType() { return _Type; }
	void GetType(TextureType Type) { _Type = Type; }

private:
	SDL_Surface* _Surface;
	SDL_Texture* _Texture;
	TextureType _Type;
};

class Renderer
{
public:
	Renderer();
	~Renderer();
	std::chrono::system_clock::time_point StartTime;

	SDL_Renderer* RendererObject;
	SDL_Window* WindowObject;
	
	vector<Texture*> TextureList;

	
	Texture* AddToRenderer(TextureType Type, SDL_Rect Rect, string Name);
	Texture* AddToRenderer(Boxtype Type, SDL_Rect Rect, string Name);
	Texture* AddToRenderer(TextureType Type, SDL_Rect Rect, int Size, string Name);

	void Render();

	int Frames = 0;
	int TotalLastFrames;
	void GetFps()
	{
		Frames += 1;
		std::chrono::duration<double> Seconds = std::chrono::system_clock::now() - StartTime;
		double c = (double)Seconds.count();

		if (c > 1)
		{
			StartTime = std::chrono::system_clock::now();
			TotalLastFrames = Frames;
			Frames = 0;
		}
	}
	//string GetLine(int index);
	//void SetRectangle(int index, SDL_Rect Rectangle);
	//void ChangeLine(int index, char Key);
	//void BackspaceLine(int index);
	//void NewTexture(TextureType Type, string Name, SDL_Rect Rect);
	//void AddToRenderer(Texture NewTexture);
};


class Text : public Texture
{
public:
	Text() 
	{
		TTF_Init(); Line = ""; 
		_Font = TTF_OpenFont("arial.ttf", 18); 
		_TextColor = { 0, 0, 0, 255 };
	}
	Text(SDL_Renderer* RenderObject, SDL_Rect Rect, string Name)
	{
		Texture::Rect = Rect;
		Texture::Name = Name;
		Texture::GetType(TextureType::TextType);
		Texture::RenderObject = RenderObject;
		TTF_Init(); Line = ""; 
		_Font = TTF_OpenFont("arial.ttf", 18); 
		_TextColor = { 0, 0, 0, 255 };
	}
	void Update() override
	{
		Texture::Surface(TTF_RenderText_Shaded(_Font, Line.c_str(), _TextColor, SDL_Color{ 255,255,255,255 }));
		Texture::TextureData(SDL_CreateTextureFromSurface(Texture::RenderObject,Texture::Surface()));
		SDL_QueryTexture(Texture::TextureData(), NULL, NULL, &Texture::Rect.w, &Texture::Rect.h);
		SDL_FreeSurface(Texture::Surface());
	}

	string PushBack(char Key)
	{
		Line.push_back(Key);
		return Line;
	}
	string Backspace()
	{
		Line = Line.substr(0, Line.size() - 1);
		return Line;
	}

	string Replace(std::string NewLine)
	{
		Line = NewLine;
		return Line;
	}
private:
	TTF_Font* _Font;
	SDL_Color _TextColor;
	string Line;
};

class Box : public Texture
{
public:
	
	//Constructing start

	bool Action;
	Boxtype Type;
	SDL_Rect TextRect;

	Box(){}
	Box(SDL_Renderer* Renderer, SDL_Rect NewRect, Boxtype NewType, string Name)
	{
		Texture::Name = Name;
		Texture::GetType(TextureType::BoxType);
		Texture::RenderObject = Renderer;
		Type = NewType;
		Texture::Rect = NewRect;

		if (Type == Insert)
		{
			TextRect = NewRect;
			TextRect.x += 3;
			TextRect.y -= 1;
			TextRect.w = 0;
			TextRect.h = 0;
			TTF_Init(); Line = ""; 
			_Font = TTF_OpenFont("arial.ttf", 18); 
			_TextColor = { 0, 0, 0, 255 };
			max_size = Texture::Rect.w / 18;
		}
	}

	// Constructing end

	//Main Functionality
	SDL_Renderer* PassRenderer() { return Texture::RenderObject; }

	void Update() override
	{
		if (TextRect.w > Rect.w){ Backspace(); }
		Texture::Surface(TTF_RenderText_Shaded(_Font, Line.c_str(), _TextColor, SDL_Color{255,255,255,255}));
		Texture::TextureData(SDL_CreateTextureFromSurface(Texture::RenderObject,Texture::Surface()));
		SDL_QueryTexture(Texture::TextureData(), NULL, NULL, &TextRect.w, &TextRect.h);
		SDL_FreeSurface(Texture::Surface());
	}
	
	string PushBack(char Key)
	{
		auto fullrect = Texture::Rect;
		auto currentrect = TextRect;
		if (fullrect.w - currentrect.w < 20)
		{
			return Line;
		}
		Line.push_back(Key);
		return Line;
	}

	string Backspace()
	{
		Line = Line.substr(0, Line.size() - 1);
		return Line;
	}

	string GetLine()
	{
		return Line;
	}
	void ResetLine()
	{
		Line = "";
	}

private:
	TTF_Font* _Font;
	SDL_Color _TextColor;
	string Line;
	int max_size;
};

class CheckBox : public Texture
{
public:
	SDL_Rect TextRect;
	CheckBox(SDL_Renderer* RenderObject, SDL_Rect Location, int Size, std::string Name)
	{
		Texture::Name = Name;
		Location.w = Size;
		Location.h = Size;
		Texture::Rect = Location;
		Texture::RenderObject = RenderObject;
		Texture::GetType(TextureType::CheckBoxType);
		Init();
		TextRect.x = Location.x;
		TextRect.y = Location.y;
	}

	bool Init()
	{
		TTF_Init();
		_Font = TTF_OpenFont("arial.ttf", 26);
		if (_Font == nullptr) return false;
		_TextColor = { 0, 0, 0, 255 };
		return true;
	}

	void Update() override
	{
		Texture::Surface(TTF_RenderText_Blended(_Font, X, _TextColor));
		Texture::TextureData(SDL_CreateTextureFromSurface(Texture::RenderObject,Texture::Surface()));
		SDL_QueryTexture(Texture::TextureData(), NULL, NULL, &TextRect.w, &TextRect.h);
		SDL_FreeSurface(Texture::Surface());
	}

	bool State() { return _State; }
	void State(bool State) { _State = State; }
	void Switch() 
	{
		_State = !_State; 
		switch (_State)
		{
			case true:
				X = "X";
				break;
			case false:
				X = "";
				break;
		}
	}
private:
	const char* X;
	bool _State;
	TTF_Font* _Font;
	SDL_Color _TextColor;
};

