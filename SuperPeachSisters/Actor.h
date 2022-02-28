// Possible interfaces for actors.  You may use all, some, or none
// of this, as you wish.

// One of the goals of this design was to reduce the coupling between
// StudentWorld.h and Actor.h as much as possible.  Notice that in fact,
// Actor.h does not need to include StudentWorld.h at all.  (Of course,
// Actor.cpp does.)

#ifndef ACTOR_INCLUDED
#define ACTOR_INCLUDED

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* sw, int imageID, int x, int y, int dir = right, int depth = 0);

      // Action to perform for each tick.
    void doSomething()
    {
        if (!m_dead){
            doSomethingAux();
        }
    }

      // Bonk this actor.  Parameter says whether bonker is Peach with invincibiity.
    virtual void getBonked(bool bonkerIsInvinciblePeach)
    {}

      // Do what the spec says happens when damage is inflicted on this actor.
    virtual bool sufferDamageIfDamageable();

      // Fall the indicated distance if not blocked.
    void fallIfPossible(int dist);

      // Reverse the direction this actor is facing.
    void reverseDirection();
    
      // Mark this actor as dead.
    virtual void setDead();

      // Is this actor dead?
    bool isDead() const;

      // Does this actor block movement?
    virtual bool blocksMovement() const;

      // Get this actor's world
    StudentWorld* world() const;

      // Set destx and desty to the coordinates dist pixels away in direction
      // dir from this actor's position.
    void converDirectionAndDistanceToXY(int dir, int dist, int& destx, int& desty) const;

private:
    virtual void doSomethingAux() = 0;
    bool m_dead;
    StudentWorld* m_world;
};

class Peach : public Actor
{
public:
    Peach(StudentWorld* w, int x, int y);
    virtual void getBonked(bool bonkerIsInvinciblePeach);
    virtual bool sufferDamageIfDamageable();
    
    bool blocksMovement() const;
    
      // Set Peach's hit points.
    void setHP(int hp);
    
      // Grant Peach invincibility for this number of ticks.
    void gainInvincibility(int ticks);
    
      // Grant Peach Shoot Power.
    void gainShootPower();

      // Grant Peach Jump Power.
    void gainJumpPower();
    
      // Is Peach invincible?
    bool isInvincible() const;
    
      // Does Peach have Shoot Power?
    bool hasShootPower() const;

      // Does Peach have Jump Power?
    bool hasJumpPower() const;
    
    int getHP() const;
    
    
    
private:
    virtual void doSomethingAux();
    int m_jumpDist;
    bool m_hasJump;
    bool m_hasShoot;
    bool m_invincible;
    int m_invicibleTime;
    int m_hp;
    int m_timeToNext;
};

// (Further private sections won't be shown.)

class Obstacle : public Actor
{
public:
    Obstacle(StudentWorld* w, int imageID, int x, int y);
    bool blocksMovement() const;
};

class Block : public Obstacle
{
public:
    enum GoodieType { none, flower, mushroom, star };
    void doSomethingAux();
    Block(StudentWorld* w, int x, int y, GoodieType g = none);
    void getBonked(bool bonkerIsInvinciblePeach);
private:
    GoodieType m_g;
};

class Pipe : public Obstacle
{
public:
    Pipe(StudentWorld* w, int x, int y);
    void doSomethingAux() override;
    void doSomething();
};

class LevelEnder : public Actor
{
public:
    void doSomething();
    void doSomethingAux() override;
    LevelEnder(StudentWorld* w, int x, int y, bool isGameEnder);
};

class Goodie : public Actor
{
public:
    Goodie(StudentWorld* w, int imageID, int x, int y);
    void Gmove();
    void doSomethingAux();
    virtual void gainPower() = 0;
};

class Flower : public Goodie
{
public:
    Flower(StudentWorld* w, int x, int y);
    void gainPower() override;
};

class Mushroom : public Goodie
{
public:
    Mushroom(StudentWorld* w, int x, int y);
    void gainPower() override;
};

class Star : public Goodie
{
public:
    Star(StudentWorld* w, int x, int y);
    void gainPower() override;
};

class Projectile : public Actor
{
public:
    Projectile(StudentWorld* w, int imageID, int x, int y, int dir);
    
};

class PiranhaFireball : public Projectile
{
public:
    PiranhaFireball(StudentWorld* w, int x, int y, int dir);
};

class PeachFireball : public Projectile
{
public:
    void doSomethingAux();
    PeachFireball(StudentWorld* w, int x, int y, int dir);
};

class Shell : public Projectile
{
public:
    void doSomethingAux();
    Shell(StudentWorld* w, int x, int y, int dir);
};

class Enemy : public Actor
{
public:
    Enemy(StudentWorld* w, int imageID, int x, int y, int dir);
    virtual void getBonked(bool bonkerIsInvinciblePeach);
    virtual bool sufferDamageIfDamageable();
    void doSomethingAux();
    bool blocksMovement() const;
};

class Goomba : public Enemy
{
public:
    Goomba(StudentWorld* w, int x, int y);
};

class Koopa : public Enemy
{
public:
    void setDead();
    Koopa(StudentWorld* w, int x, int y);
};

class Piranha : public Enemy
{
public:
    Piranha(StudentWorld* w, int x, int y);
    void doSomethingAux();
private:
    int m_fireDelay; 
};


#endif // ACTOR_INCLUDED
