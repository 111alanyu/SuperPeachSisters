#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

using namespace std;
void Block::getBonked(bool bonkerIsInvinciblePeach)
{
    cerr<<m_g<<endl;
    if(m_g != 0){
        if(m_g == flower)
        {
            Flower* flow = new Flower(world(), getX(), getY() +SPRITE_HEIGHT);
            world()->addActor(flow);
        }
        if(m_g == star)
        {
            Star* star = new Star(world(), getX(), getY() + SPRITE_HEIGHT);
            world()->addActor(star);
        }
        if(m_g == mushroom)
        {
            Mushroom* mushy = new Mushroom(world(), getX(), getY() + SPRITE_HEIGHT);
            world()->addActor(mushy);
        }
    }
    return;
}

void Mushroom::doSomethingAux()
{
    return;
}

void Flower::doSomethingAux()
{
    return;
}

void Star::doSomethingAux()
{
    return;
}

Star::Star(StudentWorld* w, int x, int y)
:Goodie(w, IID_STAR, x, y)
{
    
}

bool Actor::isDead() const{
    return m_dead;
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
    m_g = g;
}

Flower::Flower(StudentWorld* w, int x, int y)
:Goodie(w, IID_FLOWER, x, y)
{
    
}

Peach::Peach(StudentWorld *w, int x, int y)
:Actor(w, IID_PEACH, x, y)
{
    m_jumpDist = 0;
    m_hasJump = false;
    m_invincible = false;
}

Mushroom::Mushroom(StudentWorld* w, int x, int y)
:Goodie(w, IID_MUSHROOM, x, y)
{
    cerr<<"MUSHROOM CONSTRUCTOR CALLED"<<endl;
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

void Block::doSomethingAux()
{
    return;
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
        world() -> moveIfPossible(this, getX(), getY() - 4);
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
                    
                    if(!world()->isMovePossible(this, getX(), getY()-1))
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


bool Peach::isInvincible() const
{
    return m_invincible;
}

Goodie::Goodie(StudentWorld* w, int imageID, int x, int y)
:Actor(w, imageID, x, y)
{
    
}
