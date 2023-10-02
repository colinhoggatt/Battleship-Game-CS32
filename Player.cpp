#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

//for mediocre player

//made a private integer for state?
//need recursion for unplaceShips
// make func?
//takes, row, column, # of ships
//if no ships, return true
// if == 10, it went through all coordinates so did not work
//stack of ship structs???

using namespace std;

//*********************************************************************
//  AwfulPlayer
//*********************************************************************

class AwfulPlayer : public Player
{
public:
    AwfulPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
private:
    Point m_lastCellAttacked;
};

AwfulPlayer::AwfulPlayer(string nm, const Game& g)
    : Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool AwfulPlayer::placeShips(Board& b)
{
    // Clustering ships is bad strategy
    for (int k = 0; k < game().nShips(); k++)
        if (!b.placeShip(Point(k, 0), k, HORIZONTAL))
            return false;
    return true;
}

Point AwfulPlayer::recommendAttack()
{
    if (m_lastCellAttacked.c > 0)
        m_lastCellAttacked.c--;
    else
    {
        m_lastCellAttacked.c = game().cols() - 1;
        if (m_lastCellAttacked.r > 0)
            m_lastCellAttacked.r--;
        else
            m_lastCellAttacked.r = game().rows() - 1;
    }
    return m_lastCellAttacked;
}

void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
    bool /* shotHit */, bool /* shipDestroyed */,
    int /* shipId */)
{
    // AwfulPlayer completely ignores the result of any attack
}

void AwfulPlayer::recordAttackByOpponent(Point /* p */)
{
    // AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  HumanPlayer
//*********************************************************************

bool getLineWithTwoIntegers(int& r, int& c)
{
    bool result(cin >> r >> c);
    if (!result)
        cin.clear();  // clear error state so can do more input operations
    cin.ignore(10000, '\n');
    return result;
}

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string nm, const Game& g)
        : Player(nm,g)
    {}
    ~HumanPlayer();
    bool placeShips(Board& b);
    bool isHuman() const;

    void promptDir(int shipId);
    void topOrLeft(Board& b, int shipId);
    Point recommendAttack();
    void recordAttackResult(Point p, bool validShot, bool shotHit,
        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);

private:
    char direction;
    bool shipPlace = false;
};
// TODO:  You need to replace this with a real class declaration and
//        implementation.

//helper for placeShips

HumanPlayer::~HumanPlayer()
{

}

void HumanPlayer::promptDir(int shipId)
{

    cout << endl << "Enter h or v for direction of " << game().shipName(shipId) << " (length " << game().shipLength(shipId) << "): ";
    cin >> direction;
    cin.ignore(1000, '\n');

    if (direction != 'h' && direction != 'v')
    {
        cout << "Direction must be h or v.";
        //reprompt for direction
        promptDir(shipId);
    }
}
//helper for placeShips
void HumanPlayer::topOrLeft(Board& b, int shipId)
{
    int r, c;
    Direction DIR;
    if (direction == 'h')
    {
        cout << "Enter row and column of leftmost cell(e.g., 3 5): ";
        DIR = HORIZONTAL;
    }

    if (direction == 'v')
    {
        cout << "Enter row and column of topmost cell(e.g., 3 5): ";
        DIR = VERTICAL;
    }

    if (getLineWithTwoIntegers(r, c))
    { //check that this point is valid
        Point p(r, c);
        if (game().isValid(p))
        {
            //if the point is valid, place a ship here
            if (b.placeShip(Point(r, c), shipId, DIR))
                shipPlace = true;
            else
            {
                cout << "The ship cannot be placed there." << endl;
                topOrLeft(b, shipId);
            }
        }
        else
        {
            cout << "The ship cannot be placed there." << endl;
            //reprompt for valid topOrLeft
            topOrLeft(b, shipId);
        }
    }
    else
    {
        cout << "The ship cannot be placed there.";
        //reprompt for valid topOrLeft
        topOrLeft(b, shipId);
    }
}

bool HumanPlayer::placeShips(Board& b)
{
    cout << name() << " must place " << game().nShips() << " ships." << endl;
    //Game will display empty grid
    b.display(false);
    //for loop to prompt for direction and topOrLeft point
    for (int i = 0; i < game().nShips(); i++)
    {
        promptDir(i);
        topOrLeft(b, i);
        //Game will display the grid with placed ship
        b.display(false);
    }
    return shipPlace;
}

