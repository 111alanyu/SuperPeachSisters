#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <string>
using namespace std;


GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    
}


int StudentWorld::init()
{
    load();
    return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld::moveOrBonk(Actor *a, int destx, int desty) const
{
    if(moveIfPossible(a, destx, desty)){
        return true;
    }else{
        //TODO: PUT BONK CODE
        return false;
    }
    
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
        
        if((x2 <= x1 && x1 <= x2_Extend) || (x2 <= x1_Extend && x1_Extend <= x2_Extend)){
            if((y2 <= y1 && y1 <= y2_Extend) || (y2 <= y1_Extend && y1_Extend <= y2_Extend)){
                return false;
            }
        }
    }
    
    return true;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
    for(int i = 0; i < m_Actors.size(); i++){
        m_Actors[i]->doSomething();
    }
    m_peach -> doSomething();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for(int i = 0; i < m_Actors.size(); i++)
    {
        delete m_Actors[i];
        
    }
    delete m_peach;
}



StudentWorld::~StudentWorld()
{
    cleanUp();
}


void StudentWorld::load()
{
    
    Level lev(assetPath());
    string level_file = "level01.txt";
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
                        Block* newBlock = new Block(this, i * SPRITE_WIDTH, i * SPRITE_HEIGHT);
                        m_Actors.push_back(newBlock);
                        break;
                    }
                    case Level::koopa:
                        cout << "Location starts with a koopa" << endl;
                        break;
                    case Level::goomba:
                        cout << "Location starts with a goomba" << endl;
                        break;
                    case Level::peach: {
                        Peach* newPeach = new Peach(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                        m_peach = newPeach;
                        break;
                    }
                    case Level::flag:{
                        LevelEnder* newFlag = new LevelEnder(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, false);
                        m_Actors.push_back(newFlag);
                        break;
                    }
                        
                    case Level::block: {
                        Block* newBlock = new Block(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                        m_Actors.push_back(newBlock);
                        break;
                    }
                    case Level::star_goodie_block:
                        cout << "Location has a star goodie block" << endl;
                        break;
                    case Level::pipe:
                    {
                        Pipe* newPipe = new Pipe(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                        m_Actors.push_back(newPipe);
                    }
                    default:
                        cout<< "Unhandled" <<endl;
                        break;
                        
                }
            }
        }
        
    }
    
}

