#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <vector>

using namespace std;

class BoardImpl
{
public:
    BoardImpl(const Game& g);
    ~BoardImpl();
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;

private:
    // TODO:  Decide what private members you need.  Here's one that's likely
    //        to be useful:
    const Game& m_game;
    int r;
    int c;
    char gamegrid[MAXROWS][MAXCOLS];
    bool blockgrid[MAXROWS][MAXCOLS];
    //vector <Point> valid_points;
    vector <int> placedId;
    vector <Point> placedPoints;
};

BoardImpl::~BoardImpl()
{

}

BoardImpl::BoardImpl(const Game& g)
    : m_game(g)
{
    //call rows and columns from game class
    r = m_game.rows();
    c = m_game.cols();
    gamegrid[r][c];
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            gamegrid[i][j] = '.';
            //valid_points.push_back(Point(i, j));
            blockgrid[i][j] = false;
        }

    }

    // This compiles, but may not be correct
}

void BoardImpl::clear()
{
    //r = m_game.rows();
    //c = m_game.cols();
    //gamegrid[r][c];
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            gamegrid[i][j] = '.';
            blockgrid[i][j] = false;
        }
    }
    placedId.clear();
    /*for (vector <int>::iterator it = placedId.begin(); it != placedId.end(); it++)
    {
        it = placedId.erase(it);
    }*/
    // This compiles, but may not be correct
}

void BoardImpl::block()
{

    //change for loop limit
    for (int i = 0; i < /*m_game.rows()*m_game.cols()*/(m_game.rows() * m_game.cols()) / 2; i++)
    {
        //pick random valid point to block
        int col = randInt(m_game.cols());
        int row = randInt(m_game.rows());
        /*int colBlock = valid_points.at(rv).c;
        int rowBlock = valid_points.at(rv).r;*/
        //sets blockgrid to true at this rand coordinate
        if (blockgrid[row][col] == true)
        {
            i--;
            continue;
        }
        blockgrid[row][col] = true;
        //valid_points.erase(valid_points.begin() + rv);
        //MAKE SURE YOU CHECK BLOCKGRID IN PLACESHIP
    }
    //to cout blocked grid
    //cout << "  ";
    //for (int i = 0; i < m_game.cols(); i++)
    //    cout << i;
    //cout << endl;
    ////remaining rows
    //for (int i = 0; i < m_game.rows(); i++)
    //{
    //    cout << i << " ";

    //    for (int j = 0; j < m_game.cols(); j++)
    //    {
    //        if (blockgrid[i][j])
    //            cout << 't';
    //        if (!blockgrid[i][j])
    //            cout << 'f';
    //    }
    //    cout << endl;
    //}
}

