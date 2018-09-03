#include"window.h"
#include "Collision.h"

//#include "Camera.h"

/*~~~~~~~~~~~~~~~~~~ NOTES ~~~~~~~~~~~~~~~~~~~~*/ 

//  Young's modulus E = Stress / Strain
//                  k = E * (Area / Length)
// angle_deg = RADIANS(acos(Vec3::DotProduct(VectorA.Normalize(), VectorB.Normalize() ))
// Force =  Axis Displacement   * Spring Factor - Damping Factor
 

// Set the default for the Static variables
float Mass::Current_Timestep = 2.0f;
float Mass::Gravity = 0.01f; 


std::vector<Collision> Collision::Solver;
int Collision::NumberOfCollisions = 0;


//=========================================================================================================================
//__________________________________    Collider Base Class   _____________________________________________________________
//-------------------------------------------------------------------------------------------------------------------------

 
std::vector<Collider*> Collider::CollisionList;
int Collider::NumberOfObjects = 0;


//=========================================================================================================================
//___________________________    BoundingSphere Collision Detector    _____________________________________________________
//-------------------------------------------------------------------------------------------------------------------------


CollisionSphere::CollisionSphere(Vec2 position, float radius)
    : 
      Radius(radius)
{
     Position = position;

     Body = Mass(radius, position);

     Size = Vec2(Radius);

     ID = NumberOfObjects++;

     Type = ColliderCOLLISIONSPHERE;

//     CollisionList.push_back(this);  

}


bool CollisionSphere::IsCollision( CollisionSphere *other)   // Use to return a float, might go back to doing that
{ 
    if(other->ID != this->ID)
    {
        float Distance = sqrt(Squared(other->Position.x - Position.x) +
                              Squared(other->Position.y - Position.y));

        if(Distance < (Radius + other->Radius))
        {
            float  Displacement = .5f * (Distance - this->Size.x  - other->Size.x );
      
             this->Body.Position -= (this->Body.Position - other->Body.Position) * Displacement  / Distance;
            other->Body.Position += (this->Body.Position - other->Body.Position) * Displacement  / Distance;


          return true;
        }
    }
  return false;
}
bool CollisionSphere::IsCollision( AABB *other)  
{ 
    if(other->ID != this->ID)
    {
        Vec2 Point = Vec2(std::max(other->MinPoint.x, std::min(Body.Position.x, other->MaxPoint.x)),
                          std::max(other->MinPoint.y, std::min(Body.Position.y, other->MaxPoint.y)));


        float Distance = sqrt(Squared( Body.Position.x - Point.x) +
                              Squared( Body.Position.y - Point.y));

        if(Distance < Radius)
        {
            float  Displacement = .5f * (Distance - this->Size.x  - other->Size.x );
              
             this->Body.Position -= (this->Body.Position - other->Body.Position) * Displacement  / Distance;
            other->Body.Position += (this->Body.Position - other->Body.Position) * Displacement  / Distance;

          return true;
        }
    }
  return false;
}
bool CollisionSphere::IsCollision( Collider *other)  
{ 
    if(other->ID != this->ID)
    {
        return other->IsCollision(this);
    }
  return false;
}
bool CollisionSphere::IsCollision(Vec2 point) 
{
    float Distance = sqrt((point.x - Position.x) * (point.x - Position.x) +
                          (point.y - Position.y) * (point.y - Position.y));
    return Distance < Radius;
}

