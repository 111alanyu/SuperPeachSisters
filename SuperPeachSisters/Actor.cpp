#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void Block::getBonked(bool bonkerIsInvinciblePeach)
{
    return;
}


void Block::doSomethingAux()
{
    return;
}

void LevelEnder::doSomething()
{
    return;
}

Actor::Actor(StudentWorld* w, int ID, int x, int y, int dir, int depth)
:GraphObject(ID, x, y)
{
    
}

LevelEnder::LevelEnder(StudentWorld* w, int x, int y, bool isGameEnder)
:Actor(w, IID_FLAG, x, y)
{
    
}

Pipe::Pipe(StudentWorld* w, int x, int y)
:Obstacle(w, IID_PIPE, x, y){
    
}

Obstacle::Obstacle(StudentWorld* w, int imageID, int x, int y)
:Actor(w, imageID, x, y)
{
    
}

Block::Block(StudentWorld* w, int x ,int y, GoodieType g)
:Obstacle(w, IID_BLOCK, x, y)
{
    
}

Peach::Peach(StudentWorld *w, int x, int y)
:Actor(w, IID_PEACH, x, y)
{
    
}

bool Obstacle::blocksMovement() const
{
    return true;//TODO: Check
}

bool Actor::blocksMovement() const
{
    return false;
}

void Actor::sufferDamageIfDamageable()
{
    return;
}

void Peach::getBonked(bool a){
    return;
}


void Peach::sufferDamageIfDamageable()
{
    return;
}

void Peach::doSomethingAux()
{
    return;
}

void Pipe::doSomethingAux()
{
    return;
}

void LevelEnder::doSomethingAux()
{
    return;
}
