#pragma once
#include <SDL.h>
#include "window.h"
#include <vector>
#include <iostream>
#include <SDL_IMAGE.h>
#include <memory>
#include "Collision.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TypeDefs so that all that is needed it is to change this if a Library change is needed
//#undef Rect
#ifdef _SDL_

//        typedef SDL_Rect     Rect;
        typedef SDL_Surface  Surface;
        typedef SDL_Texture  Texture;
        typedef unsigned int uint;
#endif



//==================================================================================================================================
//_______________________________________  StaticSprite Sheet Class __________________________________________________________________________
//==================================================================================================================================

class SpriteSheet
{
public:
	    SpriteSheet(){}
       ~SpriteSheet(){}
        SpriteSheet(char *file);
	    
	    char    *SOURCE_FILE;
	    Surface *IMAGE;
	    Texture *SOURCE;

		void SET_TEXTURE(Texture *SOURCE);

 static void LoadAssets();
        Texture *LoadImageSheet(const char *file);



 static SpriteSheet *Ship,
                    *Eye, 
                    *EnergySpheres, 
                    *Bullet,
                    *PlasmaBurst;
};


//==================================================================================================================================
//_______________________________________  State Sheet Class ______________________________________________________________________
//                                                                                                                                  
// Each Entity have a variety of States it can be in. This class defines the Various Animation states for every Entity
//==================================================================================================================================

class State
{
public:
	    State(){}
	    ~State(){}
	    State(SDL_Rect sourcerect,uint numframes);


        State(SDL_Rect sourcerect,Vec2 size, uint numframes);


	    State(uint x, uint y,uint w,uint h,uint numframes);


	    std::vector<SDL_Rect>FRAMES;
	    uint TOTAL_FRAMES;
	    uint CURRENT_FRAME;
 

        State operator +=(SDL_Rect newframe)
{ 
    this->ADD_FRAME(newframe);  
    return *this;
}
        State operator +=(State newstate)
{
    for_loop(count, newstate.TOTAL_FRAMES)
    {
        this->ADD_FRAME(newstate.FRAMES[count]); 
        this->TOTAL_FRAMES++;
    }
    return *this;
}
        
private:
		std::vector<SDL_Rect>& ADD_FRAME(SDL_Rect frame);

};


//==================================================================================================================================
//_______________________________________  Entity Class ______________________________________________________________________
//                                                                                                                                  
// Each Entity have a variety of States it can be in. This class defines the Various Animation states for every Entity
//==================================================================================================================================


class Sprite
{
public:
	    Sprite(){}
       ~Sprite(){}

	    Sprite(SpriteSheet *source, int numstates);
	    Sprite(SpriteSheet *source){*this = Sprite(source, 1);}	    


        Vec2 Position;
        Vec2 Size;

        Vec2 ProjectedSize;
	    
	    bool SOLID,
	         ANIMATED;
	    
        float Angle;
	    SpriteSheet *SOURCE;
	    
        uint TOTAL_STATES;
        std::vector<State> STATE;

	    uint CURRENT_STATE;
        int AnimationSpeed;

        bool Collidable, 
             Static;




       // Collider *CollisionBounds;

public:

    inline void SetPosition(Vec2 pos){ Position = pos;}


        void Update();
        void Render();
        AABB* MakeCollisionBox();
};

extern SDL_Rect MAKE_Rect(int x,int y, int w, int h);
extern void DESTROY_SHEET(SpriteSheet *sheet);
std::shared_ptr<SpriteSheet> LOAD_SHEET(char *file);