void CollisionSphere::Sweep() 
{  

//ODDS ARE i AM GOING TO DITCH THE QUADTREE AND USE A GRID SYSTEM. EACH ENTITY WILL BE ON PART OF THE GRID WORLD AND i ONLY HAVE TO TEST 
// THE GRID I AM ON AND ITS NEIGHBORS. IF I FIND I HAVE TO MANY ENTITIES THAN I WILL CROSS THAT BRIDGE WHEN I GET
// TO IT BUT FOR NOW I BELIEVE THIS WILL BE THE MOST EFFECTIVE WAY.

     std::vector<Collider*> results; // Checks the area around the object in the Quadtree and returns andthing in the same Sector
 //    results = Tree->RootNode->QueryRange(Vec2(Body.Position.x, Body.Position.z),Vec2(10,10));

     for(Collider *Other: results)
     {
         if(Other != this) // This is quite possible my Object->ID check, I think I am checking twice on accident.
         {
             if(IsCollision(Other))
             {
                 Collision::Add(this, Other);
                 Print("Sphere Collision:");// React to that Collision in some way by writing a Physics Module. 
             }
         }
     }
}
void CollisionSphere::Update()
{

//====================================================================================================================================
//                                          Physics stuff to be soon moved elseware                                                                 
//====================================================================================================================================
// Body.Velocity.y += Mass::Get_Gravity();
//
//    Body.Velocity = Body.Velocity * .95f ;         
//
//    Vec2  Last_Acceleration = Body.Acceleration;
//          Body.Position += Body.Velocity *  Mass::Get_Timestep() + ( Last_Acceleration * 0.5f * Squared(Mass::Get_Timestep()) );
//          Body.Acceleration = Body.Force / Body.Kg;
//
//    Body.Force = Vec2(0.0f);
//
//    Vec2  Avg_Acceleration = ( Last_Acceleration + Body.Acceleration ) / 2.0f;
//          Body.Velocity += Avg_Acceleration * Mass::Get_Timestep();
//
    Body.Update();
//====================================================================================================================================

    //if(Object)Object->Position = Body.Position; UNBLOCK THIS FIX THE POSITION IN ENTITY
    Position = Body.Position;
#if DEBUG_COLLISIONBOX
    Render(); // Shows the Collision Box
#endif
 //   Sweep();  // Horrible naming just Temp until I have everything in place. 
}
void CollisionSphere::Render()
{

}




//=========================================================================================================================
//___________________________      AABB Collision Detector    _____________________________________________________________
//-------------------------------------------------------------------------------------------------------------------------

AABB::AABB(Vec2 position, Vec2 size)
{

    Position = position;

    Body = Mass(10, position);

    ID = NumberOfObjects++;

    Size = size;

    Vec2 max =  position + size, 
         min =  position - size;

    MaxPoint = max;
    MinPoint = min;

    Type = ColliderAABB;

// Dont really need the Surface Area calculations right now anyway if I am not going to create an AABB tree
//    SurfaceArea = 2.0f * (GetWidth() * GetHeight() + GetWidth()* GetDepth() + GetHeight()* GetDepth());
//    CollisionList.push_back(this);
}

