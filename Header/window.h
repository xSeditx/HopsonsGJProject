#pragma once
#define SDL_MAIN_HANDLED
#define _SDL_

#define _AFXDLL

#include<Windows.h>

#pragma warning(disable:4244)
#pragma warning(disable:4018)
#pragma warning(disable:4805) // Disables ==:  unsafe mix of type 'const Uint8' and type 'bool' in operation

#include"../Bin/include/SDL.h"
#include"../Bin/include/SDL_syswm.h"
#include"../Bin/glm-0.9.9.5/glm/glm.hpp"

#include <iostream>
#include <chrono>
#include <vector>
#include<functional>
///#include "Vertex.h"
///#include"GLM.hpp"
///#include"Fonts.h"

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::mat4 Matrix;


//#include "C:\Users\Curt\Documents\Visual Studio 2012\Libraries\SDL2\include\SDL_mixer.h"
/* Constants rounded for 21 decimals. */
#ifndef M_PI
#    define     M_E           2.71828182845904523536
#    define     M_LOG2E       1.44269504088896340736
#    define     M_LOG10E      0.434294481903251827651
#    define     M_LN2         0.693147180559945309417
#    define     M_LN10        2.30258509299404568402
#    define     M_PI          3.14159265358979323846
#    define     M_PI_2        1.57079632679489661923
#    define     M_PI_4        0.785398163397448309616
#    define     M_1_PI        0.318309886183790671538
#    define     M_2_PI        0.636619772367581343076
#    define     M_1_SQRTPI    0.564189583547756286948
#    define     M_2_SQRTPI    1.12837916709551257390
#    define     M_SQRT2       1.41421356237309504880
#    define     M_SQRT_2      0.707106781186547524401
#endif                      


#define     Print(x)                  std::cout << x << std::endl
#define     GetRandom( min, max )     ((rand() % (int)(((max) + 1) - (min))) + (min))  
#define     RANDOM(x)                 ((rand() * (1.0 / (1.0 + RAND_MAX))) * (x))
#define     RANDOM_RANGE(x)           (RANDOM(x * 2) - (x))

#ifdef RGB
#undef RGB
#endif

#define     RGB(r,g,b)                ((int)(b) + ((int)(g)<< 8) + ((int)(r) << 16))
#define     RADIANS(angle)            ((angle) * .0174532925199444)
           
#define     LOOP(x)                   for(int count = 0; count < (x); count++)
#define     for_loop(x,c)             for(int x = 0; x < c; x++)
           
#define     SCREENWIDTH      640 //  1280 //
#define     SCREENHEIGHT     880// 480  //  960 //
           
#define     _LOOP_GAME         SCREEN->LOOP_GAME()        // This is being done for future compatibility with various Graphics Libraries
#define     _CLS                     SCREEN->CLS()        //
#define     _SYNC                   SCREEN->SYNC()        //
                               
#define     _COS(a)               cos(RADIANS(a))  //   Cos[(int)a] // 
#define     _SIN(a)               sin(RADIANS(a)) //  Sin[(int)a] //
           
#define     MIN(a,b)          ((a<b) ? a : b)
#define     MAX(a,b)          ((a>b) ? a : b)
           
#define     PICK_ONE(a,b)          ((RANDOM(1) > .5) ? a : b)
           
#define     Speed_Test(x)     \
    float Timer = SDL_GetTicks();  \
    x  \
       \
    std::cout << "Speed:" << SDL_GetTicks() - Timer << std::endl;
                        


extern float Cos[360], 
             Sin[360]; 



inline float Squared(float x)
{
    return (x * x);
}





struct Rect
{
    Rect(){}
    Rect(int X,int Y,int W, int H) 
          :x(X), y(Y), w(W),  h(H) 
    {/*==================+=========*/}
    int x,
        y,
        h,
        w;
};



