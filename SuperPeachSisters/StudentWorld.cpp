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