bool AABB::IsCollision( Collider *other)  
{ 
    if(other->ID != this->ID)
    {
        return other->IsCollision(this);
    }
  return false;
}
bool AABB::IsCollision( AABB *other)  
{ 
    if(other->ID != this->ID)
    {
        bool ret = (MinPoint.x <= other->MaxPoint.x && MaxPoint.x >= other->MinPoint.x) &&
                   (MinPoint.y <= other->MaxPoint.y && MaxPoint.y >= other->MinPoint.y);                   //Intersect(*this, *other);
        if(ret == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
  return false;
}
bool AABB::IsCollision( CollisionSphere *other)  
{ 
    if(other->ID != this->ID)
    {
        return other->IsCollision(this);
    }
  return false;
}
bool AABB::IsCollision( Vec2 point)
{
  return (point.x >=  std::min(MinPoint.x, MaxPoint.x) && point.x <=  std::max(MinPoint.x, MaxPoint.x)) &&
         (point.y >=  std::min(MinPoint.y, MaxPoint.y) && point.y <=  std::max(MinPoint.y, MaxPoint.y));
}

bool AABB::Overlaps( AABB& other) 
{
	return(MaxPoint.x > other.MinPoint.x && // Possibly test one at a time to allow for Dropout
		   MinPoint.x < other.MaxPoint.x && // Do not know if it occurs in this form.
		   MaxPoint.y > other.MinPoint.y &&
		   MinPoint.y < other.MaxPoint.y);
}
bool AABB::Contains( AABB& other) 
{
	return other.MinPoint.x >= MinPoint.x &&
		other.MaxPoint.x <= MaxPoint.x &&
		other.MinPoint.y >= MinPoint.y &&
		other.MaxPoint.y <= MaxPoint.y;
}
bool AABB::Intersect(AABB a, AABB b) 
{
    return 
        ((std::min(a.MinPoint.x, a.MaxPoint.x) <= std::max(b.MinPoint.x, b.MaxPoint.x) && std::max(a.MinPoint.x, a.MaxPoint.x) >= std::min(b.MinPoint.x, b.MaxPoint.x)) &&
         (std::min(a.MinPoint.y, a.MaxPoint.y) <= std::max(b.MinPoint.y, b.MaxPoint.y) && std::max(a.MinPoint.y, a.MaxPoint.y) >= std::min(b.MinPoint.y, b.MaxPoint.y)));
}   

AABB AABB::Merge(AABB& other) // Careful I might have something wrong here;
{
    Vec2 Min = Vec2(std::min(MinPoint.x, other.MinPoint.x), std::min(MinPoint.y, other.MinPoint.y)), 
         Max = Vec2(std::max(MaxPoint.x, other.MaxPoint.x), std::max(MaxPoint.y, other.MaxPoint.y));
    
    Vec2 position = (MinPoint + MaxPoint) *  0.5f;
    Vec2 Length = MaxPoint - MinPoint;

  return AABB(position - Length, position + Length);
}
void AABB::Update()
{                                 
    MaxPoint = Position + Size;   
    MinPoint = Position - Size; 

    Body.Update();
    Position = Body.Position;
#if DEBUG_COLLISIONBOX
    Render();
#endif

}
void AABB::Render()
{
    SDL_SetRenderDrawColor(SCREEN->Renderer,255,0,0,255);
    SDL_Rect Box = { MinPoint.x, MinPoint.y,  MaxPoint.x - MinPoint.x, MaxPoint.y -MinPoint.y};
    SDL_RenderDrawRect(SCREEN->Renderer, &Box);
}
void AABB::Sweep() 
 {  
 //   std::vector<Collider*> results;
//Currently testing Every StaticSprite against every sprite... Should I? This is a performance issue to be managed later I guess.
 // I Tested 100x100 before so I should have enough perfomance to not worry about it
    for(Collider *Other: CollisionList)
    {
        if(Other != this)
        { 
            if( IsCollision(Other))
            {
                Collision::Add(this, Other);
                Print("AABB Collision");// React to that Collision in some way by writing a Physics Module. 
            }
        }
    }
}




//=========================================================================================================================
//___________________________      Collision Solver    ____________________________________________________________________
//-------------------------------------------------------------------------------------------------------------------------



Collision::Collision( Collider *object1, Collider *object2)
{
        Object1 = object1;      
        Object2 = object2;   

        Position = object1->Body.Position; // Change this later. I want the Point exactly where the collision occured not the center of this as this is kind of pointless right now.
        Distance = Collider::GetDistance(object1->Body.Position, object2->Body.Position);
}
void Collision::Clear()
{
    Solver.clear();
}
void Collision::Add( Collider *object1,  Collider *object2)
{
    Vec2 Point = (object1->Body.Position +  object2->Body.Position) * 0.5f; // Average between the two Colliding bodies. Use this for debugging to show where the best chance of a collision being in the future.
    Solver.push_back(Collision(object1, object2));
}
void Collision::Resolve()
{
    for(auto &Pair: Solver)
    {
        Vec2 Normals = glm::normalize(Pair.Object1->Body.Position - Pair.Object2->Body.Position);
        
        float a1 = glm::dot(Pair.Object1->Body.Velocity, Normals);
        float a2 = glm::dot(Pair.Object2->Body.Velocity, Normals);
        
        float optimizedP = (2.0 * (a1 - a2)) / (Pair.Object1->Body.Kg + Pair.Object2->Body.Kg);
        
        Vec2 v1 = Pair.Object1->Body.Velocity - optimizedP * Pair.Object2->Body.Kg * Normals;
        Vec2 v2 = Pair.Object2->Body.Velocity + optimizedP * Pair.Object1->Body.Kg * Normals;
        
        Pair.Object1->Body.Velocity = v1;
        Pair.Object2->Body.Velocity = v2;
    }
    Clear();
}
