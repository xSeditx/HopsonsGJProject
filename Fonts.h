#pragma once
#include"window.h"
#include"SDL_ttf.h"
/*


FONT RENDERER STARTED. NEED TO PLACE ALL THE GIVEN TEXT INTO A STD::VECTOR SO THAT i CAN ASSIGN IT ONCE 
AND SPEED UP THE FONT RENDERING PROCESS. 
CREATE STRING, 
RENDER STRING AND 
DESTROY STRING FUNCTIONS ARE NEEDED
ALSO SOME STYLE AND COLOR FUNCTIONALITY

*/


class FontRender
{
public:
    FontRender()
    {
        if (TTF_Init() < 0) 
        {
            Print("Font Initialization Failed");
            std::cout << "Error: " << TTF_GetError() << std::endl;
        }

        CurrentFont = nullptr;
    }


    TTF_Font *CurrentFont;

    void LoadFont(const char*file)
    {
        CurrentFont = TTF_OpenFont(file, 30);
        if(!CurrentFont)Print(TTF_GetError);
    }

    void FreeFont(TTF_Font *font)
    {
        TTF_CloseFont(font);
    }

    void CloseFontRender()
    {
        TTF_Quit();
    }

    void Write(const char *text, int x, int y)
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

            //Set rendering space and render to screen
            SDL_Rect renderQuad = { x, y, Width, Height };
            SDL_RenderCopy( SCREEN->Renderer, mTexture, NULL, &renderQuad );

            SDL_DestroyTexture(mTexture); 
         }

    }

    SDL_Color ForgroundColor, BackgroundColor;

    void SetBackGroundColor(SDL_Color col) {BackgroundColor = col;}
    void SetForgroundColor(SDL_Color col)  {ForgroundColor  = col;}
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