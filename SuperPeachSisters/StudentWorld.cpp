#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <sstream>
using namespace std;


GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    gameEnded = false;
    nextLvl = false;
}


int StudentWorld::init()
{
    load();
    return GWSTATUS_CONTINUE_GAME;
}

Peach* StudentWorld::getPeach() const
{
    return m_peach;
}



bool StudentWorld::moveOrBonk(Actor *a, int destx, int desty) const
{
    if(moveIfPossible(a, destx, desty)){
        return true;
    }else{
        cerr<<"FIND"<<endl;
        findBonkable(a, destx, desty);
        return false;
    }
    
}

void StudentWorld::findBonkable(Actor* a, int destx, int desty) const
{
    for(int i = 0; i < m_Actors.size(); i++)
    {
        int x1 = destx;
        int y1 = desty;

        int x2 = m_Actors[i]->getX();
        int y2 = m_Actors[i]->getY();

        int x1_Extend = x1 + SPRITE_WIDTH - 1;
        int y1_Extend = y1 + SPRITE_HEIGHT -1;

        int x2_Extend = x2 + SPRITE_WIDTH - 1;
        int y2_Extend = y2 + SPRITE_HEIGHT - 1;
        
        if((x2 <= x1 && x1 <= x2_Extend) || (x2 <= x1_Extend && x1_Extend <= x2_Extend)){
            if((y2 <= y1 && y1 <= y2_Extend) || (y2 <= y1_Extend && y1_Extend <= y2_Extend)){
                m_Actors[i]->getBonked(getPeach()->isInvincible());
                return;
            }
        }

    }
    
    return;
}

void StudentWorld::addActor(Actor* a)
{
    m_Actors.push_back(a);
    return;
}

bool StudentWorld::moveIfPossible(Actor *a, int destx, int desty) const
{
    if(isMovePossible(a, destx, desty)){
        a->moveTo(destx, desty);
        return true;
    }else{
        return false;
    }
}


bool StudentWorld::isMovePossible(Actor *a, int destx, int desty) const
{
    
    for(int i = 0; i < m_Actors.size(); i++)
    {
        int x1 = destx;
        int y1 = desty;

        int x2 = m_Actors[i]->getX();
        int y2 = m_Actors[i]->getY();

        int x1_Extend = x1 + SPRITE_WIDTH - 1;
        int y1_Extend = y1 + SPRITE_HEIGHT -1;

        int x2_Extend = x2 + SPRITE_WIDTH - 1;
        int y2_Extend = y2 + SPRITE_HEIGHT - 1;
        
        /* DEBUG TOOLS*/
        /*
        cerr<<x1<<endl;
        cerr<<y1<<endl;
        cerr<<x1_Extend<<endl;
        cerr<<y1_Extend<<endl;
        
        cerr<<endl;
        
        cerr<<x2<<endl;
        cerr<<y2<<endl;
        cerr<<x2_Extend<<endl;
        cerr<<y2_Extend<<endl;
        
        cerr<<endl;
        cerr<<"------------------------"<<endl;
        cerr<<endl;
        
         */
        if(m_Actors[i] ->blocksMovement()){
            if((x2 <= x1 && x1 <= x2_Extend) || (x2 <= x1_Extend && x1_Extend <= x2_Extend)){
                if((y2 <= y1 && y1 <= y2_Extend) || (y2 <= y1_Extend && y1_Extend <= y2_Extend)){
                    return false;
                }
            }
        }
    }
    
    return true;
}

bool StudentWorld::bonkOverlappingActor(Actor *bonker)const
{
    if(overlapsPeach(bonker))
    {
        bonker -> getBonked(m_peach -> isInvincible());
        return true;
    }else{
        return false;
    }
    
}

bool StudentWorld::bonkOverlappingPeach(Actor* bonker)const
{
    if(overlapsPeach(bonker))
    {
        bonker->getBonked(m_peach -> isInvincible());
        return true;
    }else{
        return false;
    }
}

bool StudentWorld::overlapsPeach(Actor *a) const
{
    int x1 = getPeach()->getX();
    int y1 = getPeach()->getY();

    int x2 = a->getX();
    int y2 = a->getY();

    int x1_Extend = x1 + SPRITE_WIDTH - 1;
    int y1_Extend = y1 + SPRITE_HEIGHT -1;

    int x2_Extend = x2 + SPRITE_WIDTH - 1;
    int y2_Extend = y2 + SPRITE_HEIGHT - 1;
    
    /* DEBUG TOOLS*/
    /*
    cerr<<x1<<endl;
    cerr<<y1<<endl;
    cerr<<x1_Extend<<endl;
    cerr<<y1_Extend<<endl;
    
    cerr<<endl;
    
    cerr<<x2<<endl;
    cerr<<y2<<endl;
    cerr<<x2_Extend<<endl;
    cerr<<y2_Extend<<endl;
    
    cerr<<endl;
    cerr<<"------------------------"<<endl;
    cerr<<endl;
    
     */
    
    if((x2 <= x1 && x1 <= x2_Extend) || (x2 <= x1_Extend && x1_Extend <= x2_Extend)){
        if((y2 <= y1 && y1 <= y2_Extend) || (y2 <= y1_Extend && y1_Extend <= y2_Extend)){
            return true;
        }
    }
    return false;
}

void StudentWorld::displayText()
{
    ostringstream a;
    string star = "";
    string jump = "";
    string fire = "";
    
    if(m_peach->hasJumpPower())
    {
        jump = " JumpPower!";
    }
    
    if(m_peach->hasShootPower()){
        fire = " ShootPower!";
    }
    
    if(m_peach-> hasStarPower()){
        star = " StarPower!";
    }
    
    a.fill('0');
    a << "Lives: " <<getLives()<< "  Level: " << setw(2) << getLevel() << "  Points: " << setw(6) << getScore() << star << fire << jump;
    
    string game = a.str();
    setGameStatText(game);
}

