#pragma once
#include"window.h"
#include"SDL_ttf.h"
#include<string>
/*

FONT RENDERER STARTED. NEED TO PLACE ALL THE GIVEN TEXT INTO A STD::VECTOR SO THAT i CAN ASSIGN IT ONCE 
AND SPEED UP THE FONT RENDERING PROCESS. 
CREATE STRING, 
RENDER STRING AND 
DESTROY STRING FUNCTIONS ARE NEEDED
ALSO SOME STYLE AND COLOR FUNCTIONALITY

*/


//TODO: So much shit to do here. Perhaps make a loader like I did everything else but even that has become a pain in the ass to manage 
//     even though its extremely easy.




#define OPENING_FONT 0 

class FontRender
{

public:
    FontRender(const char*file)
    {
        if (TTF_Init() < 0) 
        {
            Print("Font Initialization Failed");
            Print("Error: " << TTF_GetError());
        }

        CurrentFont = TTF_OpenFont(file, 30);

        if(!CurrentFont)
        {
            Print(TTF_GetError);
        }
    }
    FontRender(const char*file, int size)
    {
        if (TTF_Init() < 0) 
        {
            Print("Font Initialization Failed");
            Print("Error: " << TTF_GetError());
        }

        CurrentFont = TTF_OpenFont(file, size);

        if(!CurrentFont)
        {
            Print(TTF_GetError);
        }
    }

    TTF_Font *CurrentFont;

    void FreeFont(TTF_Font *font)
    {
        TTF_CloseFont(font);
    }
    void CloseFontRender()
    {
        TTF_Quit();
    }
    void SetSize()
    {
        
    }
    void Write(float value, Vec2 pos)
    {
        std::string Str = std::to_string((int)value);
        const char* S = Str.c_str();

        Write(S, pos);
    }
    void Write(const char *text, Vec2 pos)
    {
        float Width  = 0, 
              Height = 0;

        SDL_Surface *surface = TTF_RenderText_Solid(CurrentFont, text, ForgroundColor);

        if( surface == NULL )
         {
             printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
         }
         else
         {
             SDL_Texture *mTexture = SDL_CreateTextureFromSurface( SCREEN->Renderer, surface );
             if( mTexture == NULL )
             {
                 printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
             }
             else
             {
                 //Get image dimensions
                 Width  = surface->w;
                 Height = surface->h;
             }
             SDL_FreeSurface( surface );
             //TTF_Set
             //Set rendering space and render to screen
             SDL_Rect renderQuad = { (int)pos.x, (int)pos.y, (int)Width, (int)Height };
             SDL_RenderCopy( SCREEN->Renderer, mTexture, NULL, &renderQuad );
             
             SDL_DestroyTexture(mTexture); 
         }
    }


    void WriteShadow(const char *text, Vec2 pos, int depth)
    {
        SDL_Color savedcol = ForgroundColor; 

        SetForgroundColor(100,100,100, 255);
        Write(text, Vec2(pos.x + depth, pos.y + depth));

        SetForgroundColor(savedcol.r, savedcol.g, savedcol.b, savedcol.a);
        Write(text, pos);
    }
    void WriteShadow(float value, Vec2 pos, int depth)
    {
        SDL_Color savedcol = ForgroundColor; 

        SetForgroundColor(100,100,100, 255);
        std::string Str = std::to_string((int)value);
        const char* S = Str.c_str();
        Write(S, Vec2(pos.x + depth, pos.y + depth));

        SetForgroundColor(savedcol.r, savedcol.g, savedcol.b, savedcol.a);
        Str = std::to_string((int)value);
        S = Str.c_str();
        Write(S, pos);
    }



    void SetForgroundColor(float R, float G, float B, float A)
    {
        ForgroundColor.r = R;
        ForgroundColor.g = G;
        ForgroundColor.b = B;
        ForgroundColor.a = A;
    }

    int CurrentFontID;

    SDL_Color ForgroundColor, 
              BackgroundColor;
    static FontRender *Fonts;
    void SetBackGroundColor(SDL_Color col) {BackgroundColor = col;}
    void SetForgroundColor(SDL_Color col)  {ForgroundColor  = col;}

    float Size;
};










//SDL_Surface *TTF_RenderGlyph_Solid(TTF_Font* font, Uint16 ch, SDL_Color fg);
//SDL_Surface *TTF_RenderText_Solid(TTF_Font *font, const char *text, SDL_Color fg);
//SDL_Surface *TTF_RenderUTF8_Solid(TTF_Font *font, const char *text, SDL_Color fg);
//SDL_Surface *TTF_RenderUNICODE_Solid(TTF_Font *font, const Uint16 *text, SDL_Color fg);
//
// 
// The third function is:
// 1
// TTF_Font* TTF_OpenFontRW(SDL_RWops *src, int freesrc, int ptsize);
// You may or may not have seen the SDL_RWops struct before. It is an undocumented feature of SDL and so is rarely seen (I personally have never seen nor used it). It is capable of taking a pointer to memory where some data is stored, but files are supported too. Since this tutorial is about SDL_ttf and not SDL_RWops, I've added a suggested reading entry at the bottom if you want to know more. If you pass a non-zero value as the second argument the memory used by the SDL_RWops struct is automatically freed before the function returns. The third and last argument is the point size. 