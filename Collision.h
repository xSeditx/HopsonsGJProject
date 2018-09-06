#pragma once

#include<vector>
#include"Window.h"
#include"Physics.h"


#define DEBUG_COLLISIONBOX  1




const float Time_Limit = 16.667f / 1000.0f;


enum ColliderType
{
    ColliderUNKNOWN = 0,
    ColliderAABB,
    ColliderCOLLISIONSPHERE,
    ColliderPVP,
    ColliderTERRAIN,
    ColliderOBB,
    ColliderConvexHull
};

class AABB;
class CollisionSphere;
class Terrain;
class TerrainCollider;



struct Collision;





class Collider
{
public:
        Collider(){}

        int ID;       

        Vec2 Position;

//        Entity *Object; 
        
        Mass Body;
        
        ColliderType Type;

        Vec2 Size;


        virtual bool IsCollision( Collider        *other) = 0;
        virtual bool IsCollision( AABB            *other) = 0;
        virtual bool IsCollision( CollisionSphere *other) = 0;

        virtual bool IsCollision( Vec2 point) = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void Sweep()  = 0;

// Static Methods and Variables
        static std::vector<Collider*> CollisionList;
        static int NumberOfObjects;

 static float GetDistance(Vec2 p, Vec2 p2)
 {
     return sqrt(Squared(p.x - p2.x) + Squared(p.y-p2.y));
 }

};
class CollisionSphere: public Collider 
{
public:
  //      CollisionSphere(float radius); // ORIGINAL         CollisionSphere(Mesh  *object, float radius);
        CollisionSphere(Vec2 Position, float radius);

        float Radius;

        bool IsCollision( CollisionSphere *other)  override;
        bool IsCollision( AABB            *other)  override;
        bool IsCollision( Collider        *other)  override;

        bool IsCollision(Vec2 point);

        void Update();
        void Render();
        void Sweep() override;
};


class AABB: public Collider
{
public:
        AABB(){Type = ColliderAABB;}

        AABB(Vec2 position, Vec2 size);// Center Radius ORIGINAL:   AABB(Mesh *object, Vec3 position, Vec3 size)

        Vec2 MinPoint, 
             MaxPoint;

        float SurfaceArea;

        bool IsCollision( AABB            *other)  override;     
        bool IsCollision( CollisionSphere *other)  override;
        bool IsCollision( Collider        *other)  override;

        bool IsCollision(Vec2 point);
        bool Contains(AABB& other); 
        bool Overlaps(AABB& other);

        AABB Merge(AABB& other);
//       AABB IntersectPoints(AABB& b); 

        void Update();
        void Render();
        void Sweep() override;

inline float GetWidth()  const { return MaxPoint.x - MinPoint.x; }
inline float GetHeight() const { return MaxPoint.y - MinPoint.y; }

static bool Intersect(AABB a, AABB b);

};



struct Collision
{
    Collision( Collider *object1,  Collider *object2);
    Collision();

    float Distance;

    Vec2 Position;

    ColliderType Type1,  
                 Type2;

    Collider *Object1,
             *Object2;

static void Clear();
static void Add( Collider *object1,  Collider *object2);
static void Resolve();

static std::vector<Collision> Solver;
static int NumberOfCollisions;
};
