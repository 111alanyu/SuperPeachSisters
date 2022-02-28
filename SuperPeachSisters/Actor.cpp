#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

using namespace std;

/*----------------ACTOR----------------*/

Actor::Actor(StudentWorld* w, int ID, int x, int y, int dir, int depth)
:GraphObject(ID, x, y, dir)
{
    m_world = w;
    m_dead = false;
}


bool Actor::isDead() const
{
    return m_dead;
}
bool Actor::blocksMovement() const
{
    return false;
}

void Actor::setDead()
{
    m_dead = true;
}

StudentWorld* Actor::world() const
{
    return m_world;
}

bool Actor::sufferDamageIfDamageable()
{
    return false;
}


/*-------------PEACH-----------------*/

Peach::Peach(StudentWorld *w, int x, int y)
:Actor(w, IID_PEACH, x, y)
{
    m_jumpDist = 0;
    m_hasJump = false;
    m_hasStar = false;
    m_hasShoot = false;
    m_hp = 1;
    m_timeToNext = 0;
    m_invicibleTime = 0;
    m_tempInvTime = 0;
}

void Peach::setTempInvis(int num)
{
    m_tempInvTime = num;
}

bool Peach::hasStarPower()const
{
    return m_hasStar;
}

bool Peach::isInvincible() const
{
    if(m_invicibleTime > 0 || m_tempInvTime > 0){
        return true;
    }else{
        return false;
    }
}