bool HumanPlayer::isHuman() const
{
    return true;
}

Point HumanPlayer::recommendAttack()
{
    int r, c;
    cout << "Enter the row and column to attack (e.g., 3 5): ";
    if (!getLineWithTwoIntegers(r, c))
        cout << "Invalid attack";
        //attackPoint = (r, c);
    //don't need to verify valid coord?
    //cin >> r >> c;
    cin.clear();
    return Point(r, c);
}

void HumanPlayer::recordAttackResult(Point p, bool validShot, bool shotHit,
    bool shipDestroyed, int shipId)
{
    ////check validShot
    ////how to check if that point has been attacked before
    //if (game().isValid(p) || /*point hasn't been attacked before*/)
    //{
    //    validShot = true;
    //    if (/*the shot hits a ship*/)
    //    {
    //        shotHit = true;
    //        if (/*the shot hits the last undamaged segment of a ship*/)
    //        {
    //            shipDestroyed = true;
    //        }
    //    }
    //}
}

void HumanPlayer::recordAttackByOpponent(Point p)
{
 
}

//*********************************************************************
//  MediocrePlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
// Remember that Mediocre::placeShips(Board& b) must start by calling
// b.block(), and must call b.unblock() just before returning.

class MediocrePlayer : public Player
{
public:
    MediocrePlayer(std::string nm, const Game& g)
        : Player(nm, g), goodPoint(-1, -1)
    {
        state = 1;
    }
    ~MediocrePlayer();
    //Verify use of goodPoint
    virtual bool placeShips(Board& b);
    Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);

    //helper function
    //bool place(int r, int c, int shipLength, int shipId, Point& goodPoint);
    bool place(Board& b, int shipsLeft);

    void crossPointsSum(Point p);
    bool usedPoint(Point p);
private:
    int placeShipCount = 0;
    int m_shipId;
    Point goodPoint;
    int state;
    Point lastAttack;
    //char placedgrid[MAXROWS][MAXCOLS];
    vector <Point> placedgrid;
    vector <Point> validpoints;

    vector <Point> allCrossPoints;
    vector <Point> prevPoint;
    Point center;
    Point recommended_point;
    int num = 0;

};

//helper function for placeShips

//bool MediocrePlayer::place(int r, int c, int shipLength, int shipId, Point& goodPoint)
//{
//    //keep track of how many place attempts have been made 
//    placeShipCount++;
//    //if r is greater than rows, we've reached the end of the grid 
//    if (r >= game().rows())
//        return false;
//    //if c is greater than columns, move to the next row
//    if (c >= game().cols())
//        //recursive call
//        return place(r + 1, 0, shipLength, shipId, goodPoint);
//    if (place(r, c, shipLength, shipId, goodPoint) == true)
//    {
//        goodPoint = Point(r, c);
//        return true;
//    }
//    else
//        //is this an infinite loop or return false here?
//        return place(r, c, shipLength, shipId, goodPoint);
//}

MediocrePlayer::~MediocrePlayer()
{

}

bool MediocrePlayer::place(Board& b, int shipsLeft)
{
    bool placesub;
    bool placerest;
    if (shipsLeft < 0) //Kendrake said this should be < 0??? is this nShips or shipId??
        return true;
    for (int i = 0; i < game().rows(); i++)
    {
        for (int j = 0; j < game().rows(); j++)
        {
            //Attempt to place horizontally
            placesub = b.placeShip(Point(i, j), shipsLeft, HORIZONTAL);

            if (placesub)
            {
                //If able to place horizontally, attempt with next ship
                placerest = place(b, shipsLeft - 1);
                //if all ships are placed, return true;
                if (placerest)
                    return true;
                if (!placerest)
                    b.unplaceShip(Point(i, j), shipsLeft, HORIZONTAL);
            }

            if (!placesub)
            {
                //b.unplaceShip(Point(i, j), shipsLeft, HORIZONTAL);
                placesub = b.placeShip(Point(i, j), shipsLeft, VERTICAL);

                if (placesub)
                {
                    placerest = place(b, shipsLeft - 1);

                    if (placerest)
                        return true;
                    if(!placerest)
                        b.unplaceShip(Point(i, j), shipsLeft, VERTICAL);
                }

                /*if (!placesub)
                {
                    b.unplaceShip(Point(i, j), shipsLeft, VERTICAL);
                }*/
            }
        }
    }
    return false;
}

