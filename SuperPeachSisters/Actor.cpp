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

int Peach::isInvincibleTime() const
{
    return m_invicibleTime;
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

void Koopa::setDead()
{
    if(!this ->isDead())
    {
        Shell* s = new Shell(world(), getX(), getY(), getDirection());
        world()->addActor(s);
        
        Actor::setDead();
    }
    
}

void Shell::doSomethingAux()
{
    if(world()->damageOverlappingActor(this))
    {
        cerr<<"RET"<<endl;
        this->setDead();
        return;
    }
    
    world()->moveIfPossible(this, getX(), getY() - 2);
    cerr<<"GD: "<<getDirection()<<endl;
    if(getDirection() == 0){
        cerr<<"Z Called"<<endl;
        if(!world() -> moveIfPossible(this, getX() + 2, getY())){
            setDead();
            return;
        }
    }else if(getDirection() == 180)
    {
        cerr<<"O Called"<<endl;
        if(!world() -> moveIfPossible(this, getX() - 2, getY())){
            setDead();
            return;
        }
    }
    
    return;
}


Shell::Shell(StudentWorld* w, int x, int y, int dir)
:Projectile(w, IID_SHELL, x, y, dir)
{
    
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
    m_invicibleTime = ticks;
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
:GraphObject(ID, x, y, dir)
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
    m_hp = 1;
    m_timeToNext = 0;
}

Mushroom::Mushroom(StudentWorld* w, int x, int y)
:Goodie(w, IID_MUSHROOM, x, y)
{
}


bool Obstacle::blocksMovement() const
{
    return true;//TODO: Check
}

bool Peach::sufferDamageIfDamageable()
{
    return true;
}


int Peach::getHP() const
{
    return m_hp;
}

void Peach::setHP(int hp)
{
    m_hp = hp;
    if(m_hp == 0){
        setDead();
    }
    return;
}

void Peach::getBonked(bool a){
    
    if(a){
        return;
    }
    int temp = getHP() - 1;
    setHP(temp);
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

bool Enemy::blocksMovement()const
{
    return false;
}

void Peach::removePowers()
{
    m_hasJump = false;
    m_hasShoot = false;
}

void Enemy::doSomethingAux()
{
    if(isDead())
    {
        return;
    }
    
    if(world()->overlapsPeach(this))
    {
        if(!world()->getPeach()->isInvincible())
        {
            if(world()->getPeach()->hasShootPower() || world()->getPeach()->hasJumpPower())
            {
                world()->getPeach()->removePowers();
                world()->getPeach()->gainInvincibility(10);
            }
        }
        world()->getPeach()->getBonked(world()->getPeach()->isInvincible() || world()->getPeach()->isInvincibleTime() > 0);
    }
    
    if(getDirection() == 0){
        if(!world()->isMovePossible(this, getX()+SPRITE_WIDTH-1, getY()-1)){
            
            if(!world()->moveIfPossible(this, getX()+1, getY())){
                setDirection(180);
            }
                
        }else{
            setDirection(180);
        }
    }else{
        if(!world()->isMovePossible(this, getX()-SPRITE_WIDTH+1, getY()-1)){
            
            if(!world()->moveIfPossible(this, getX()-1, getY())){
                setDirection(0);
            }
        }else{
            setDirection(0);
        }
    }
    return;
}

Enemy::Enemy(StudentWorld* w, int imageID, int x, int y, int dir)
:Actor(w, imageID, x, y, dir)
{
    
}

void Enemy::getBonked(bool bonkerIsInvinciblePeach)
{
    return;
}

bool Enemy::sufferDamageIfDamageable()
{
    world()->increaseScore(100);
    this->setDead();
    cerr<<"TITTIES"<<endl;
    return true;
}

Goomba::Goomba(StudentWorld* w, int x, int y)
:Enemy(w, IID_GOOMBA, x, y, (randInt(0, 1) * 180))
{
    
}

Koopa::Koopa(StudentWorld* w, int x, int y)
:Enemy(w, IID_KOOPA, x, y, (randInt(0,1) * 180))
{
    
}

Piranha::Piranha(StudentWorld* w, int x, int y)
:Enemy(w, IID_PIRANHA, x, y, (randInt(0,1) * 180))
{
    m_fireDelay = 0;
}

void Piranha::doSomethingAux()
{
    if(isDead())
    {
        return;
    }
    
    increaseAnimationNumber();
    
    if(world()->overlapsPeach(this))
    {
        world()->getPeach()->getBonked(world()->getPeach()->isInvincible());
    }
    
    int y = this->getY();
    int yMin = y - 1.5 * SPRITE_HEIGHT;
    int yMax = y + 1.5 * SPRITE_HEIGHT;
    
    int pY = world()->getPeach()->getY();
    int pX = world()->getPeach()->getX();
    
    if(!(yMin <= pY && pY <= yMax))
    {
        cerr<<"NOT THE SAME LEVEL: P: "<<y<<endl;
        cerr<<"PEACH Y: "<<pY<<endl;
        return;
    }
    
    if(pX <= this->getX())
    {
        setDirection(180);
    }else if (pX >this->getX()){
        setDirection(0);
    }
    
    if(m_fireDelay > 0)
    {
        m_fireDelay--;
        return;
    }
    
    int sDist = abs(pX - this->getX());
    
    if(sDist < (8* SPRITE_WIDTH))
    {
        PiranhaFireball* pf = new PiranhaFireball(world(), getX(), getY(), getDirection());
        world()->addActor(pf);
        m_fireDelay = 40;
    }

    
    return;
}

PiranhaFireball::PiranhaFireball(StudentWorld* w, int x, int y, int dir)
:Projectile(w, IID_PIRANHA_FIRE, x, y, dir)
{
    
}

void PiranhaFireball::doSomethingAux()
{
    if(world()->overlapsPeach(this))
    {
        world()->getPeach()->getBonked(world()->getPeach()->isInvincible());
        this->setDead();
        return;
    }
    world()->moveIfPossible(this, getX(), getY() - 2);
    
    if(getDirection() == 0){
        cerr<<"Z Called"<<endl;
        if(!world() -> moveIfPossible(this, getX() + 2, getY())){
            setDead();
            return;
        }
    }else if(getDirection() == 180)
    {
        cerr<<"O Called"<<endl;
        if(!world() -> moveIfPossible(this, getX() - 2, getY())){
            setDead();
            return;
        }
    }
    return;
}


void Peach::doSomethingAux()
{
    if(isDead()){
        return;
    }
    
    if(m_invicibleTime != 0)
    {
        m_invicibleTime--;
    }else if(m_invicibleTime == 0){
        m_invincible = false;
    }
    
    if(m_timeToNext > 0)
    {
        m_timeToNext--;
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
                {
                    if(hasShootPower() && m_timeToNext == 0)
                    {
                        m_timeToNext = 8;
                        
                        PeachFireball* pf = new PeachFireball(world(), getX(), getY(), getDirection());
                        world()->addActor(pf);
                    }
                break;
                }
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
        gainPower();
        setDead();
    }else{
        Gmove();
    }
    return;
}

void Flower::gainPower()
{
    world()->getPeach()->gainShootPower();
}

void Mushroom::gainPower()
{
    world()->getPeach()->gainJumpPower();
}

void Star::gainPower()
{
    world()->getPeach()->gainInvincibility(150);
    
}



Projectile::Projectile(StudentWorld* w, int imageID, int x, int y, int dir)
:Actor(w, imageID, x, y, dir)
{
    
}


PeachFireball::PeachFireball(StudentWorld* w, int x, int y, int dir)
:Projectile(w, IID_PEACH_FIRE, x, y, dir)
{
    
}

void PeachFireball::doSomethingAux()
{
    if(world()->damageOverlappingActor(this))
    {
        cerr<<"RET"<<endl;
        this->setDead();
        return;
    }
    
    world()->moveIfPossible(this, getX(), getY() - 2);
    cerr<<"GD: "<<getDirection()<<endl;
    if(getDirection() == 0){
        cerr<<"Z Called"<<endl;
        if(!world() -> moveIfPossible(this, getX() + 2, getY())){
            setDead();
            return;
        }
    }else if(getDirection() == 180)
    {
        cerr<<"O Called"<<endl;
        if(!world() -> moveIfPossible(this, getX() - 2, getY())){
            setDead();
            return;
        }
    }
    
    return;
}

bool Actor::sufferDamageIfDamageable()
{
    return false;
}
