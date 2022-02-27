#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void Block::getBonked(bool bonkerIsInvinciblePeach)
{
    return;
}

bool Actor::isDead() const{
    return m_dead;
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
    m_world = w;
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
    m_jumpDist = 0;
    m_hasJump = false;
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

bool Peach::hasJumpPower() const
{
    return m_hasJump;
}

bool Peach::hasShootPower() const
{
    return m_hasShoot;
}

void Peach::gainJumpPower()
{
    m_hasJump = true;
}



void Peach::doSomethingAux()
{
    if(isDead()){
        return;
    }
    if(m_jumpDist > 0){
        if(world() -> moveOrBonk(this, getX(), getY() + 4)){
            m_jumpDist--;
        }else{
            m_jumpDist = 0;
        }
    }else{
        world() -> moveOrBonk(this, getX(), getY() - 4);
    }
    
        int ch;
        if (world()->getKey(ch))
        {
            switch(ch){
            case KEY_PRESS_LEFT:
                    setDirection(180);
                    world()->moveOrBonk(this, getX() - 4, getY());
                break;
            case KEY_PRESS_RIGHT:
                    setDirection(0);
                    world()->moveOrBonk(this, getX() + 4, getY());
                break;
                    
            case KEY_PRESS_UP:
                {
                    if(world()->isMovePossible(this, getX(), getY()-1))
                    {
                        if(hasShootPower())
                        {
                            m_jumpDist = 12;
                        }else{
                            m_jumpDist = 8;
                        }
                        
                    }
                    break;
                }
            case KEY_PRESS_SPACE:
                break;
            }
        }
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

StudentWorld* Actor::world() const
{
    return m_world;
}