//EDIT
void BoardImpl::unblock()
{
    // TODO:  Replace this with code to unblock all blocked cells
    int count = 0;
    for (int r = 0; r < m_game.rows(); r++) {
        for (int c = 0; c < m_game.cols(); c++) {
            //if (blockgrid[r][c] == true)
            //{
            //    //valid_points.insert(valid_points.begin() + count, Point(r, c));
            //    blockgrid[r][c] = false;
            //}
            blockgrid[r][c] = false;
            count++;
        }
    }
}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    //first coordinate must be on the board

    //if the shipLength bool doesn't return -1, 
    //check if the shipLength fits on the board

    for (int i = 0; i < placedId.size(); i++)
    {
        if (shipId == placedId[i])
            return false;
    }
    if (m_game.shipLength(shipId) != -1)
    {
        if ((topOrLeft.r >= 0 && topOrLeft.r <= 9) || topOrLeft.c >= 0 && topOrLeft.c <= 9)
        {
            //now check that the length and direction does not fall off the board
            int s1, s2, e1, e2, len;
            s1 = topOrLeft.r;
            s2 = topOrLeft.c;
            //how to call length of the ship
            //len = m_game.m_addShips[shipId].len;
            len = m_game.shipLength(shipId);
            if (dir == HORIZONTAL)
            {
                e1 = s1;
                e2 = s2 + (len - 1);
                if (e1 >= m_game.rows() || e2 >= m_game.cols())
                    return false;
                for (int j = s2; j <= e2; j++)
                    if (gamegrid[e1][j] != '.' || blockgrid[e1][j])
                        return false;
                for (int i = s2; i <= e2; i++)
                {
                    // check if there are any other ships already placed in this space
                    
                    if (gamegrid[e1][i] == '.')
                    {
                        gamegrid[e1][i] = m_game.shipSymbol(shipId);
                    }
                }
            }
            if (dir == VERTICAL)
            {
                e2 = s2;
                e1 = s1 + (len - 1);
                if (e1 >= m_game.rows() || e2 >= m_game.cols())
                    return false;

                for (int j = s1; j <= e1; j++)
                    if (gamegrid[j][e2] != '.' || blockgrid[j][e2])
                        return false;
                for (int i = s1; i <= e1; i++)
                {
                    // check if there are any other ships already placed in this space
                    
                    if (gamegrid[i][e2] == '.')
                    {
                        gamegrid[i][e2] = m_game.shipSymbol(shipId);
                    }
                }

            }
            //now check if end coordinates are on the grid
            
        }
    }
    placedId.push_back(shipId);
    placedPoints.push_back(topOrLeft);
    return true;
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    vector <int>::iterator it = placedId.begin();
    vector <Point>::iterator itPoint = placedPoints.begin();
    //CHECK THIS
    bool idMatch = false;
    for (int i = 0; i < placedId.size(); i++)
    {
        if (shipId == placedId[i])
        {
            idMatch = true;
            break;
        }
    }
    //This shape has not been placed so it cannot be unplaced
    if (!idMatch)
        return false;
    //return false if ship Id is invalid or if the ship does not fit on the board
    if (m_game.shipLength(shipId) != -1)
    {
        if ((topOrLeft.r >= 0 && topOrLeft.r <= m_game.rows()) || topOrLeft.c >= 0 && topOrLeft.c <= m_game.cols())
        {
            //now check that the length and direction does not fall off the board
            int s1, s2, e1, e2, len;
            s1 = topOrLeft.r;
            s2 = topOrLeft.c;
            //how to call length of the ship
            //len = m_game.m_addShips[shipId].len;
            len = m_game.shipLength(shipId);
            if (dir == HORIZONTAL)
            {
                e1 = s1;
                e2 = s2 + (len - 1);
                if (e1 >= m_game.rows() || e2 >= m_game.cols())
                    return false;

                for (int j = s2; j <= e2; j++)
                {
                    if (gamegrid[e1][j] != m_game.shipSymbol(shipId))
                        return false;
                }
                for (int i = s2; i <= e2; i++)
                {
                    
                    //if (the shipId at the coordinate matches shipId)
                    //How to find the shipId at a point
                    //if (s1 == placedPoints.at(i).r && i == placedPoints.at(i).c)
                    
                    //if (gamegrid[e1][i] == m_game.shipSymbol(shipId)/* || gamegrid[e1][i] == 'X'*/) //When you push the shipId to the vector, also create another vector and push the topOrLeft point to that vector
                        //just check symbols ig
                    //{
                        gamegrid[e1][i] = '.';
                    //}
                    //else
                        //return false;
                }
            }
            if (dir == VERTICAL)
            {
                e2 = s2;
                e1 = s1 + (len - 1);
                if (e1 >= m_game.rows() || e2 >= m_game.cols())
                    return false;

                for (int j = s1; j <= e1; j++)
                    if (gamegrid[j][e2] != m_game.shipSymbol(shipId))
                        return false;
                for (int i = s1; i <= e1; i++)
                {
                    
                    // check if there are any other ships already placed in this space
                    /*if (gamegrid[i][e2] == m_game.shipSymbol(shipId))
                    {*/
                        gamegrid[i][e2] = '.';
                    /*}
                    else
                        return false;*/
                }
            }
        }
        else
            return false;
    }
    else
        return false;
    for (it; it != placedId.end(); it++)
    {
        if (*it == shipId)
        {
            it = placedId.erase(it);
            break;
        }
           
  
    }
    /*for (itPoint; itPoint != placedPoints.end(); it++)
    {
        if (itPoint->r == topOrLeft.r && itPoint->c == topOrLeft.c)
        {
            itPoint = placedPoints.erase(itPoint);
            break;
        }
    }*/
    return true; 
}

void BoardImpl::display(bool shotsOnly) const
{

    cout << "  ";
    for (int i = 0; i < m_game.cols(); i++)
        cout << i;
    cout << endl;
    //remaining rows
    for (int i = 0; i < m_game.rows(); i++)
    {
        cout << i << " ";
        
        for (int j = 0; j < m_game.cols(); j++)
        {
            if (shotsOnly)
            {
                if (gamegrid[i][j] != 'X' && gamegrid[i][j] != 'o')  
                    cout << '.';
                else if (gamegrid[i][j] == 'X' || gamegrid[i][j] == 'o') 
                    cout << gamegrid[i][j];
            }
            if (!shotsOnly)
                cout << gamegrid[i][j];
        }
        cout << endl;
    }
}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    //how to get the shipId of the ship at point p??
    shotHit = false;
    shipDestroyed = false;
    int r = p.r;
    int c = p.c;
    int tempId;

    if (p.r > m_game.rows() || p.c > m_game.cols())
        return false;
    if (gamegrid[r][c] == 'X' || gamegrid[r][c] == 'o') //check if point has already been attacked
        return false;
    if (gamegrid[r][c] == '.')
    {
        gamegrid[r][c] = 'o';
        return true;
    }
    //check that p = an undamaged ship coordinate
    for (int i = 0; i < m_game.nShips(); i++)
    {
        if (gamegrid[r][c] == m_game.shipSymbol(i))
        {
            tempId = i;
            break;
        }

    }
    if (gamegrid[r][c] != '.')
    {
        char s = gamegrid[r][c];
        gamegrid[r][c] = 'X';
        shotHit = true;
        shipDestroyed = true;
        for (int i = 0; i < m_game.rows(); i++)
        {
            for (int j = 0; j < m_game.cols(); j++)
            {
                if (s == gamegrid[i][j])
                {
                    shipDestroyed = false;
                    //delete the ship from the ship vector here??
                    break;
                }

                //if (gamegrid[i][j] == gamegrid[r][c])
                //{
                //    //  set p to 'X'
                //    gamegrid[r][c] = 'X';
                //    shotHit = true;
                //    break;
                //}
            }

        }
        if (shipDestroyed)
            shipId = tempId;
        //delete the number of ships
            //m_game.nShips()
    }
    else
        shotHit = false;
    return true;
}

bool BoardImpl::allShipsDestroyed() const
{
    int r = m_game.rows();
    int c = m_game.cols();

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            char x = gamegrid[i][j];
            if (x != 'X' && x != 'o' && x != '.')
                return false;
        }
    }
    return true;
}

//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}