void Peach::gainStarPower()
{
    m_hasStar = true;
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

void Peach::gainShootPower()
{
    m_hasShoot = true;
}

void Peach::gainInvincibility(int ticks)
{
    m_invicibleTime = ticks;
}


void Peach::getBonked(bool a)
{
    
    if(!a)
    {
        if(world()->getPeach()->hasShootPower() || world()->getPeach()->hasJumpPower())
        {
            world()->playSound(SOUND_PLAYER_HURT);
            world()->getPeach()->removePowers();
            world()->getPeach()->setTempInvis(10); //TODO: REMOVE 100 to 10
        }
    }
    
    if(world()->getPeach()->isInvincible())
    {
        return;
    }
    
    
    world()->playSound(SOUND_PLAYER_DIE);
    setHP(getHP() - 1);
    
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


void Peach::doSomethingAux()
{
    if(isDead()){
        return;
    }
    
    if(m_invicibleTime != 0)
    {
        m_invicibleTime--;
    }else if(m_invicibleTime == 0){
        m_hasStar = false;
    }
    
    
    if(m_tempInvTime != 0)
    {
        m_tempInvTime--;
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
                        world()->playSound(SOUND_PLAYER_JUMP);
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
                        world()->playSound(SOUND_PLAYER_FIRE);
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

/*-------------OBSTICLE------------*/
Obstacle::Obstacle(StudentWorld* w, int imageID, int x, int y)
:Actor(w, imageID, x, y)
{
    
}

bool Obstacle::blocksMovement() const
{
    return true;//TODO: Check
}


/*---BLOCK---*/
Block::Block(StudentWorld* w, int x ,int y, GoodieType g)
:Obstacle(w, IID_BLOCK, x, y)
{
    m_g = g;
}

void Block::doSomethingAux()
{
    return;
}

void Block::getBonked(bool bonkerIsInvinciblePeach)
{
    if(m_g != 0){
        world()->playSound(SOUND_POWERUP_APPEARS);
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
    }else{
        world()->playSound(SOUND_PLAYER_BONK);
    }
    return;
}


/*---PIPE---*/
Pipe::Pipe(StudentWorld* w, int x, int y)
:Obstacle(w, IID_PIPE, x, y)
{
    
}

void Pipe::doSomethingAux()
{
    return;
}




/*----------LEVEL ENDER-------------*/

void LevelEnder::doSomethingAux()
{
    if(isDead())
    {
        return;
    }
    
    if(world()->overlapsPeach(this))
    {
        world()->increaseScore(1000);
        this->setDead();
        world()->endLevel(m_isLvlEnder);
        world()->playSound(SOUND_FINISHED_LEVEL);
        
    }
    return;
}

LevelEnder::LevelEnder(StudentWorld* w, int imageID, int x, int y, bool isGameEnder)
:Actor(w, imageID, x, y)
{
    m_isLvlEnder = isGameEnder;
}


/*---------GOODIE----------------*/

Goodie::Goodie(StudentWorld* w, int imageID, int x, int y)
:Actor(w, imageID, x, y)
{
    
}

void Goodie::doSomethingAux()
{
    if(world()->overlapsPeach(this)){
        world()->playSound(SOUND_PLAYER_POWERUP);
        gainPower();
        setDead();
    }else{
        Gmove();
    }
    return;
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

/*---FLOWER---*/
Flower::Flower(StudentWorld* w, int x, int y)
:Goodie(w, IID_FLOWER, x, y)
{
    
}

void Flower::gainPower()
{
    world()->increaseScore(50);
    world()->getPeach()->gainShootPower();
}

/*---MUSHROOM---*/
Mushroom::Mushroom(StudentWorld* w, int x, int y)
:Goodie(w, IID_MUSHROOM, x, y)
{
}



void Mushroom::gainPower()
{
    world()->increaseScore(75);
    world()->getPeach()->gainJumpPower();
}

/*---STAR---*/
Star::Star(StudentWorld* w, int x, int y)
:Goodie(w, IID_STAR, x, y)
{
    
}



void Star::gainPower()
{
    world()->increaseScore(100);
    world()->getPeach()->gainStarPower();
    world()->getPeach()->gainInvincibility(150);
}



/*---------PROJECTILE-----------------*/
Projectile::Projectile(StudentWorld* w, int imageID, int x, int y, int dir)
:Actor(w, imageID, x, y, dir)
{
    
}

/*---Pir FIREBALL---*/
PiranhaFireball::PiranhaFireball(StudentWorld* w, int x, int y, int dir)
:Projectile(w, IID_PIRANHA_FIRE, x, y, dir)
{
    
}

void PiranhaFireball::doSomethingAux()
{
    if(isDead())
    {
        return;
    }
    
    if(world()->overlapsPeach(this))
    {
        if(world()->getPeach()->hasStarPower())
        {
            world()->playSound(SOUND_PLAYER_KICK);
            this->setDead();
            
            return;
        }
        
        setDead();
        world()->getPeach()->getBonked(world()->getPeach()->isInvincible());
        return;
    }
    
    world()->moveIfPossible(this, getX(), getY() - 2);
    
    if(getDirection() == 0){
        if(!world() -> moveIfPossible(this, getX() + 2, getY())){
            setDead();
            return;
        }
    }else if(getDirection() == 180)
    {
        if(!world() -> moveIfPossible(this, getX() - 2, getY())){
            setDead();
            return;
        }
    }
    return;
}

/*---Pe FIREBALL---*/
PeachFireball::PeachFireball(StudentWorld* w, int x, int y, int dir)
:Projectile(w, IID_PEACH_FIRE, x, y, dir)
{
    
}

void PeachFireball::doSomethingAux()
{
    if(world()->damageOverlappingActor(this))
    {
        this->setDead();
        return;
    }
    
    world()->moveIfPossible(this, getX(), getY() - 2);
    if(getDirection() == 0){
        if(!world() -> moveIfPossible(this, getX() + 2, getY())){
            setDead();
            return;
        }
    }else if(getDirection() == 180)
    {
        if(!world() -> moveIfPossible(this, getX() - 2, getY())){
            setDead();
            return;
        }
    }
    
    return;
}



/*---SHELL---*/
void Shell::doSomethingAux()
{
    if(world()->damageOverlappingActor(this))
    {
        this->setDead();
        return;
    }
    
    world()->moveIfPossible(this, getX(), getY() - 2);
    if(getDirection() == 0){
        if(!world() -> moveIfPossible(this, getX() + 2, getY())){
            setDead();
            return;
        }
    }else if(getDirection() == 180)
    {
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








/*-----------------ENEMY-----------------------*/
void Enemy::doSomethingAux()
{
    if(isDead())
    {
        return;
    }
    
    if(world()->overlapsPeach(this))
    {
        if(world()->getPeach()->hasStarPower())
        {
            world()->playSound(SOUND_PLAYER_KICK);
            this->setDead();
            
            return;
        }
        
        world()->getPeach()->getBonked(world()->getPeach()->isInvincible());
        return;
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
    if(world()->getPeach()->isInvincible())
    {
        world()->playSound(SOUND_PLAYER_KICK);
        world()->increaseScore(100);
        this->setDead();
        return;
    }
    return;
}

bool Enemy::sufferDamageIfDamageable()
{
    world()->increaseScore(100);
    this->setDead();
    return true;
}


/*---GOOMBA---*/
Goomba::Goomba(StudentWorld* w, int x, int y)
:Enemy(w, IID_GOOMBA, x, y, (randInt(0, 1) * 180))
{
    
}

/*---Koopa---*/
Koopa::Koopa(StudentWorld* w, int x, int y)
:Enemy(w, IID_KOOPA, x, y, (randInt(0,1) * 180))
{
    
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

/*---Piranha---*/
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
        if(world()->getPeach()->hasStarPower())
        {
            this->setDead();
            return;
        }
        world()->getPeach()->getBonked(world()->getPeach()->isInvincible());
        return;
    }
    
    int y = this->getY();
    int yMin = y - 1.5 * SPRITE_HEIGHT;
    int yMax = y + 1.5 * SPRITE_HEIGHT;
    
    int pY = world()->getPeach()->getY();
    int pX = world()->getPeach()->getX();
    
    if(!(yMin <= pY && pY <= yMax))
    {
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
        world()->playSound(SOUND_PIRANHA_FIRE);
        m_fireDelay = 40;
    }

    
    return;
}

