#include"Layers.h"




    std::vector<Layer*> Layer::LayerList;
    int Layer::LayerNumber = 0;

Layer::Layer(Sprite* img)
{
    Image = img;
    ID = LayerNumber++;
}