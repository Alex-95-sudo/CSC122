#include <iostream>   // used for input/output (
#include <vector>     // used for dynamic arrays 
#include <string>     // used for text handling
#include <cctype>     // used for tolower()

using namespace std;

// struct used to store coordinates (row/col)
struct Position {
    int row;
    int col;
};

// struct used to store guard data (position + direction)
struct Guard {
    Position pos;
    char dir;
};

// FUNCTION: converts string to lowercase w/ for-loop
string toLowerCase(string text) {
    for (int i = 0; i < (int)text.size(); i++) {   // FIXED: no range-for
        text[i] = tolower(text[i]);
    }
    return text;
}

class Level {
private:
    vector<string> board;          // vector used as 2D map
    Position player;               // struct variable
    Position goal;                 // struct variable
    vector<Guard> guards;          // vector of structs

    // FUNCTION: checks bounds (uses if statements)
    bool inBounds(int r, int c) {
        return r >= 0 && r < (int)board.size() &&
               c >= 0 && c < (int)board[0].size();
    }

    // FUNCTION: checks walls (uses indexing)
    bool isWall(int r, int c) {
        return board[r][c] == '#';
    }

    // FUNCTION: checks guard position w/ loop
    bool guardHere(int r, int c) {
        for (int i = 0; i < (int)guards.size(); i++) {   // FIXED loop
            if (guards[i].pos.row == r &&
                guards[i].pos.col == c)
                return true;
        }
        return false;
    }

    // FUNCTION: vision system w/ loop + if statements
    bool seenByGuard() {
        for (int i = 0; i < (int)guards.size(); i++) {

            int r = guards[i].pos.row;
            int c = guards[i].pos.col;
            char d = guards[i].dir;

            while (true) {

                if (d == '>') c++;
                else if (d == '<') c--;
                else if (d == '^') r--;
                else if (d == 'v') r++;

                if (!inBounds(r, c)) break;
                if (isWall(r, c)) break;
                if (guardHere(r, c)) break;

                if (player.row == r && player.col == c)
                    return true;
            }
        }
        return false;
    }

    // FUNCTION: moves all guards
    void moveGuards() {
        for (int i = 0; i < (int)guards.size(); i++) {

            int newR = guards[i].pos.row;
            int newC = guards[i].pos.col;

            if (guards[i].dir == '>') newC++;
            else if (guards[i].dir == '<') newC--;
            else if (guards[i].dir == '^') newR--;
            else if (guards[i].dir == 'v') newR++;

            if (!inBounds(newR, newC) || isWall(newR, newC) || guardHere(newR, newC)) {

                if (guards[i].dir == '>') guards[i].dir = '<';
                else if (guards[i].dir == '<') guards[i].dir = '>';
                else if (guards[i].dir == '^') guards[i].dir = 'v';
                else if (guards[i].dir == 'v') guards[i].dir = '^';

                newR = guards[i].pos.row;
                newC = guards[i].pos.col;

                if (guards[i].dir == '>') newC++;
                else if (guards[i].dir == '<') newC--;
                else if (guards[i].dir == '^') newR--;
                else if (guards[i].dir == 'v') newR++;
            }

            guards[i].pos.row = newR;
            guards[i].pos.col = newC;
        }
    }

    // FUNCTION: handles player movement w/ input
    bool movePlayer(char input) {

        int newR = player.row;
        int newC = player.col;

        if (input == 'w') newR--;
        else if (input == 's') newR++;
        else if (input == 'a') newC--;
        else if (input == 'd') newC++;

        if (!inBounds(newR, newC) || isWall(newR, newC)) {
            cout << "Blocked by wall.\n";
            return true;
        }

        if (guardHere(newR, newC)) {
            cout << "Caught by a guard!\n";
            return false;
        }

        player.row = newR;
        player.col = newC;

        if (player.row == goal.row && player.col == goal.col) {
            cout << "You reached the goal!\n";
            return false;
        }

        return true;
    }

public:
    // CONSTRUCTOR used to initialize level data
    Level(vector<string> b, vector<Guard> g, Position p, Position go) {
        board = b;
        guards = g;
        player = p;
        goal = go;
    }

    // FUNCTION: displays map w/ loops
    void draw() {
        vector<string> temp = board;

        temp[player.row][player.col] = '@';

        for (int i = 0; i < (int)guards.size(); i++) {
            temp[guards[i].pos.row][guards[i].pos.col] = guards[i].dir;
        }

        for (int r = 0; r < (int)temp.size(); r++) {
            cout << temp[r] << endl;
        }
    }

    // MAIN GAME LOOP using while
    void play() {

        bool running = true;

        while (running) {

            draw();

            if (seenByGuard()) {
                cout << "You were spotted!\n";
                break;
            }

            cout << "Move (WASD): ";
            char move;
            cin >> move;
            move = tolower(move);

            running = movePlayer(move);

            if (running)
                moveGuards();
        }
    }
};


// FUNCTION: creates level 1
Level makeLevel1() {

    vector<string> map;
    map.push_back("########");
    map.push_back("#   v  #");
    map.push_back("# > #  #");
    map.push_back("#   #  #");
    map.push_back("#@    $#");
    map.push_back("########");

    vector<Guard> guards;

    Guard g1;
    g1.pos.row = 1;
    g1.pos.col = 4;
    g1.dir = 'v';
    guards.push_back(g1);

    Guard g2;
    g2.pos.row = 2;
    g2.pos.col = 2;
    g2.dir = '>';
    guards.push_back(g2);

    Position start;
    start.row = 4;
    start.col = 1;

    Position goal;
    goal.row = 4;
    goal.col = 6;

    return Level(map, guards, start, goal);
}


// FUNCTION: creates level 2
Level makeLevel2() {

    vector<string> map;
    map.push_back("#########");
    map.push_back("#   >   #");
    map.push_back("# ### # #");
    map.push_back("# @   #$#");
    map.push_back("#   v   #");
    map.push_back("#########");

    vector<Guard> guards;

    Guard g1;
    g1.pos.row = 1;
    g1.pos.col = 4;
    g1.dir = '>';
    guards.push_back(g1);

    Guard g2;
    g2.pos.row = 4;
    g2.pos.col = 4;
    g2.dir = 'v';
    guards.push_back(g2);

    Position start;
    start.row = 3;
    start.col = 2;

    Position goal;
    goal.row = 3;
    goal.col = 7;

    return Level(map, guards, start, goal);
}


// MAIN FUNCTION
int main() {

    Level level1 = makeLevel1();
    Level level2 = makeLevel2();

    while (true) {

        cout << "\nWelcome to Ultra-Spy!\n";
        cout << "1) A New Enemy\n";
        cout << "2) The Truth of the Weapon\n";
        cout << "Enter choice: ";

        string input;
        cin >> input;

        input = toLowerCase(input);

        if (input == "1" || input == "a new enemy") {
            level1.play();
        }
        else if (input == "2" || input == "the truth of the weapon") {
            level2.play();
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}