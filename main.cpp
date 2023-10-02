#include "Game.h"
#include "Player.h"
//MAKE SURE TO DELETE Board.h
#include "Board.h"
#include <iostream>
#include <string>
#include "globals.h"

using namespace std;

bool addStandardShips(Game& g)
{
    return g.addShip(5, 'A', "aircraft carrier") &&
        g.addShip(4, 'B', "battleship") &&
        g.addShip(3, 'D', "destroyer") &&
        g.addShip(3, 'S', "submarine") &&
        g.addShip(2, 'P', "patrol boat");
}



//int main()
//{
    //test placeShips
   /* Game g(10, 10);
    addStandardShips(g);
    Board b(g);
    Player* p1 = createPlayer("mediocre", "Mediocre Midori", g);
    p1->placeShips(b);
    b.display(false);*/

    //testplaceShips places 100 times
    /*Game g(10, 10);
    addStandardShips(g);
    Board b(g);
    Player* p1 = createPlayer("mediocre", "Mediocre Midori", g);

    int count = 0;

    for (int i = 0; i < 100; i++)
    {
        if (p1->placeShips(b))
            count++;
        b.clear();
    }
    cout << "Placed " << count << " times" << endl;*/
    //b.display(false);







//    Game a(8, 5);
//    a.dump();
//    assert(a.addShip(3, 'a', "Harry") == true);
//    assert(a.addShip(0, 'b', "ERROR") == false);
//    assert(a.addShip(9, 'c', "ERROR") == false);
//    assert(a.addShip(8, 'd', "Beta") == true);
//    assert(a.addShip(5, 'e', "Gamma") == true);
//    assert(a.addShip(3, 'e', "ADFA") == false);
//    assert(a.addShip(3, 'd', "dd") == false);
//    assert(a.addShip(1, EOF, "dd") == false);
//    assert(a.addShip(2, 'x', "test") == true);
//    assert(a.addShip(2, 'X', "test") == false);
//    assert(a.addShip(3, 'o', "FAIK") == false);
//    assert(a.addShip(3, '.', "dd") == false);
//    assert(a.addShip(1, 'b', "blocked") == true);
//    a.dump();
//    //everything above works
//
//    Board b(a);
//    b.block();
//    b.block();
//    b.display(false);
//    b.clear();
//    b.display(false);
//
//    //    assert(b.placeChecker(Point(1,1), 4, HORIZONTAL) == false);
//    //    assert(b.placeChecker(Point(1,1), 5, HORIZONTAL) == false);
//    //assert(b.placeChecker(Point(1, 0), 1, VERTICAL) == false);
//    //assert(b.placeChecker(Point(0, 0), 1, VERTICAL) == true);
//    //assert(b.placeChecker(Point(3, 1), 2, HORIZONTAL) == false);
//    //assert(b.placeChecker(Point(3, 0), 2, HORIZONTAL) == true);  //placed
//    //assert(b.placeChecker(Point(7, 7), 1, HORIZONTAL) == false);
//    //assert(b.placeChecker(Point(8, 4), 1, HORIZONTAL) == false);
//    //assert(b.placeChecker(Point(-1, -1), 1, HORIZONTAL) == false);
//    //assert(b.placeChecker(Point(7, 7), 1, HORIZONTAL) == false);
//    assert(b.placeShip(Point(0, 0), 1, VERTICAL) == true);
//    //assert(b.placeChecker(Point(3, 0), 2, HORIZONTAL) == false);
//    assert(b.placeShip(Point(4, 1), 3, HORIZONTAL) == true);
//    b.display(false);
//    b.clear();
//    //assert(b.placeChecker(Point(3, 0), 2, HORIZONTAL) == true);
//        //b.block();
//        b.display(false);
//    assert(b.placeShip(Point(5, 2), 3, VERTICAL) == true);
//    assert(b.placeShip(Point(1, 1), 2, VERTICAL) == true);
//    b.display(false);
//    assert(b.placeShip(Point(4, 4), 3, VERTICAL) == false);
//    assert(b.placeShip(Point(4, 0), 1, VERTICAL) == false);
//    assert(b.placeShip(Point(4, 0), 1, VERTICAL) == false);
//    assert(b.placeShip(Point(3, 2), 0, HORIZONTAL) == true);
//    b.display(false);
//
//    //test attack()
//    bool shotHit;
//    bool shipDestroyed;
//    int shipId;
//    /*assert(b.attackChecker(Point(-1, -1)) == false);
//    assert(b.attackChecker(Point(8, 4)) == false);
//    assert(b.attackChecker(Point(7, 5)) == false);
//    assert(b.attackChecker(Point(8, 5)) == false);
//    assert(b.attackChecker(Point(3, 2)) == true);*/
//    assert(b.attack(Point(3, 2), shotHit, shipDestroyed, shipId) == true && shotHit == true && shipDestroyed == false);
//    //WRONG TEST CASE HARVEY
//    assert(b.attack(Point(3, 2), shotHit, shipDestroyed, shipId) == false && shotHit == false && shipDestroyed == false); //if segment is already damaged, shotHit is set to false
//    assert(b.attack(Point(3, 3), shotHit, shipDestroyed, shipId) == true && shotHit == true && shipDestroyed == false);
//    b.display(false);
//    //assert(b.isLastUndamaged(Point(3, 4), 'a'));
//    assert(b.attack(Point(3, 4), shotHit, shipDestroyed, shipId) == true && shotHit == true && shipDestroyed == true && shipId == 0);
//    //assert(b.attackChecker(Point(3, 3)) == false);
//
//    assert(b.attack(Point(3, 1), shotHit, shipDestroyed, shipId) && shotHit == true && shipDestroyed == false);
//    b.display(true);
//    b.display(false);
//    //test unplaceChecker()
////    b.cheekyRemove(3, 3);
////    b.cheekyRemove(5, 1);
//    
//    //assert(b.unplaceChecker(Point(4, 2), 0, HORIZONTAL) == false);
//    assert(b.unplaceShip(Point(3, 2), 0, HORIZONTAL) == false);
//    assert(b.unplaceShip(Point(-1, -1), 3, HORIZONTAL) == false);
//    assert(b.unplaceShip(Point(1, 1), 2, VERTICAL) == false); //shouldn't this be true
//    assert(b.unplaceShip(Point(6, 2), 3, VERTICAL) == false);
//    assert(b.unplaceShip(Point(4, 2), 3, VERTICAL) == false);
//    b.display(false);
//    assert(b.unplaceShip(Point(5, 2), 3, VERTICAL) == true);
//    assert(b.unplaceShip(Point(5, 2), 3, VERTICAL) == false);
//    b.display(false);
//
//    assert(b.allShipsDestroyed() == false);
//    for (int i = 1; i < 6; i++)
//        b.attack(Point(i, 1), shotHit, shipDestroyed, shipId);
//    assert(b.allShipsDestroyed() == true);
//}