class CallBack{
    public:
        CallBack()
        {
                
            CallBackOnEvent          = NULL;
            CallBackOnInputFocus     = NULL;
            CallBackOnInputBlur      = NULL;
            CallBackOnKeyDown        = NULL;
            CallBackOnKeyUp          = NULL;
            CallBackOnMouseFocus     = NULL;
            CallBackOnMouseBlur      = NULL;
            CallBackOnMouseMove      = NULL;
            CallBackOnMouseWheel     = NULL;
                                     
            CallBackOnLButtonDown    = NULL;
            CallBackOnLButtonUp      = NULL;
            CallBackOnRButtonDown    = NULL;
            CallBackOnRButtonUp      = NULL;
            CallBackOnMButtonDown    = NULL;
            CallBackOnMButtonUp      = NULL;
                                   
            CallBackOnJoyAxis        = NULL;
            CallBackOnJoyButtonDown  = NULL;
            CallBackOnJoyButtonUp    = NULL;
            CallBackOnJoyHat         = NULL;
            CallBackOnJoyBall        = NULL;
            CallBackOnMinimize       = NULL;
            CallBackOnRestore        = NULL;
            CallBackOnResize         = NULL;
            CallBackOnExpose         = NULL;
            CallBackOnExit           = NULL;
            CallBackOnUser           = NULL;

        };
        ~CallBack(){};

       void (*CallBackOnEvent)                (SDL_Event* Event);

