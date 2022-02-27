#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

using namespace std;

bool Actor::isDead() const
{
    return m_dead;
}
bool Actor::blocksMovement() const
{
    return false;
}

void Block::getBonked(bool bonkerIsInvinciblePeach)
{
    cerr<<m_g<<endl;
    if(m_g != 0){
        if(m_g == flower)
        {
            Flower* flow = new Flower(world(), getX(), getY() +SPRITE_HEIGHT);
            world()->addActor(flow);
            m_g = none;
        }
        if(m_g == star)
        {
            Star* star = new Star(world(), getX(), getY() + SPRITE_HEIGHT);
            world()->addActor(star);
            m_g = none;
        }
        if(m_g == mushroom)
        {
            Mushroom* mushy = new Mushroom(world(), getX(), getY() + SPRITE_HEIGHT);
            world()->addActor(mushy);
            m_g = none;
        }
    }
    return;
}

void Actor::setDead()
{
    m_dead = true;
}

void Goodie::Gmove()
{
    world() -> moveIfPossible(this, getX(), getY() - 2);
    if(getDirection() == 0){
        if(!world() -> moveIfPossible(this, getX() + 2, getY())){
            setDirection(180);
        }
    }else if(getDirection() == 180)
    {
        if(!world() -> moveIfPossible(this, getX() - 2, getY())){
            setDirection(0);
        }
    }
}



void Peach::gainShootPower()
{
    m_hasShoot = true;
}

void Peach::gainInvincibility(int ticks)
{
    m_invincible = true;
    m_invicibleTime = true;
}

Star::Star(StudentWorld* w, int x, int y)
:Goodie(w, IID_STAR, x, y)
{
    
}



void LevelEnder::doSomething()
{
    return;
}



Actor::Actor(StudentWorld* w, int ID, int x, int y, int dir, int depth)
:GraphObject(ID, x, y)
{
    m_world = w;
    m_dead = false;
}

LevelEnder::LevelEnder(StudentWorld* w, int x, int y, bool isGameEnder)
:Actor(w, IID_FLAG, x, y)
{
    
}

Pipe::Pipe(StudentWorld* w, int x, int y)
:Obstacle(w, IID_PIPE, x, y)
{
    
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
}


bool Obstacle::blocksMovement() const
{
    return true;//TODO: Check
}


void Actor::sufferDamageIfDamageable()
{
    return;
}

int Peach::getHP() const
{
    return m_hp;
}

void Peach::setHP(int hp)
{
    m_hp = hp;
}

void Peach::getBonked(bool a){
    
    if(a){
        return;
    }
    
    setHP(getHP() - 1);
    m_invicibleTime = 10;
    m_hasShoot = false;
    m_hasJump = false;
    world()->playSound(SOUND_PLAYER_HURT);
    
    if(getHP() == 0)
    {
        setDead();
    }
    
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

bool Peach::blocksMovement() const
{
    return false;
}


void Enemy::doSomethingAux()
{
    if(isDead())
    {
        return;
    }
    
    if(world()->overlapsPeach(this))
    {
        world()->getPeach()->getBonked(world()->getPeach()->isInvincible());
        return;
    }
    
    
    if(getDirection() == 0){
        if(!world()->moveIfPossible(this, getX() + 1, getY()))
        {
            setDirection(180);
        }
    }else{
        if(!world()->moveIfPossible(this, getX() - 1, getY())){
            setDirection(0);
        }
    }
    
    return;
}

Enemy::Enemy(StudentWorld* w, int imageID, int x, int y)
:Actor(w, imageID, x, y)
{
    
}

void Enemy::getBonked(bool bonkerIsInvinciblePeach)
{
    return;
}

void Enemy::sufferDamageIfDamageable()
{
    return;
}

Goomba::Goomba(StudentWorld* w, int x, int y)
:Enemy(w, IID_GOOMBA, x, y)
{
    
}

Koopa::Koopa(StudentWorld* w, int x, int y)
:Enemy(w, IID_KOOPA, x, y)
{
    
}

Piranha::Piranha(StudentWorld* w, int x, int y)
:Enemy(w, IID_PIRANHA, x, y)
{
    
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
                        
                        if(hasJumpPower())
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

void Goodie::doSomethingAux()
{
    if(world()->overlapsPeach(this)){
        world()->getPeach()->gainJumpPower();
        setDead();
    }else{
        Gmove();
    }
    return;
}


void Piranha::doSomethingAux()
{
    return;
}