int main()
{
    Game g(10, 10);
    assert(g.addShip(5, 'A', "aircraft carrier") &&
        g.addShip(4, 'B', "battleship") &&
        g.addShip(3, 'D', "destroyer") &&
        g.addShip(3, 'S', "submarine") &&
        g.addShip(2, 'P', "patrol boat"));
    for (int i = 0; i < 5; i++) {
        cout << "Length: " << g.shipLength(i) << "| Char: " << g.shipSymbol(i) << "| Näme: " << g.shipName(i) << endl;
    }
    
    const int NTRIALS = 10;

    cout << "Select one of these choices for an example of the game:" << endl;
    cout << "  1.  A mini-game between two mediocre players" << endl;
    cout << "  2.  A mediocre player against a human player" << endl;
    cout << "  3.  A " << NTRIALS
        << "-game match between a mediocre and an awful player, with no pauses"
        << endl;
    cout << "  4.  A " << NTRIALS
        << "-game match between a mediocre and a good player, with no pauses"
        << endl;
    cout << "Enter your choice: ";
    string line;
    getline(cin, line);
    if (line.empty())
    {
        cout << "You did not enter a choice" << endl;
    }
    else if (line[0] == '1')
    {
        Game g(2, 3);
        g.addShip(2, 'R', "rowboat");
        Player* p1 = createPlayer("mediocre", "Popeye", g);
        Player* p2 = createPlayer("mediocre", "Bluto", g);
        cout << "This mini-game has one ship, a 2-segment rowboat." << endl;
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '2')
    {
        Game g(10, 10);
        addStandardShips(g);
        Player* p1 = createPlayer("mediocre", "Mediocre Midori", g);
        Player* p2 = createPlayer("human", "Shuman the Human", g);
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '3')
    {
        int nMediocreWins = 0;

        for (int k = 1; k <= NTRIALS; k++)
        {
            cout << "============================= Game " << k
                << " =============================" << endl;
            Game g(10, 10);
            addStandardShips(g);
            Player* p1 = createPlayer("awful", "Awful Audrey", g);
            Player* p2 = createPlayer("mediocre", "Mediocre Mimi", g);
            Player* winner = (k % 2 == 1 ?
                g.play(p1, p2, false) : g.play(p2, p1, false));
            if (winner == p2)
                nMediocreWins++;
            delete p1;
            delete p2;
        }
        cout << "The mediocre player won " << nMediocreWins << " out of "
            << NTRIALS << " games." << endl;
        // We'd expect a mediocre player to win most of the games against
        // an awful player.  Similarly, a good player should outperform
        // a mediocre player.
    }
    else if (line[0] == '4')
    {
        int nGoodWins = 0;

        for (int k = 1; k <= NTRIALS; k++)
        {
            cout << "============================= Game " << k
                << " =============================" << endl;
            Game g(10, 10);
            addStandardShips(g);
            Player* p2 = createPlayer("good", "Gessafelstein", g);
            Player* p1 = createPlayer("mediocre", "Mediocre Mimi", g);
            Player* winner = (k % 2 == 1 ?
                g.play(p1, p2, false) : g.play(p2, p1, false));
            if (winner == p2)
                nGoodWins++;
            delete p1;
            delete p2;
        }
        cout << "The good player won " << nGoodWins << " out of "
            << NTRIALS << " games." << endl;
    }
    else
    {
        cout << "That's not one of the choices." << endl;
    }
}