bool MediocrePlayer::placeShips(Board& b)
{
    //bool placeSucc = false;
    int shipNum = game().nShips() - 1;
    b.block();
    while (placeShipCount < 50)
    {
        if (place(b, shipNum))
        {
            b.unblock();
            return true;
        }
        else
        {
            placeShipCount++;
            b.unblock();
            b.block();
        }
    }

    return false;
}

//bool function to check if a coordinate has been attacked
bool MediocrePlayer::usedPoint(Point p)
{
    bool usedPoint = false;
    //check that we haven't attacked this point yet
    for (int i = 0; i < prevPoint.size(); i++)
    {
        //if the random coordinate has been previously pushed onto the prevPoint vector
        if (prevPoint[i].r == p.r && prevPoint[i].c == p.c) {
            usedPoint = true;
            break;
        }
    }
    return usedPoint;
}

void MediocrePlayer::crossPointsSum(Point p)
{
    //add all the points in each direction of the cross
    
    //add points in upward direction
    for (int r = p.r - 1; r >= p.r - 4 && game().isValid(Point(r, p.c)); r--)
    {
        //if it hasn't been chosen before
        if (!usedPoint(Point(r, p.c)))
        {
            allCrossPoints.push_back(Point(r, p.c));
        }
    }
    //add points to the right
    for (int c = p.c + 1; c <= p.c + 4 && game().isValid(Point(p.r, c)); c++)
    {
        //if it hasn't been chosen before
        if (!usedPoint(Point(p.r, c)))
        {
            allCrossPoints.push_back(Point(p.r, c));
        }
    }
    //add point downward direction
    for (int r = p.r + 1; r <= p.r + 4 && game().isValid(Point(r, p.c)); r++)
    {
        //if it hasn't been chosen before
        if (!usedPoint(Point(r, p.c)))
        {
            allCrossPoints.push_back(Point(r, p.c));
        }
    }
    // add points to left
    for (int c = p.c - 1; c >= p.c - 4 && game().isValid(Point(p.r, c)); c--)
    {
        //if it hasn't been chosen before
        if (!usedPoint(Point(p.r, c)))
        {
            allCrossPoints.push_back(Point(p.r,c));
        }
    }
}

Point MediocrePlayer::recommendAttack()
{
    //cout << "state " << state << endl;
    if (state == 1)
    {
        //set a new random point
        // then check if the point has been attacked before
        Point p = game().randomPoint();
        bool used = usedPoint(p);
        while (used)
        {
            p = game().randomPoint();
            used = usedPoint(p);
        }
        //prevPoint.push_back(p);
        return p;

    }
    else if (state == 2)
    {  //state = 2
        allCrossPoints.clear();
        crossPointsSum(center);
        int pos = randInt(allCrossPoints.size());
        Point p = allCrossPoints[pos];

        //allCrossPoints.erase(allCrossPoints.begin() + pos);
       // prevPoint.push_back(p);
        return p;
    }
    return Point(-1, -1);
}

void MediocrePlayer::recordAttackResult(Point p, bool validShot, bool shotHit,
    bool shipDestroyed, int shipId)
{
    
    if (!validShot)
        return;
    //cout << "hello" << endl;
    //cout << "num_hits" << ' ' << num << endl;

    //push point to document having already attacked this coordinate
    prevPoint.push_back(p);
    if (state == 1)
    {
        if (shotHit)
        {
            
            if (shipDestroyed)
            {
                state = 1;
            }
            else {
                state = 2;
                center = p;
            }
            
        }
    }
    if (state == 2)
    {
        if (shotHit) 
        {

            if (shipDestroyed)
            {
                state = 1;
            }
            else {
                allCrossPoints.clear();
                crossPointsSum(center);
                if (allCrossPoints.empty()) {
                    state = 1;
                }
            }
        }
    }



}

