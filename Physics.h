#pragma once

#include"window.h"


#define     INFINITE_MASS        0xFFFFFFFF


class Mass
{
public:
        Mass(){}
        Mass(float weight, Vec2 pos)
            : Force(0,0),
             Acceleration(0,0),
             Velocity(0,0),
             Kg(weight)
        {
            Position = pos;   
        }
       
        //Mass(float weight,float x, float y)
        //{
        //    Mass(weight, Vec2(x,y));
        //}
       ~Mass(){}
        
        Vec2   Velocity,
               Position, 
               Acceleration,
               Angular,
               Force;
        
        float  Kg;
        
        void Apply_Gravity  ();
        void Apply_Physics  ();
        void Set_Force      (float x, float y);
        void Set_Position   (float x, float y);
        
        Vec2 Get_Position();
        
        inline float Get_X(){return Position.x;}
        inline float Get_Y(){return Position.y;}

        
        struct convert
        {
            inline float Pounds_to_Kg  (float lb) { return lb * .453; }
            inline float Newtons_to_Kg (float N)  { return N / 9.8;   }
            inline float Kg_to_Newtons (float Kg) { return Kg * 9.8;  }
        }Convert;
        struct volume
        {
            inline float ofBox(Vec2 min, Vec2 max){return (max.x - min.x) * (max.y - min.y);}
            //inline float ofBox(AABB &box){return (box.MaxPoint.x - box.MinPoint.x) * (box.MaxPoint.y - box.MinPoint.y) * (box.MaxPoint.z - box.MinPoint.x);}
            inline float ofSphere(float radius){ return (4/3)*(M_PI * (radius*radius*radius));}
        }Volume;


        static void  Set_Timestep(float time){Current_Timestep = time;}
        static void  Set_Gravity(float g){Gravity = g;}
        
        static float Get_Timestep(){return Current_Timestep;}
        static float Get_Gravity(){ return Gravity;}


        static inline float GetDistance(Vec2 p, Vec2 p2)
        {
            return sqrt(Squared(p.x - p2.x) + 
                        Squared(p.y - p2.y));
        }
        

        void inline Update()
        {
                Velocity *= .95f ;         
            
                Vec2  Last_Acceleration = Acceleration;

                Position +=  Velocity *  Mass::Get_Timestep() + (Last_Acceleration * 0.5f * Squared(Mass::Get_Timestep()) );
                Acceleration = Force / Kg;
            
                Force = Vec2(0.0f);
            
                Vec2  Avg_Acceleration = ( Last_Acceleration + Acceleration ) / 2.0f;
                      Velocity += Avg_Acceleration * Mass::Get_Timestep();
         //  Render(); // Possibly for debug
        }

private:
           
        bool Grounded;
        
        static float Current_Timestep;
        static float Gravity; 

// NOTES:

// https://www2.cs.duke.edu/courses/cps124/spring04/notes/12_collisions/collision_detection.pdf
//  Rigid body is represented by:
//________________________________________________
//  – Position x(t)
//  – Rotation R(t)
//  – Linear Momentum P(t)
//  – Angular Momentum L(t)
//------------------------------------------------
//  * New Position:
//  – x (t) = x(t) + v(t), where v(t) = P(t)/Mass
//  – R (t) = w(t)*R(t), where w(t) = I(t)-1L(t)
//  – P (t) = P(t) + F(t)
//  – L (t) = L(t) + T(t)
//------------------------------------------------

};