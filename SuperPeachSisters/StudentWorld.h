// A possible interface for StudentWorld.  You may use all, some, or none
// of this, as you wish.

// One of the goals of this design was to reduce the coupling between
// StudentWorld.h and Actor.h as much as possible.  Notice that in fact,
// StudentWorld.h does not need to include Actor.h at all, and knows only
// two of the names in the Actor hierarchy.  (Of course, StudentWorld.cpp
// does need to include Actor.h.)

// Also, no public StudentWorld function returns an Actor pointer to its
// caller.  The goal was that all interactions between actors be mediated
// through StudentWorld.  An actor doesn't do something to another actor
//  directly; it tells StudentWorld to do it on its behalf.

#ifndef STUDENTWORLD_INCLUDED
#define STUDENTWORLD_INCLUDED

#include "GameWorld.h"
#include "Level.h"
#include <string>

class Actor;
class Peach;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();

      // Add an actor to the world.
    void addActor(Actor* a); 
    
      // Record that a level was finished.  The parameter is true if it was
      // the last level.
    void endLevel(bool isGameWon);
    
    void load();

      // If a can move to (destx,desty), move it and return true; otherwise
      // bonk the object that's blockig it and return false.
    bool moveOrBonk(Actor *a, int destx, int desty) const;

      // If a can move to (destx,desty), move it and return true; otherwise,
      // return false.
    bool moveIfPossible(Actor* a, int destx, int desty) const;

      // If a can move to (destx,destx), return true (but don't move it);
      // otherwise (it would be blocked), return false.
    bool isMovePossible(Actor* a, int destx, int desty) const;

      // If Peach overlaps bonker, bonk 'er and return true; otherwise,
      // return false.
    bool bonkOverlappingPeach(Actor* bonker) const;

      // If a non-Peach actor overlaps bonker, bonk that non-Peach actor and
      // return true; otherwise, return false.  (The bonker will be Peach.)
    bool bonkOverlappingActor(Actor* bonker) const;


      // If a non-Peach actor overlaps damager, damage that non-Peach actor
      // and return true; otherwise, return false.
    bool damageOverlappingActor(Actor* damager) const;

      // Return true if a overlaps Peach; otherwise, return false.
    bool overlapsPeach(Actor* a) const;


      // Set Peach's hit points to hp.
    void setPeachHP(int hp) const; //done

      // Grant Peach invincibility for this number of ticks.
    void grantInvincibility(int ticks) const;

      // Grant Peach Shoot Power.
    void grantShootPower() const;

      // Grant Peach Jump Power.
    void grantJumpPower() const;
    
    Peach* getPeach() const;
    
    void findBonkable(Actor* a, int destx, int desty) const;
    
    void displayText();
    
    
private:
    std::vector <Actor*> m_Actors;
    Peach* m_peach;
    
    bool nextLvl;
    bool gameEnded;
};

#endif // STUDENTWORLD_INCLUDED