void MediocrePlayer::recordAttackByOpponent(Point p)
{
    //leave as is
}



//*********************************************************************
//  GoodPlayer
//*********************************************************************

class GoodPlayer : public Player
{
public:
    GoodPlayer(string nm, const Game& g)
        : Player(nm, g), state(1), randAttack(Point(1, UP)),
        lastAttack(Point(-999, -999)), prevPoint(make_pair(0, UP))
    {}
    ~GoodPlayer();
    bool placeShips(Board& b);
    Point recommendAttack();
    void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
    void recordAttackByOpponent(Point p);

    //helper functions
    bool place(Board& b, int shipId);
    
    bool diagSwitch(char chkboard);
    Point randDiagonal(int r, int c);
    bool goodIsValid(Point p);
    bool spaceLeft(Point p);
    Point accuratePoint(char chkboard);
    bool availableCross(Point p);
    Point onceHitAttack();
   
    

private:

    int state;
    int placeShipCount = 0;
    enum direction { UP, DOWN, LEFT, RIGHT };
    Point randAttack;
    Point lastAttack; 
    pair<int, direction> prevPoint;

    set<pair<int, int>> usedPoint; //already attacked coordinates
};

GoodPlayer::~GoodPlayer() 
{

}

bool GoodPlayer::place(Board& b, int shipsLeft)
{
    bool placesub;
    bool placerest;
    if (shipsLeft < 0)
        return true;
    for (int i = 0; i < game().rows(); i++)
    {
        for (int j = 0; j < game().rows(); j++)
        {
            //Attempt to place horizontally
            placesub = b.placeShip(Point(i, j), shipsLeft, HORIZONTAL);

            if (placesub)
            {
                //If able to place horizontally, attempt with next ship
                placerest = place(b, shipsLeft - 1);
                //if all ships are placed, return true;
                if (placerest)
                    return true;
                if (!placerest)
                    b.unplaceShip(Point(i, j), shipsLeft, HORIZONTAL);
            }

            if (!placesub)
            {
                //b.unplaceShip(Point(i, j), shipsLeft, HORIZONTAL);
                placesub = b.placeShip(Point(i, j), shipsLeft, VERTICAL);

                if (placesub)
                {
                    placerest = place(b, shipsLeft - 1);

                    if (placerest)
                        return true;
                    if (!placerest)
                        b.unplaceShip(Point(i, j), shipsLeft, VERTICAL);
                }

                /*if (!placesub)
                {
                    b.unplaceShip(Point(i, j), shipsLeft, VERTICAL);
                }*/
            }
        }
    }
    return false;
}

//MediocrePlayer impl for placeShips
bool GoodPlayer::placeShips(Board& b)
{
    //bool placeSucc = false;
    int shipNum = game().nShips() - 1;
    b.block();
    while (placeShipCount < 50)
    {
        if (place(b, shipNum))
        {
            b.unblock();
            return true;
        }
        else
        {
            placeShipCount++;
            b.unblock();
            b.block();
        }
    }
    return false;
}

bool GoodPlayer::goodIsValid(Point p)
{
    if (!game().isValid(p))    return false;
    if (usedPoint.find(make_pair(p.r, p.c)) != usedPoint.end()) return false;
    else return true;
}

bool GoodPlayer::availableCross(Point p)
{
    int maxCheck = max(game().rows(), game().cols());

    for (int i = 0; i < maxCheck; i++)
    {
        if (i < game().rows() && usedPoint.find(make_pair(i, p.c)) == usedPoint.end())
            return true;
        if (i < game().cols() && usedPoint.find(make_pair(p.r, i)) == usedPoint.end())
            return true;
    }
    return false;
}

