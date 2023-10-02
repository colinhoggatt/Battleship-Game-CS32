#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <algorithm> //is this ok to add?

using namespace std;

struct Ship {
    int len;
    char sym;
    string name;
};

class GameImpl
{
public:
    GameImpl(int nRows, int nCols);
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    string shipName(int shipId) const;
    Player* play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);
    vector<Ship> getShip()
    {
        return m_addShips;
    }
    
    bool attackHelp(Board& bTurn, Board& bNot, Player* pTurn, Player* pNot, bool shouldPause, Player*& winner);

private:
    
    vector<Ship> m_addShips;
    vector<char> m_shipSym;
    vector<char>::iterator it;

    int m_r;
    int m_c;
    int shipId; //do I need this
    //Player* winner = nullptr;
};

void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

GameImpl::GameImpl(int nRows, int nCols)
{
    //set rows and columns
    m_r = nRows;
    m_c = nCols;
    // This compiles but may not be correct
}

int GameImpl::rows() const
{
    if (m_r >= 0 && m_r <= MAXROWS)
        return m_r;
    return -1;  // This compiles but may not be correct
}

int GameImpl::cols() const
{
    if (m_c >= 0 && m_c <= MAXCOLS)
        return m_c;
    return -1;  // This compiles but may not be correct
}

bool GameImpl::isValid(Point p) const
{
    return p.r >= 0 && p.r < rows() && p.c >= 0 && p.c < cols();
}

Point GameImpl::randomPoint() const
{
    return Point(randInt(rows()), randInt(cols()));
}

bool GameImpl::addShip(int length, char symbol, string name)
{
    //EDIT
    if ((length <= m_c || length <= m_r) && length >= 0) //make sure all parameters are valid// n
        //symbol cannot be X, o, . 
        //symbol cannot be previously used
    {
        if (symbol != 'X' && symbol != 'o' && symbol != '.')
        {
            Ship shipadded = { length, symbol, name };
            //check if symbol is already in symbol vector
            it = find(m_shipSym.begin(), m_shipSym.end(), symbol);
            if (it == m_shipSym.end())
            {
                //symbol does not already exist
                m_shipSym.push_back(symbol);
                m_addShips.push_back(shipadded);
                return true;
            }
        }
    }
    return false;  // This compiles but may not be correct
}

int GameImpl::nShips() const
{
    return m_addShips.size();
    //return -1;  // This compiles but may not be correct
}

int GameImpl::shipLength(int shipId) const
{
    if (shipId >= 0 && shipId < m_addShips.size())
        return m_addShips[shipId].len;
    else
    return -1;  // This compiles but may not be correct
}

char GameImpl::shipSymbol(int shipId) const
{
    if (shipId >= 0 && shipId < m_addShips.size())
        return m_addShips[shipId].sym;
    else
    return '?';  // This compiles but may not be correct
}

string GameImpl::shipName(int shipId) const
{
    if (shipId >= 0 && shipId < m_addShips.size())
        return m_addShips[shipId].name;
    else
    return "";  // This compiles but may not be correct
}

bool GameImpl::attackHelp(Board& bTurn, Board& bNot,Player* pTurn, Player* pNot, bool shouldPause, Player*& winner)
{
    bool shotHit = false, shipDestroyed = false, wasted = false, validShot = false;
    int shipId;
    cout << pTurn->name() << "'s turn. Board for " << pNot->name() << ": " << endl;
    if (pTurn->isHuman())
        bNot.display(true);
    else
        bNot.display(false);
    //Place an attack
    //If the attack is valid,
    //If shotHit is true, cout << (Player whose turn it is) attacked (point just attacked
    Point p = pTurn->recommendAttack();
    if (validShot=bNot.attack(p, shotHit, shipDestroyed, shipId) == true)
    {
        if (shotHit && shipDestroyed)
        {
            cout << pTurn->name() << " attacked (" << p.r << "," << p.c << "), and destroyed a " << shipName(shipId) << ", resulting in : ";
        }
        if (shotHit && !shipDestroyed)
        {
            cout << pTurn->name() << " attacked (" << p.r << "," << p.c << ") and hit something, resulting in: ";
        }
        if (!shotHit && !shipDestroyed)
        {
            cout << pTurn->name() << " attacked (" << p.r << "," << p.c << ") and missed, resulting in: ";
        }
        cout << endl;
    }
    else
    {
        wasted = true;
        cout << pTurn->name() << " wasted a shot at (" << p.r << "," << p.c << ")." << endl;
        if (shouldPause)
        {
            cout << "Press enter to continue: ";
            cin.ignore(100000, '\n');
        }
    }

    if (pTurn->isHuman())
        bNot.display(true);
    else
        bNot.display(false);

    if (shouldPause)
    {
        cout << "Press enter to continue: ";
        cin.clear();
        cin.ignore(100000, '\n');
        //cout << endl << "ignore was run" << endl;
        
    }
    /*if (shotHit) {
        cout << "shotHit!" << endl;
    }*/
    pTurn->recordAttackResult(p, validShot, shotHit, shipDestroyed, shipId);
    /*if (shouldPause && !wasted)
    {
        cout << "Press enter to continue: ";
        cin.ignore(1000, '\n');
    }*/
    if (bTurn.allShipsDestroyed())
    {
        cout << pNot->name() << " is the winner!" << endl;
        winner = pNot;
        return true;
    }
    if (bNot.allShipsDestroyed())
    {
        cout << pTurn->name() << " is the winner!" << endl;
        winner = pTurn;
        return true;
    }
    return false;

    //code above will loop while allshipsDestroyed for both boards is false
    //once breaks out of while loop in play function, if b1 allshipsDestroyed is true, player 2 is winner and vice versa.

}

