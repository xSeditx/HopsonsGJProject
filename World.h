#pragma once
/*
________________________________________________________________________________________________________________________________________
                                                                                                                                
                                                     WORLD.CPP                                                                                                                                 
                                                                                                                                
              Handler of all Layers, Players Sprites, Collisions, Almost everything from the sounds of it                                                                                                                  
                                                                                                                                
________________________________________________________________________________________________________________________________________
*/



// TODO: Fix the HUD so that the health displays over the Background. 
// Fix the Background so that it positions correctly at the start, make a background that is the entire level, when its reached a Boss starts

#include"Camera.h"
#include"Sprite.h"
#include"Entities.h"
#include"Fonts.h"

#define NUMSTARS 200

#define PointScale 2

class StarField
{
public:
    StarField()
    {
        ForwardThrust = 1.0f;
        BackgroundPosition = 0;
        Background = new Image("assets\\Background1.bmp");
 

        Init();
    }
    Vec3 Stars[NUMSTARS];

    float ForwardThrust;

    SDL_Point *Points;

    float BackgroundPosition; 

    void Update()
    {
        for_loop(Index, NUMSTARS)
        {
            Stars[Index].y += ForwardThrust / Stars[Index].z;
            if(Stars[Index].y >= SCREENHEIGHT)
            {
                Stars[Index].y = 0;
                Stars[Index].x = RANDOM(SCREENWIDTH);
            }
                Points[Index].x =  Stars[Index].x / PointScale;
                Points[Index].y =  Stars[Index].y / PointScale;
        }

    }

    void Render()
    {
        BackgroundPosition += 0.05f;
  //      Background->Render(Vec2(0, BackgroundPosition),Vec2(SCREENWIDTH, Background->Size.y ));

        SDL_RenderSetScale(SCREEN->Renderer,PointScale,PointScale);
        SDL_SetRenderDrawColor( SCREEN->Renderer, 255, 255, 255, 255 );
        SDL_RenderDrawPoints(SCREEN->Renderer, Points, NUMSTARS);
        SDL_SetRenderDrawColor( SCREEN->Renderer, 0, 0, 0, 255 );
        SDL_RenderSetScale(SCREEN->Renderer,1,1);
    }

    void Init()
    {
        for_loop(Index, NUMSTARS)
        {
            Stars[Index] = Vec3(RANDOM(SCREENWIDTH), RANDOM(SCREENHEIGHT), RANDOM(10));
        }
        Points = new SDL_Point[NUMSTARS];
    }


    Image *Background;
};
class HUD
{
public:
        HUD()
        {
                const char *file = "Assets\\HUD.BMP";
                
    	        Surface = IMG_Load(file);
    	        if(!Surface)
                {
    	                Print("Image Can not be loaded");Print(file);
    	        }
                
    	        Texture = SDL_CreateTextureFromSurface(SCREEN->Renderer, Surface);
    	        if(!Texture)
                {
    	                Print("Texture Can not be made.");Print(file);
    	        }
                SDL_FreeSurface(Surface);
                SrcRect.x = 0;
                SrcRect.y = 0;
                SrcRect.w = 640;
                SrcRect.h = 75;
                
                
                DestRect.x = 0;
                DestRect.y = SCREENHEIGHT - 75;
                DestRect.w = 640;
                DestRect.h = 75;
        }
        
        void Update(int health, int energy, int lives)
        {
                SDL_Rect HBar ={19, SCREENHEIGHT - 38,   2+ health * 3, 20};
                
                SDL_SetRenderDrawColor(SCREEN->Renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(SCREEN->Renderer, &HBar);
                
                SDL_Rect EBar ={19, SCREENHEIGHT - 52,   3* energy , 8};
                SDL_SetRenderDrawColor(SCREEN->Renderer, 0, 15, 255, 255);
                SDL_RenderFillRect(SCREEN->Renderer, &EBar);
                FontRender::Fonts->Write(lives, Vec2(SCREENWIDTH - 50, SCREENHEIGHT - 60));
        }
        void Render()
        {
                SDL_RenderCopy(SCREEN->Renderer, Texture, &SrcRect, &DestRect);
        }
        
        SDL_Surface *Surface;
        SDL_Texture *Texture;

        SDL_Rect SrcRect,
                 DestRect;
};
class World
{
public:
        World()
        {  
                Player1 = nullptr;
                Difficulty = 1;
              //  BackgroundPosition = 0;
                Load();
                WorldTimer = SDL_GetTicks();
        }


        HUD       *HeadsUp;
        Music     *BackgroundMusic;
        StarField *StarBackground;

        Player    *Player1;

        float WorldTimer;

        void Load();
        void Update();
        void Render();

static void Reset();


        void StartScreen();

private: 
        int Difficulty;
};
