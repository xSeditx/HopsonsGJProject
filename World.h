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

    ~StarField()
    {
        delete(Background);
        delete(Points);

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

                SDL_Surface *SBG = IMG_Load("Assets\\Score.bmp");
                ScoreBG = SDL_CreateTextureFromSurface(SCREEN->Renderer, SBG);
        }
        
        void Update(int health, int energy, int lives)
        {
                if(Player::PlayerOne->Score < 0 )
                {
                    Player::PlayerOne->Score = 0;
                }
        }
        void Render()
        {

                SDL_Rect Sour = {0,0,350,60};
                SDL_Rect Dest = {0,0,350,60};
                SDL_SetRenderDrawColor(SCREEN->Renderer, 0, 0, 0, 255);
                SDL_RenderCopy(SCREEN->Renderer, ScoreBG, &Sour, &Dest);

//~~Base of HUD Render
                SDL_SetRenderDrawColor(SCREEN->Renderer, 0, 0, 0, 255);
                SDL_RenderCopy(SCREEN->Renderer, Texture, &SrcRect, &DestRect);

//~~~~~~~ Score Render
                std::string Str = std::to_string(Player::PlayerOne->Score);
                const char* S = Str.c_str();

                FontRender::Fonts->SetForgroundColor(0, 255,255,255); // Front
                FontRender::Fonts->WriteShadow("Score: " ,Vec2(10,10), 5);
                FontRender::Fonts->WriteShadow(S, Vec2(160,10),2);// Displaying the Score

//~~~~ HeathBar Render

                SDL_Rect HBar ={20, SCREENHEIGHT - 37,   2+ Player::PlayerOne->Health * 3, 16};
                SDL_SetRenderDrawColor(SCREEN->Renderer, 0, 150, 0, 255);
                SDL_RenderFillRect(SCREEN->Renderer, &HBar);
               
                SDL_Rect HBar3 ={22, SCREENHEIGHT - 35, (Player::PlayerOne->Health * 3) - 2, 3};
                SDL_SetRenderDrawColor(SCREEN->Renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(SCREEN->Renderer, &HBar3);

//~~~ EnergyBar Render
                SDL_Rect EBar ={19, SCREENHEIGHT - 52,   3* Player::PlayerOne->EnergyLevel , 8};
                SDL_SetRenderDrawColor(SCREEN->Renderer, 0, 15, 255, 255);
                SDL_RenderFillRect(SCREEN->Renderer, &EBar);
                SDL_SetRenderDrawColor(SCREEN->Renderer, 0, 100, 255, 255);
                SDL_RenderDrawLine(SCREEN->Renderer, 21, SCREENHEIGHT - 50, 17 + (3* Player::PlayerOne->EnergyLevel) , SCREENHEIGHT - 50);

//~~~~~~~~Lives Render
                FontRender::Fonts->SetForgroundColor(255, 255, 0,255); // Front
                FontRender::Fonts->WriteShadow(Player::PlayerOne->Lives, Vec2(SCREENWIDTH - 53, SCREENHEIGHT - 60), 5);
                SDL_SetRenderDrawColor(SCREEN->Renderer, 0, 0, 0, 255);

        }

        SDL_Texture *ScoreBG;
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
                WorldTimer = SDL_GetTicks();
                Load();
        }
       ~World()
        {
               delete(HeadsUp);
               delete(StarBackground);
               delete(BackgroundMusic);
        }

        static bool DoneLoading;
        static bool KeyHasBeenPressed;

        HUD       *HeadsUp;
        Music     *BackgroundMusic;
        StarField *StarBackground;

        Player    *Player1;

        float WorldTimer,
              StartTimer; 

        void Load();
        void Update();
        void Render();


        void SpawnEnemies();
static  void Reset();
static  void PauseGame();
static  void StartScreen();
static  void THREAD_InitializeAll();

private: 
        int Difficulty;
};





