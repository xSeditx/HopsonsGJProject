#pragma once
#include <SDL.h>
#include "window.h"
#include<vector>
#include<iostream>
#include<SDL_IMAGE.h>
#include<memory>

#include"Collision.h"

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



//   class AniEntity : public Sprite
//   {
//   public:
//   	  AniEntity(){}
//   	 ~AniEntity(){}
//       
//   	  AniEntity(SpriteSheet *source, int numstates): Sprite(source,numstates){}
//   };
//   
//   
//   class Player: public AniEntity
//   {
//   public:
//       Player( SpriteSheet *source, int numstates);
//       int Health;
//   };
//   
//   class Enemy: public AniEntity
//   {
//   public:
//       Enemy(Vec2 pos, SpriteSheet *source, int numstates);
//   
//       void(*func)(Enemy *object);
//       int Health;
//   };
//   
//   class StaticSprite: public AniEntity
//   {
//   public:
//       StaticSprite(Vec2 pos, SpriteSheet *source, int numstates);
//       bool Moveable;
//   };
//   



extern SDL_Rect MAKE_Rect(int x,int y, int w, int h);
extern void DESTROY_SHEET(SpriteSheet *sheet);
std::shared_ptr<SpriteSheet> LOAD_SHEET(char *file);



//{
//    return std::make_shared<SpriteSheet>(file);
//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

struct TILE{
	Rect SOURCE;
	bool IS_SOLID;
};

class TileSheet{
public:
	TileSheet();
	~TileSheet();
	TileSheet(char *file, Rect crop);
	char *SOURCE_FILE;

	Surface *IMAGE;
	Texture *SOURCE;

	Rect TILE_DIMENSIONS;

	std::vector<TILE> TILES;
 
	void PASTE(int index, int x,int y);
};





class StaticSprite{
public:
	struct{
		float X,Y,Z;
	}POSITION;

	struct{
		int WIDTH,
			HEIGHT;
	}SIZE;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// ANIMATED SPRITES /////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class State{
public:
	State(){}
~State(){}
    State(Rect start, int number_of_frames);

	int NUMBER_OF_FRAMES;

	std::vector<Rect> FRAMES;
};


class AnimatedSprite : public StaticSprite{
public:
	AnimatedSprite(){}
	~AnimatedSprite(){}
	AnimatedSprite(char *file, int numstates);

	char        *SOURCE_FILE;

	Surface *IMAGE;
	Texture *SOURCE;

	int NUMBER_OF_STATES;
    bool IS_ANIMATING;

	struct{
		int STATE,
			FRAME;
	}CURRENT;

	std::vector<State> STATE;

	void ANIMATE();
	bool CHOP(int numstates,int numframes);

private:

	bool  IS_SOLID;
	bool  COLLISION_TYPE;
	float COLLISION_RADIUS;
};


*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// WORLD CLASS //////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//extern bool CHECK_COLLISION(StaticSprite sprite1, StaticSprite sprite2);
/*class AniSprite: public SpriteSheet{

	AniSprite(){}
   ~AniSprite(){}

	AniSprite(SpriteSheet *source, int numstates);

	struct{
		unsigned int STATE,
			         FRAME;
	}CURRENT;

	int NUMBER_OF_STATES;
	std::vector<State> STATES;


	State::State(uint x, uint y, uint w, uint h,uint numframes){
		FRAMES.reserve(numframes);
	LOOP(numframes){
		Rect temp;
		temp.x = x;
		temp.y = y;
		temp.w = w;
		temp.h = h;
		FRAMES.emplace_back(temp);
		x += w;
	}
}



};*/


