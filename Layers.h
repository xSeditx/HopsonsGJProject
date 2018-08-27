

#include<list>

#include"sprite.h"






class Layer
{
    Layer(Sprite* img);

    Sprite* Image;

    int ID;

    Vec2 Size;


    static std::vector<Layer*> LayerList;
    static int LayerNumber;
};