Point GoodPlayer::onceHitAttack()
{
    int r_prev = lastAttack.r;
    int c_prev = lastAttack.c;

    if (prevPoint.second == UP)
    {
        int diff = prevPoint.first;
        Point p = Point(r_prev - diff - 1, c_prev);
        do
        {
            if (p.r < 0)
            {
                prevPoint.first = 0;
                prevPoint.second = RIGHT;
                break;
            }
            else if (usedPoint.find(make_pair(p.r, p.c)) == usedPoint.end())
            {
                prevPoint.first = diff + 1;
                prevPoint.second = UP;
                return p;
            }
            else
            {
                p.r--;
                prevPoint.first++;
            }
        } while (game().isValid(p));
    }
    else if (prevPoint.second == RIGHT)
    {
        int diff = prevPoint.first;
        Point p = Point(r_prev, c_prev + diff + 1);
        do
        {
            if (p.c >= game().cols())
            {
                prevPoint.first = 0;
                prevPoint.second = DOWN;
                break;
            }
            else if (usedPoint.find(make_pair(p.r, p.c)) == usedPoint.end())
            {
                prevPoint.first = diff + 1;
                prevPoint.second = RIGHT;
                return p;
            }
            else
            {
                p.c++;
                prevPoint.first++;
            }
        } while (game().isValid(p));
    }
    else if (prevPoint.second == DOWN)
    {
        int diff = prevPoint.first;
        Point p = Point(r_prev + diff + 1, c_prev);
        do
        {
            if (p.r >= game().rows())
            {
                prevPoint.first = 0;
                prevPoint.second = LEFT;
                break;
            }
            else if (usedPoint.find(make_pair(p.r, p.c)) == usedPoint.end())
            {
                prevPoint.first = diff + 1;
                prevPoint.second = DOWN;
                return p;
            }
            else
            {
                p.r++;
                prevPoint.first++;
            }
        } while (game().isValid(p));
    }
    else if (prevPoint.second == LEFT)
    {
        int diff = prevPoint.first;
        Point p = Point(r_prev, c_prev - diff - 1);
        do
        {
            if (p.c < 0)
            {
                prevPoint.first = 0;
                prevPoint.second = UP;
                break;
            }
            else if (usedPoint.find(make_pair(p.r, p.c)) == usedPoint.end())
            {
                prevPoint.first = diff + 1;
                prevPoint.second = LEFT;
                return p;
            }
            else
            {
                p.c--;
                prevPoint.first++;
            }
        } while (game().isValid(p));
    }

    return Point(-1, -1);
}


bool GoodPlayer::diagSwitch(char chkboard)
{
    for (int i = 0; i < game().rows(); i++)
    {
        for (int j = 0; j < game().cols(); j++)
        {
            if (chkboard == 'b')
            {
                //if coordinate is even
                if ((i + j) % 2 == 0 && usedPoint.find(make_pair(i, j)) == usedPoint.end())
                    return false;
            }
            else
            {
                //if coordinate is odd
                if ((i + j) % 2 == 1 && usedPoint.find(make_pair(i, j)) == usedPoint.end())
                    return false;
            }
        }
    }
    return true;
}


bool GoodPlayer::spaceLeft(Point p)
{
    //check if there is a space left in the diagonal paths
    for (int i = 1; i < max(game().rows(), game().cols()); i++)
    {
        //top left
        if (p.r - i >= 0 && p.c - i >= 0 && usedPoint.find(make_pair(p.r - i, p.c - i)) == usedPoint.end())
            return true;

        //top right
        if (p.r - i >= 0 && p.c + i < game().cols() && usedPoint.find(make_pair(p.r - i, p.c + i)) == usedPoint.end())
            return true;

        //bottom left
        if (p.r + i < game().rows() && p.c - i >= 0 && usedPoint.find(make_pair(p.r + i, p.c - i)) == usedPoint.end())
            return true;
        //bottom right
        if (p.r + i < game().rows() && p.c + i < game().cols() && usedPoint.find(make_pair(p.r + i, p.c + i)) == usedPoint.end())
            return true;
    }
    return false;
}

// returning a random coordinate along a diagonal
Point GoodPlayer::randDiagonal(int r, int c)
{
    int rowRand = -1, colRand = -1;
    int randomDiff = -MAXROWS + randInt(MAXCOLS * 2);

    int num = randInt(5);
    if (num == 0)
    {
        rowRand = r - randomDiff;
        colRand = c - randomDiff;
    }
    else if (num == 1)
    {
        rowRand = r - randomDiff;
        colRand = c + randomDiff;
    }
    else if (num == 2)
    {
        rowRand = r + randomDiff;
        colRand = c - randomDiff;
    }
    else if (num == 3)
    {
        rowRand = r + randomDiff;
        colRand = c + randomDiff;
    }
    return Point(rowRand, colRand);
}

