#pragma once

#include"window.h"





class VideoCamera
{
public:
        VideoCamera(Vec2 pos, Vec2 size);
       
        Vec2 Position;
        Vec2 ViewPort;
       
        Vec2 Velocity,
             Acceleration,
             Force;
       
       
        void Update();
};