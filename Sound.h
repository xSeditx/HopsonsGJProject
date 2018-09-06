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

    LaserHead0001 = new SoundEffect("Assets\\Head0001.wav", 100);
    LaserHead0002 = new SoundEffect("Assets\\Head0002.wav", 100);
    LaserHead0003 = new SoundEffect("Assets\\Head0003.wav", 100);
    LaserHead0004 = new SoundEffect("Assets\\Head0004.wav", 100);
    LaserHead0005 = new SoundEffect("Assets\\Head0005.wav", 100);
    LaserHead0006 = new SoundEffect("Assets\\Head0006.wav", 100);
    LaserHead0007 = new SoundEffect("Assets\\Head0007.wav", 100);
    LaserHead0008 = new SoundEffect("Assets\\Head0008.wav", 100);
    LaserHead0000 = new SoundEffect("Assets\\Head0000.wav", 100);
                                                               
    LaserTail0001 = new SoundEffect("Assets\\Tail0001.wav", 100);
    LaserTail0002 = new SoundEffect("Assets\\Tail0002.wav", 100);
    LaserTail0003 = new SoundEffect("Assets\\Tail0003.wav", 100);
    LaserTail0004 = new SoundEffect("Assets\\Tail0004.wav", 100);
    LaserTail0005 = new SoundEffect("Assets\\Tail0005.wav", 100);
    LaserTail0006 = new SoundEffect("Assets\\Tail0006.wav", 100);
    LaserTail0007 = new SoundEffect("Assets\\Tail0007.wav", 100);
    LaserTail0008 = new SoundEffect("Assets\\Tail0008.wav", 100);
    LaserTail0000 = new SoundEffect("Assets\\Tail0000.wav", 100);
                                                               
    LaserBody0001 = new SoundEffect("Assets\\Body0001.wav", 100);
    LaserBody0002 = new SoundEffect("Assets\\Body0002.wav", 100);
    LaserBody0003 = new SoundEffect("Assets\\Body0003.wav", 100);
    LaserBody0004 = new SoundEffect("Assets\\Body0004.wav", 100);
    LaserBody0005 = new SoundEffect("Assets\\Body0005.wav", 100);
    LaserBody0006 = new SoundEffect("Assets\\Body0006.wav", 100);
    LaserBody0007 = new SoundEffect("Assets\\Body0007.wav", 100);
    LaserBody0008 = new SoundEffect("Assets\\Body0008.wav", 100);
    LaserBody0000 = new SoundEffect("Assets\\Body0000.wav", 100);

    Beep01 = new SoundEffect("Assets\\Click.wav", 100);
    GunFire = new SoundEffect("Assets\\antimatterhit.wav",100);
}


static SoundEffect *LaserSound,
                   *PlayerHit;

static SoundEffect *Beep01;

static SoundEffect *Boom1,
                   *Boom2,
                   *Boom3,
                   *Boom4,
                   *Boom5,
                   *Boom6,
                   *Boom7,
                   *Boom8,
                   *Boom9;


static SoundEffect *LaserHead0001,
                   *LaserHead0002,
                   *LaserHead0003,
                   *LaserHead0004,
                   *LaserHead0005,
                   *LaserHead0006,
                   *LaserHead0007,
                   *LaserHead0008,
                   *LaserHead0000;
                                
static SoundEffect *LaserTail0001,
                   *LaserTail0002,
                   *LaserTail0003,
                   *LaserTail0004,
                   *LaserTail0005,
                   *LaserTail0006,
                   *LaserTail0007,
                   *LaserTail0008,
                   *LaserTail0000;
                                
static SoundEffect *LaserBody0001,
                   *LaserBody0002,
                   *LaserBody0003,
                   *LaserBody0004,
                   *LaserBody0005,
                   *LaserBody0006,
                   *LaserBody0007,
                   *LaserBody0008,
                   *LaserBody0000;
 static SoundEffect *GunFire;                               
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
        BackgroundMusic2 = new Music("Assets\\Mayhem.mp3", 1000);
    }
    
    static  Music *BackgroundMusic, *BackgroundMusic2;
};
 