Point GoodPlayer::recommendAttack()
{
    //select only points on the black spots
    //check coordinates diagonally
    if (usedPoint.size() >= game().rows() * game().cols())
        return Point(-1, -1);

    //state 2 if an attack hits a ship
    if (state == 2)
    {
        bool isDoable = true;

        Point p = onceHitAttack();
        while (!goodIsValid(p) || (p.r == lastAttack.r && p.c == lastAttack.c))
        {
            if (!availableCross(p))
            {
                isDoable = false;
                break;
            }
            p = onceHitAttack();
        }

        if (!isDoable)  state = 1;
        else
        {
            usedPoint.insert(make_pair(p.r, p.c));
            return p;
        }
    }

    //state 3. randomly finding a point on the diagonal
    if (state == 3)
    {
        //randomly select a point based off of the diagonal space of randAttack.
        Point p = randDiagonal(randAttack.r, randAttack.c);
        if (!spaceLeft(randAttack)) state = 1;
        else
        {
            while (!goodIsValid(p))
                p = randDiagonal(randAttack.r, randAttack.c);
            usedPoint.insert(make_pair(p.r, p.c));
            return p;
        }
    }

    //state 1. randomly finding a point(when the current diagonal is full)
    if (state == 1)
    {
        Point p = accuratePoint('w');

        while (usedPoint.find(make_pair(p.r, p.c)) != usedPoint.end())
        {
            if (diagSwitch('w'))
                p = accuratePoint('b');
            else
                p = accuratePoint('w');
        }
        usedPoint.insert(make_pair(p.r, p.c));
        randAttack = p;
        return p;
    }

    //return an invalid point (all of the condition outlined above has to be met)
    return Point(-1, -1);
}

Point GoodPlayer::accuratePoint(char color)
{
    int rowRand = randInt(game().rows()), colRand = randInt(game().cols());
    if (color == 'b')
    {
        while ((rowRand + colRand) % 2 != 0)
        {
            rowRand = randInt(game().rows());
            colRand = randInt(game().cols());
        }
        return Point(rowRand, colRand);
    }
    else if (color == 'w')
    {
        while ((rowRand + colRand) % 2 != 1)
        {
            rowRand = randInt(game().rows());
            colRand = randInt(game().cols());
        }
        return Point(rowRand, colRand);
    }
    else    
        return Point(-999, -999);
}

void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
    if (!validShot)
        return;

    if (state == 1)
    {
        if (!shotHit || shipDestroyed)
        {
            state = 3;
            return;
        }
        else
        {
            lastAttack = p;
            state = 2;
        }
    }
    else if (state == 2)
    {
        if (!shotHit)
        {
            //reset prevPoint and change directions
            prevPoint.first = 0;
            if (prevPoint.second == UP)
            {
                prevPoint.second = RIGHT;
            }
            else if (prevPoint.second == DOWN)
            {
                prevPoint.second = LEFT;
            }
            else if (prevPoint.second == LEFT)
            {
                prevPoint.second = UP;
            }
            else if (prevPoint.second == RIGHT)
            {
                prevPoint.second = DOWN;
            }

        }
        else if (!shipDestroyed) {}//stays the same
        else
        {
            prevPoint = make_pair(0, UP); 
            state = 1;
        }
    }

    else
    {
        if (shotHit && !shipDestroyed)
        {
            lastAttack = p;
            state = 2;
        }
    }
}

void GoodPlayer::recordAttackByOpponent(Point p)
{

}






//typedef AwfulPlayer GoodPlayer;
//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };

    int pos;
    for (pos = 0; pos != sizeof(types) / sizeof(types[0]) &&
        type != types[pos]; pos++)
        ;
    switch (pos)
    {
    case 0:  return new HumanPlayer(nm, g);
    case 1:  return new AwfulPlayer(nm, g);
    case 2:  return new MediocrePlayer(nm, g);
    case 3:  return new GoodPlayer(nm, g);
    default: return nullptr;
    }
}