int StudentWorld::move()
{
    displayText();
    
    if(m_peach -> isDead())
    {
        playSound(SOUND_PLAYER_DIE);
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    for(int i = 0; i < m_Actors.size(); i++){
        if(!m_Actors[i]->isDead()){
            m_Actors[i]->doSomething();
        }else{
            delete m_Actors[i];
            m_Actors.erase(m_Actors.begin()+i);
        }
        
        if(gameEnded)
        {
            gameEnded = false;
            return GWSTATUS_PLAYER_WON;
        }
        if(nextLvl)
        {
            nextLvl = false;
            return GWSTATUS_FINISHED_LEVEL;
        }
    }
    m_peach -> doSomething();

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    vector<Actor*>::iterator it;
    it = m_Actors.begin();
    for(; it != m_Actors.end(); it++)
    {
        delete *it;
        it = m_Actors.erase(it);
        it--;
    }
    delete m_peach;
    
}




bool StudentWorld::damageOverlappingActor(Actor *damager)const
{
    for(int i = 0; i < m_Actors.size(); i++)
    {
        int x1 = damager->getX();
        int y1 = damager->getY();

        int x2 = m_Actors[i]->getX();
        int y2 = m_Actors[i]->getY();

        int x1_Extend = x1 + SPRITE_WIDTH - 1;
        int y1_Extend = y1 + SPRITE_HEIGHT -1;

        int x2_Extend = x2 + SPRITE_WIDTH - 1;
        int y2_Extend = y2 + SPRITE_HEIGHT - 1;
        
            if((x2 <= x1 && x1 <= x2_Extend) || (x2 <= x1_Extend && x1_Extend <= x2_Extend)){
                if((y2 <= y1 && y1 <= y2_Extend) || (y2 <= y1_Extend && y1_Extend <= y2_Extend)){
                    if(!m_Actors[i]->isDead() && m_Actors[i]->sufferDamageIfDamageable()){
                        cerr<<"SDID"<<endl;
                        return true;
                    }
                }
            }
    }
    
    return false;
}


StudentWorld::~StudentWorld()
{
    cleanUp();
}


void StudentWorld::load()
{
    ostringstream l;
    l.setf(ios::fixed);
    l.precision(2);
    
    string before = "level";
    string after = ".txt";
    
    l << before <<setw(2)<< setfill('0')<<getLevel()<<after;
    
    string done = l.str();
    cerr<<done<<endl;
    Level lev(assetPath());
    string level_file = done;
    
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
        cerr << "Could not find level01.txt data file" << endl;
    
    else if (result == Level::load_fail_bad_format)
        cerr << "level01.txt is improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        Level::GridEntry ge;
        
        for(int i = 0; i < VIEW_HEIGHT/8; i++)
        {
            for(int j = 0; j < VIEW_WIDTH/8; j++)
            {
                ge = lev.getContentsOf(i, j);
                cout<<i << " "<<j <<endl;
                switch(ge){
                    case Level::empty:
                        //does nothing
                        break;
                    case Level::mushroom_goodie_block:{
                        Block* newBlock = new Block(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, Block::mushroom);
                        m_Actors.push_back(newBlock);
                        break;
                    }
                    case Level::koopa:
                    {
                        Koopa* newKoopa = new Koopa(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                        m_Actors.push_back(newKoopa);
                        break;
                    }
                    case Level::goomba:
                    {
                        Goomba* newGoomba = new Goomba(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                        m_Actors.push_back(newGoomba);
                        break;
                    }
                    case Level::peach: {
                        Peach* newPeach = new Peach(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                        m_peach = newPeach;
                        break;
                    }
                    case Level::flag:{
                        LevelEnder* newFlag = new LevelEnder(this, IID_FLAG, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, false);
                        m_Actors.push_back(newFlag);
                        break;
                    }
                        
                    case Level::block: {
                        Block* newBlock = new Block(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                        m_Actors.push_back(newBlock);
                        break;
                    }
                    case Level::star_goodie_block:{
                        Block* newBlock = new Block(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, Block::star);
                        m_Actors.push_back(newBlock);
                        break;
                    }
                    case Level::pipe:
                    {
                        Pipe* newPipe = new Pipe(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                        m_Actors.push_back(newPipe);
                        break;
                    }
                    case Level::flower_goodie_block:
                    {
                        Block* newBlock = new Block(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, Block::flower);
                        m_Actors.push_back(newBlock);
                        break;
                    }
                    case Level::piranha:
                    {
                        Piranha* newPiranha = new Piranha(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                        m_Actors.push_back(newPiranha);
                        break;
                    }
                        
                    case Level::mario:
                    {
                        LevelEnder* newMar = new LevelEnder(this, IID_MARIO, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, true);
                        m_Actors.push_back(newMar);
                        break;
                    }
                        
                    default:
                        break;
                        
                }
            }
        }
        
    }
    
}


void StudentWorld::endLevel(bool isGameWon)
{
    if(isGameWon)
    {
        gameEnded = true;
    }else{
        nextLvl = true;
    }
}

bool StudentWorld::getPeachTargetingInfo(Actor* a, int yDeltaLimit, int& xDeltaFromActor) const
{
    int tempAY = a->getY();
    int peachY = getPeach() -> getY();
    
    int dif = abs(tempAY - peachY);
    
    if(dif > yDeltaLimit)
    {
        return false;
    }
    
    xDeltaFromActor = getPeach()->getX() - a->getX();
    return true;
}
