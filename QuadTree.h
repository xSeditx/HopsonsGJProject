#pragma once
#include<vector>
#include"Window.h"


enum Direction
{
    NE = 0,
    SE = 1,
    NW = 2,
    SW = 3,
};

class Node;

class Particle
{
public:
        Particle(){}
       ~Particle();
        Particle(Vec2 pos);
        Vec2 Position;
        float Speed;
        float Angle;
        int ID;
        Node *QTnode;
        //long long sdf,tr,sdgfg,sdfgdh,fg,sdfgs,dfgsg,fdsgs,gfasdg,gfds,sdfr,sagf sdf;
        void Render();
static  int ParticleCount;
static  std::vector<Particle *> ParticleList;
static  void RenderAll();
        void ClampPosition();
};


class Node
{
public:
        Node(){}
       ~Node();
        Node(Vec2 Position, Vec2 size);
       
        Vec2 Position;
        Vec2 Size;
       
        Node *SubNodes[4];
        Node *Parent;

        int Capacity;
        bool IsLeaf;
        Direction Facing;
       
        std::vector<Particle *> Entities;

Node* Node::FindAdjacentNode(Direction facing);

        void Subdivide();
        void Render();
        Vec2 NewPos(Vec2 pos, Direction dir);
       
        bool PushDown   (Particle *Object);
        void Moveup     (Particle *Object);
       
        bool Insert     (Particle *object);
        bool IsContained(Particle *object);
        void Prune(Node *node);

        bool Node::Intersects(Vec2 position, Vec2 size);

        Node *FindNorthNeighbor();
std::vector<Particle*> Node::QueryRange(Vec2 position, Vec2 size);
};


class QT{
public:
        QT(){}
       ~QT(){}
        QT(Vec2 Position, Vec2 size);
        Vec2 Position;
        Vec2 Size;
        Node *RootNode;
        void Init();
        void Update();
};