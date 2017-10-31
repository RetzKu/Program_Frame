#include "Renderer.h"
#include <tchar.h>


Texture* Renderer::AddToRenderer(TextureType Type, SDL_Rect Rect, string Name)
{
	if (Type == TextureType::TextType)
	{
		Text* NewTexture = new Text(RendererObject, Rect, Name);
		TextureList.push_back(NewTexture);
		return NewTexture;
	}
	return nullptr;
}

Texture* Renderer::AddToRenderer(TextureType Type, SDL_Rect Rect, int Size, string Name)
{
	if (Type == TextureType::CheckBoxType)
	{
		CheckBox* NewTexture = new CheckBox(RendererObject, Rect, Size, Name);
		TextureList.push_back(NewTexture);
		return NewTexture;
	}
	return nullptr;
}

Texture* Renderer::AddToRenderer(Boxtype Type, SDL_Rect Rect, string Name)
{
	if (Type == Boxtype::Empty)
	{
		Text* NewTexture = new Text(RendererObject, Rect, Name);
		TextureList.push_back(NewTexture);
		return NewTexture;
	}
	else if (Type == Boxtype::Insert)
	{
		Box* NewBox = new Box(RendererObject, Rect, Boxtype::Insert, Name);
		TextureList.push_back(NewBox);
		return NewBox;
	}
	else if (Type == Boxtype::Button)
	{
		Text* NewTexture = new Text(RendererObject, Rect, Name);
		TextureList.push_back(NewTexture);
		return NewTexture;
	}
	else if (Type == Boxtype::Filled)
	{
		Text* NewTexture = new Text(RendererObject, Rect, Name);
		TextureList.push_back(NewTexture);
		return NewTexture;
	}
	return nullptr;
}

Renderer::Renderer()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(400, 80, 0, &WindowObject, &RendererObject);
	SDL_SetRenderDrawColor(RendererObject, 255, 255, 255, 0xFF);
	StartTime = std::chrono::system_clock::now();
}


Renderer::~Renderer()
{
	for each(Texture* var in TextureList)
		delete var;
	TextureList.clear();

	SDL_DestroyRenderer(RendererObject);
	SDL_DestroyWindow(WindowObject);
	SDL_Quit();
}



void Renderer::Render()
{
	SDL_RenderClear(RendererObject);
	GetFps();
	if (sizeof(TextureList) != 0)
	{
		for each (Texture* var in TextureList)
		{
			if (var->GetType() != BoxType)
			{
				if (var->GetType() == TextType)
				{
					//Text* TmpText = dynamic_cast<Text*>(var);
					//TmpText->Update();
				}
				else if(var->GetType() == CheckBoxType)
				{
					SDL_SetRenderDrawColor(var->RenderObject, 0, 0, 0, 0xFF);
					SDL_RenderDrawRect(var->RenderObject, &var->Rect);
					SDL_SetRenderDrawColor(var->RenderObject, 255, 255, 255, 0xFF);
					CheckBox* Tmp = dynamic_cast<CheckBox*>(var);
					Tmp->Update();
				}

				SDL_RenderCopy(var->Texture::RenderObject, var->Texture::TextureData(), 0, &var->Rect);
				SDL_DestroyTexture(var->Texture::TextureData());
			}
			else
			{
				SDL_SetRenderDrawColor(var->Texture::RenderObject, 0, 0, 0, 0xFF);
				Box* TmpBox = dynamic_cast<Box*>(var);
				if (TmpBox->Type == Boxtype::Insert)
				{
					var->Update();
					SDL_RenderCopy(var->Texture::RenderObject, var->Texture::TextureData(), 0, &TmpBox->TextRect);
					SDL_DestroyTexture(var->Texture::TextureData());
				}
				SDL_RenderDrawRect(var->Texture::RenderObject, &TmpBox->Rect);
				SDL_SetRenderDrawColor(var->Texture::RenderObject, 255, 255, 255, 0xFF);
			}
		}
	}
	SDL_RenderPresent(RendererObject);
}

