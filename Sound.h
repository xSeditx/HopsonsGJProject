#pragma once
#include"window.h"
#include"SDL_Mixer.h"

// Good Sound Effect Site:  https://opengameart.org/content/rpg-sound-archive-attack-movement-hits

class SoundEffect
{
public:
    SoundEffect(){}
    
    ~SoundEffect()
    {
        Mix_FreeChunk(Object);
    }
    SoundEffect(const char *file, int volume)
    {
        Volume = volume;

        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT,2, 4096 ) == -1 )
        {
            Print("Failed to initialize Sound Effect" << Mix_GetError() );  
          return;
        }
        else
        {
            Object = Mix_LoadWAV(file  );
            //Mix_VolumeMusic(Volume);
        }
    }
    void Play()
    {
        Mix_PlayChannel(-1, Object, 0);
    }

    void SetVolume(int vol)
    {
        Volume = vol;
    }
    Mix_Chunk *Object;
    int Volume;


/*___________________________________________________________________________________________________________________________________________
 =====================================================          SOUND  ASSETS             ===========================================================
 ============================================================================================================================================*/

static void InitializeSound()
{
    LaserSound = new SoundEffect("Assets\\Laser.wav", 100);
    PlayerHit  = new SoundEffect("assets\\PlayerHit.wav", 100);

    Boom1 = new SoundEffect("assets\\Boom1.wav", 100);
    Boom2 = new SoundEffect("assets\\Boom2.wav", 100);
    Boom3 = new SoundEffect("assets\\Boom3.wav", 100);
    Boom4 = new SoundEffect("assets\\Boom4.wav", 100);
    Boom5 = new SoundEffect("assets\\Boom5.wav", 100);
    Boom6 = new SoundEffect("assets\\Boom6.wav", 100);
    Boom7 = new SoundEffect("assets\\Boom7.wav", 100);
    Boom8 = new SoundEffect("assets\\Boom8.wav", 100);
    Boom9 = new SoundEffect("assets\\Boom9.wav", 100);
}
static SoundEffect *LaserSound,
                   *PlayerHit;

static SoundEffect *Boom1,
                   *Boom2,
                   *Boom3,
                   *Boom4,
                   *Boom5,
                   *Boom6,
                   *Boom7,
                   *Boom8,
                   *Boom9;
};



class Music
{
public:
        Music(){}
        
        ~Music()
        {
                Mix_FreeMusic(Object);
        }
        Music(const char *file, int volume)
        {
                Volume = volume;
                
                if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT,2, 4096 ) == -1 )
                {
                    Print("Failed to initialize Music" << Mix_GetError() );  
                  return;
                }
                else
                {
                    Object = Mix_LoadMUS(file);
                    Mix_VolumeMusic(2000);
                }


                Stereo = true;
        }
        
        void Play()
        {
                Mix_PlayMusic(Object, -1 );
        }
        
        void SetVolume(int vol)
        {
                Volume = vol;
                Mix_VolumeMusic(Volume);
        }


        Mix_Music *Object;
        bool Stereo;
        int Volume;

/*___________________________________________________________________________________________________________________________________________
 =====================================================           MUSIC  ASSETS             ==================================================
 ============================================================================================================================================*/
    static void InitializeMusic()
    {
        BackgroundMusic  = new Music("Assets\\Music.wav", 1000);
        BackgroundMusic2 = new Music("Assets\\Mayhem.wav", 1000);
    }
    
    static  Music *BackgroundMusic, *BackgroundMusic2;
};



//
//
//class Sound
//{
//public:
//    Sound()
//    {
//
//    }
//
//};
//
//
//
//
//



//          //Initialize SDL_mixer
//      if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT,2, 4096 ) == -1 )
//      {
//          Print("Failed to initialize sound");  
//      }
//      else
//      {
//          BottleRocket = Mix_LoadWAV( "Assets\\Laser.wav" );
//          PlayerHit = Mix_LoadWAV("Assets\\PlayerHit.wav");
//
//
//
//
//          Mix_VolumeMusic(1000 );
//          Mix_Volume(-1, 20);
//          if(!BGmusic)printf("Music Error %s",Mix_GetError());
//      }
//    Mix_Chunk *BottleRocket;
//    Mix_Chunk *PlayerHit;
//    Mix_Music *BGmusic;
//    void Play(Mix_Chunk *sound)
//    {
//        Mix_PlayChannel(-1, sound, 0);
//    }
//
//    void MusicPlay(Mix_Music *song)
//    {
//         Mix_PlayMusic( song, -1 );
//    }
//
//
//    ~Sound()
//    {
//        Mix_FreeChunk(BottleRocket);
//    }
//static SoundEffect*BackgroundMusic;