Player* GameImpl::play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause)
{
    //this will be made up of calls from player and board class
    // temp variables for p1 and p2
    // 
    // once in while loop, swap vars and this will switch them for each call of while loop
    //call placeShips for player 1 and 2
    if (p1->placeShips(b1) == false)
    {
        cout << p1->name() << " was unable to place all their ships.";
        return nullptr;
    }
    if (p2->placeShips(b2) == false)
    {
        cout << p2->name() << " was unable to place all their ships.";
        return nullptr;
    }
    //once ships are successfully placed, gameplay begins
    //use a helper function in a while loop
    Player* winner = nullptr;
    while (!b1.allShipsDestroyed() && !b2.allShipsDestroyed()) //or while attackHelp == false;
    {
        if (attackHelp(b1, b2, p1, p2, shouldPause, winner))
            break;
        attackHelp(b2, b1, p2, p1, shouldPause, winner);
    }
   
    return winner;  
}

//MAKE SURE TO DELETE
//void Game::dump()
//{
//    for (int i = 0; i < nShips(); i++)
//    {
//        cout << m_impl->getShip().at(i).len << endl;
//        cout << m_impl->getShip().at(i).sym << endl;
//        cout << m_impl->getShip().at(i).name << endl;
//        cout << endl;
//    }
//}




//******************** Game functions *******************************

// These functions for the most part simply delegate to GameImpl's functions.
// You probably don't want to change any of the code from this point down.

Game::Game(int nRows, int nCols)
{
    if (nRows < 1 || nRows > MAXROWS)
    {
        cout << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1 || nCols > MAXCOLS)
    {
        cout << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
    m_impl = new GameImpl(nRows, nCols);
}

Game::~Game()
{
    delete m_impl;
}

int Game::rows() const
{
    return m_impl->rows();
}

int Game::cols() const
{
    return m_impl->cols();
}

bool Game::isValid(Point p) const
{
    return m_impl->isValid(p);
}

Point Game::randomPoint() const
{
    return m_impl->randomPoint();
}

bool Game::addShip(int length, char symbol, string name)
{
    if (length < 1)
    {
        cout << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows() && length > cols())
    {
        cout << "Bad ship length " << length << "; it won't fit on the board"
            << endl;
        return false;
    }
    if (!isascii(symbol) || !isprint(symbol))
    {
        cout << "Unprintable character with decimal value " << symbol
            << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X' || symbol == '.' || symbol == 'o')
    {
        cout << "Character " << symbol << " must not be used as a ship symbol"
            << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cout << "Ship symbol " << symbol
                << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cout << "Board is too small to fit all ships" << endl;
        return false;
    }
    return m_impl->addShip(length, symbol, name);
}

int Game::nShips() const
{
    return m_impl->nShips();
}

int Game::shipLength(int shipId) const
{
    assert(shipId >= 0 && shipId < nShips());
    return m_impl->shipLength(shipId);
}

char Game::shipSymbol(int shipId) const
{
    assert(shipId >= 0 && shipId < nShips());
    return m_impl->shipSymbol(shipId);
}

string Game::shipName(int shipId) const
{
    assert(shipId >= 0 && shipId < nShips());
    return m_impl->shipName(shipId);
}

Player* Game::play(Player* p1, Player* p2, bool shouldPause)
{
    if (p1 == nullptr || p2 == nullptr || nShips() == 0)
        return nullptr;
    Board b1(*this);
    Board b2(*this);
    return m_impl->play(p1, p2, b1, b2, shouldPause);
}