       void (*CallBackOnInputFocus)           ();
       void (*CallBackOnInputBlur)            ();
       void (*CallBackOnKeyDown)              (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier , Uint8 rep);                                                    //(SDL_Keysym sym, int mod, Uint16 unicode);
       void (*CallBackOnKeyUp)                (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier );                                                               //(SDL_Keysym sym, int mod, Uint16 unicode);
       void (*CallBackOnMouseFocus)           ();
       void (*CallBackOnMouseBlur)            ();
       void (*CallBackOnMouseMove)            (int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
       void (*CallBackOnMouseWheel)           (bool Up, bool Down); 
                                             
       void (*CallBackOnLButtonDown )         (int mX, int mY);
       void (*CallBackOnLButtonUp  )          (int mX, int mY);
       void (*CallBackOnRButtonDown)          (int mX, int mY);
       void (*CallBackOnRButtonUp )           (int mX, int mY);
       void (*CallBackOnMButtonDown)          (int mX, int mY);
       void (*CallBackOnMButtonUp   )         (int mX, int mY);


       void (*CallBackOnJoyAxis)              (Uint8 which, Uint8 axis, Sint16 value);
       void (*CallBackOnJoyButtonDown)        (Uint8 which, Uint8 button);
       void (*CallBackOnJoyButtonUp)          (Uint8 which, Uint8 button);
       void (*CallBackOnJoyHat)               (Uint8 which, Uint8 hat, Uint8 value);
       void (*CallBackOnJoyBall)              (Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
       void (*CallBackOnMinimize)             ();
       void (*CallBackOnRestore)              ();
       void (*CallBackOnResize)               (int w,int h);
       void (*CallBackOnExpose)               ();
       void (*CallBackOnExit)                 ();
       void (*CallBackOnUser)                 (Uint8 type, int code, void* data1, void* data2);

       void SetOnEvent(SDL_Event* Event);

       void SetOnInputFocus();
       void SetOnInputBlur();
       
       void SetOnKeyDown(void (*f)   (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier , Uint8 rep)) {CallBackOnKeyDown     = f;}
       void SetOnKeyUp  (void (*f)   (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier ))            {CallBackOnKeyUp       = f;}
       
       void SetOnMouseFocus                   ();
       void SetOnMouseBlur                    ();
       void SetOnMouseMove(void (*f) (int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle))  {CallBackOnMouseMove = f;}
       void SetOnMouseWheel                   (bool Up, bool Down);    
       
       void SetOnLButtonDown(void (*f)        (int, int))                                            {CallBackOnLButtonDown = f;}
       void SetOnLButtonUp(void (*f)          (int, int))                                            {CallBackOnLButtonUp   = f;}
       void SetOnRButtonDown(void (*f)        (int, int))                                            {CallBackOnRButtonDown = f;}
       void SetOnRButtonUp(void (*f)          (int, int))                                            {CallBackOnRButtonUp   = f;}
       void SetOnMButtonDown(void (*f)        (int, int))                                            {CallBackOnMButtonDown = f;}
       void SetOnMButtonUp(void (*f)          (int, int))                                            {CallBackOnMButtonUp   = f;}
       
       void SetOnJoyAxis                      (Uint8 which, Uint8 axis, Sint16 value);
       void SetOnJoyButtonDown                (Uint8 which, Uint8 button);
       void SetOnJoyButtonUp                  (Uint8 which, Uint8 button);
       void SetOnJoyHat                       (Uint8 which, Uint8 hat, Uint8 value);
       void SetOnJoyBall                      (Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
       
       void SetOnMinimize                     ();
       void SetOnRestore                      ();
       void SetOnResize                       (int w,int h);
       void SetOnExpose                       ();
       void SetOnExit                         ();
       void SetOnUser                         (Uint8 type, int code, void* data1, void* data2);
};

class GUI; // FORWARD DECLARATION OF GUI CLASS
class Window
{

public:
	Window();~Window();
	Window(int,int,int,int,char*);


	 int       X,
	       	   Y,
		       WIDTH,
		       HEIGHT;

	 char     *TITLE;

     HWND                    WIN_HWND;
     SDL_Window             *SDL_HWND;
	 SDL_Texture            *BackBuffer;
     SDL_Renderer           *Renderer;

	 Uint32                  *WindowPixels;

	 Uint32                  WindowFormat; 
	 SDL_Event               Event;
	 SDL_Surface            *WindowSurface;
	 SDL_PixelFormat        *MappingFormat;

     SDL_Surface            *FONT_SURFACE;
     SDL_Texture            *FONT_TEXTURE;
     int FONT_SET[96*256];
// Mouse Position and Velocity can be accessed as either SDL_Point or via its X,Y Coords. 
// This is done for Future implementations with SDL;

     struct{
         float Angle,
               Speed;

         union {
             struct{
                 float X,
                       Y;
             }Velocity;
            SDL_Point MouseVelocity;
         };


         struct{
             bool Left,
                  Right,
                  Center;
         }Button;


         union{
             struct{
                 float X,
                       Y;
             }Position;
             SDL_Point MousePosition;
         };
// Methods possible callback registry;
         void OnClick();
         void MouseOver();
         void MouseMove();
     }Mouse;

     CallBack CallBacks;

     struct{
         struct keytype{
             int  Modifier;
             int  Code;
             int  ScanCode;
             bool State;
         }Key;
        const Uint8 *KeyState;
    }Keyboard;


    GUI *thisGUI;

    unsigned long           DRAW_COLOR;
	float  FPS;
 

    double TIME;

    //int   FrameCounter;
    int   CYCLE_COUNTER;

    int   CyclePerSecond;
   
    float CYCLE_TIMER;
	float TIMER;

    inline void  Set_Sync_rate(float rate){Sync_rate = rate;}
    inline float Get_Sync_rate(){return Sync_rate;}

private:
    
    float Sync_rate;
    int NumberOfFrames;



    struct
    {
        int NumberOfFrames;
    }FrameCounter;
public:

  void      SYNC               ();
  void      CLS                (); 
  void      CLS                (DWORD col);
  bool      LOOP_GAME          ();

  void      SET_PIXEL          (int, int, Uint32);
  void      SET_PIXELII        (int, int, Uint32);
  void      SET_DRAW_COLOR     (unsigned long Col);
  void      LINE               (int x1,int y1,int x2,int y2);
  void      LINE2              (int x,int y, float Angle,int Length);
  void      CIRCLE             (int x, int y, float radius);
  void      FILLED_CIRCLE      (int x, int y, float radius);
  void      BOX                (int X1, int Y1, int X2, int Y2);
  void      FILLED_BOX         (int X1, int Y1, int X2, int Y2);

  bool      Is_CLICK           (int X, int Y);

  int       WINDOW_OFFSET;
  int       LEFT_BOUNDS;
  int       TOP_BOUNDS;
  int       RIGHT_BOUNDS;
  int       BOTTOM_BOUNDS;

  void      LOCK_PIXELS();
  void      UNLOCK_PIXELS();

  void      PRINT_SCREEN(char *text);
  void      PRINT_FONT(char*);

  float     OldMouseX;
  float     OldMouseY;
            
  void SetGUI(GUI *gui){ thisGUI = gui;}

  SDL_SysWMinfo wmInfo; 

  void AddMenu();
  void AddControls();

  private:
       void EventHandler(SDL_Event &Event);

       bool Active;
       bool Alive;

private:
    float ResizeAspect;
};

extern   Window   *SCREEN; 
extern   bool      SetActiveWindow(Window *active); 



class Widgit
{
public:
    Widgit(){}
    ~Widgit();
   // Widgit::Widgit(Rect dimensions,LPCTSTR text, DWORD style);

    Widgit::Widgit(Window *parent, LPCTSTR type, LPCTSTR text, Rect dimensions, DWORD style , DWORD exstyle);

    Vec2 Position, 
         Size;
    HWND     Handle;
    Window  *Parent;
    LPCTSTR  Type;
    LPCTSTR  Text;
    DWORD    Style;
    DWORD    ExStyle;
    CallBack CallBacks;

    int ID;
    std::vector<Widgit*> Children;

    Widgit *MakeButton  (Rect dimensions,LPCTSTR text, DWORD style);
    Widgit *MakeTextBox (Vec2 pos, Vec2 size);
    Widgit *MakeFrame   (Vec2 pos, Vec2 size);

static int NumberOfWidgits;
static std::vector<Widgit*> WidgitList;
};


 

// WS_EX_CLIENTEDGE 0x00000200L The window has a border with a sunken edge.
//WS_EX_MDICHILD 0x00000040L The window is a MDI child window.
/* WS_GROUP 0x00020000L The window is the first control of a group of controls.
                        The group consists of this first control and all controls defined after it, 
                        up to the next control with the WS_GROUP style. The first control in each group usually 
                        has the WS_TABSTOP style so that the user can move from group to group*/

// WS_HSCROLL - WS_VSCROLL 0x00100000L The window has a scroll bar.

// CREATING CHILD CONTROLS Make a Control that uses the handle of the other control as its menu
//An application specifies the child-window identifier for other types of child windows by setting the hMenu
//    parameter of the CreateWindowEx function to a value rather than a menu handle.


//      HINSTANCE   Class name
//1.	USER32.DLL	Static
//2.	USER32.DLL	Button
//3.	USER32.DLL	Listbox
//4.	USER32.DLL	Combobox
//5.	USER32.DLL	Edit
//6.	A.DLL	    MyClass
//7.	B.DLL	    MyClass
//


class GUI
{
public:
    GUI(){}
   ~GUI()
    {

    }
    GUI(Window *window)
    {
        ParentWindow = window;
    }
    Window *ParentWindow;
    HMENU CurrentMenu;

    struct WidgitStruct
    {
           WidgitStruct(){            
                    Parent           = NULL;
                    Menu             = NULL;
                    Instance         = NULL;
                    Text             = NULL;
                    Type             = NULL;
                    Dimensions       = Rect(0,0,0,0);
                    Style            = NULL;
                    ExtendedStyle    = NULL;
                    lpParam          = nullptr;
                    CB               = CallBack();
                    ID               = NULL;

                    NumberofControls = NULL;
           }

           Window   *Parent;
           HMENU     Menu;
           HINSTANCE Instance;
           LPCTSTR   Text;
           LPCTSTR   Type;
           Rect      Dimensions;
           LPVOID    lpParam;
           CallBack  CB;
           DWORD     Style;
           DWORD     ExtendedStyle;
           int       ID;
           int       NumberofControls;
    } CurrentState;

    std::vector<WidgitStruct> BuildList;

private: 
        int FreeMenuID;
        int FreeButtonID;
static  int FreeInstance;

//____________________________________________________________________________________________________________________
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
public:

    int Button()    
    { 
        CurrentState.Type = "Button"; 
        return 0;
    }
    int TextBox()   
    { 
        CurrentState.Type = "Edit";
        CurrentState.Style |=  WS_BORDER;
        return 0;
    }
    int Frame()     
    { 
        CurrentState.Type = "Static";
        return 0;
    }
    int RadioButton()          
    { 
        CurrentState.Type = "Button";
        CurrentState.Style |= BS_AUTORADIOBUTTON| WS_GROUP ;
      return 0;
    }
    int Menu();

    int Position(int x, int y) 
    { 
        CurrentState.Dimensions.x = x; 
        CurrentState.Dimensions.y = y;
      return 0;
    }
    int Size(int w, int h)     
    { 
        CurrentState.Dimensions.w = w; 
        CurrentState.Dimensions.h = h;
      return 0;
    }
    int LeftMouseDown(void(*func)(int, int))
    {
        CurrentState.CB.SetOnLButtonDown(func);
      return 0;
    }
    int RightMouseDown(void(*func)(int, int))
    {
        CurrentState.CB.SetOnRButtonDown(func);
      return 0;
    }
 
    int Color(int R, int G, int B);
    int Text(LPCTSTR text)
    {
        CurrentState.Text = text;
        return 0;
    }


// Style Commands
    int Style(int style)
    {
        CurrentState.Style |= style;
        return 0;
    }
    int HSCrollBar()
    {
        CurrentState.Style |= WS_HSCROLL;
        return 0;
    }
    int VScrollBar()
    {
        CurrentState.Style |= WS_VSCROLL;
        return 0;
    }
    int Sunkin()
    {
        CurrentState.ExtendedStyle |= WS_EX_CLIENTEDGE;
        return 0;
    }


//  STATE COMMANDS
    int Child();  
    int Push()
    {
        CurrentState.ID = FreeInstance++;
        BuildList.push_back( CurrentState );
        CurrentState.NumberofControls++;
    return 0;
    }
    int Begin()
    {
         CurrentState.Parent = ParentWindow;
         CurrentState.Style |= WS_VISIBLE | WS_CHILD;
    return 0;
    }
    int End()
    {
        //for(auto &Control: BuildList)
        for_loop(Index, CurrentState.NumberofControls)
        {
          // HWND CreateWindow(Control.Type, 
          //                   Control.Text,
          //                   Control.Style,
          //                   Control.Dimensions.x, Control.Dimensions.y, 
          //                   Control.Dimensions.w, Control.Dimensions.h, 
          //                   Control.Parent,
          //                   (HMENU)Control.ID,
          //                   NULL,NULL);
            Widgit *NewControl = new Widgit(BuildList[Index].Parent,
                                            BuildList[Index].Type,
                                            BuildList[Index].Text, 
                                            BuildList[Index].Dimensions, 
                                            BuildList[Index].Style, BuildList[Index].ExtendedStyle);
            NewControl->CallBacks = BuildList[Index].CB;
        }
    return 0;
    }
};

extern bool TERMINATE;


//____________________________________________________________________________________________________________________________________________________________
//---------------------------------- TOOL BOX FUNCTIONS -------------------------------------------------------------------------------------------------- 
//=============================================================================================================================== 


float        FindAngle    (SDL_Point A, SDL_Point B);
inline int   MODULO       (int x, int n);
float        FAST_SQRT    (float X);
bool         Is_CLICK     (int X, int Y);            




template<class T>
class Dynamic
{
public:
    Dynamic(){}
    Dynamic (int c)
    {
        Data = new T[c];
        Count = c;
        Iter = 0;
        Start = Data; 
        Finish = &Data[c];
        Counter = Start;
    }
    int Iter;
    int Size(){return Count;}
    T *Begin(){return Start;}
    //T *End(){return 
    int _Resize(int howmany)
    {
        Count += howmany;

        T *temp = new T[Count];
        Start = temp;
        memcpy(temp, Data, Count);
        delete Data;
        Data = temp;
    }
private:
    int Count;
    T *Data;
    T *Start,
        *Finish,
        *Counter;
};


