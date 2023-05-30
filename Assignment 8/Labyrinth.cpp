/* File header: This file contains the function to check if the provided moves is path to freedom using linked lists concept.
*/
#include "Labyrinth.h"
#include <set.h>
using namespace std;

/** Helper function to isPathToFreedom()
 * @brief checkMove: check if the move is legal
 * @param cell: current cell
 * @param move: possible move
 * @return: true/false if the move is possible
 */
bool checkMove(MazeCell* cell, char& move) {
    if (move == 'N' && cell->north == nullptr) return false;
    else if(move == 'E' && cell->east == nullptr) return false;
    else if(move == 'W' && cell->west == nullptr) return false;
    else if(move == 'S' && cell->south == nullptr) return false;
    else return true;
}

/** helper function to isPathToFreedom()
 * @brief makeMove: makes a possible move
 * @param cell: current cell
 * @param move: move to be made in the given direction
 */
void makeMove(MazeCell*& cell, char& move) {
    if (move == 'N') cell = cell->north;
    else if(move == 'E') cell = cell->east;
    else if(move == 'W') cell = cell->west;
    else if(move == 'S') cell = cell->south;
}

/**
 * @brief isPathToFreedom: checks if the given moves is path to freedom
 * @param start: starting cell in the maze
 * @param moves: string of moves made up of N/S/E/W
 * @return: true/false if the given moves is path to freedom
 */
bool isPathToFreedom(MazeCell* start, const string& moves) {
    Set<Item> collected;
    MazeCell* cell = start;
    for (char ch: moves) {

        if (cell->whatsHere != Item::NOTHING) {
            collected.add(cell->whatsHere);
        }
        // Check 1: all moves are legal & if so move the cell to "ch" move
        if (checkMove(cell, ch)) {
            makeMove(cell, ch);
        }
        else return false;
    }
    // check for presence of Item in edge case (i.e. when the move made)
    if (cell->whatsHere != Item::NOTHING) {
        collected.add(cell->whatsHere);
    }

    // Check 2: it finds all 3 things in any order
    return (collected.contains(Item::POTION) && collected.contains(Item::SPELLBOOK) && collected.contains(Item::WAND));

}


/* * * * * * Test Cases Below This Point * * * * * */
#include "GUI/SimpleTest.h"
#include "Demos/MazeGenerator.h"

/* Optional: Add your own custom tests here! */



/* * * * * Provided Tests Below This Point * * * * */

/* Utility function to free all memory allocated for a maze. */
void deleteMaze(const Grid<MazeCell*>& maze) {
    for (auto* elem: maze) {
        delete elem;
    }
    /* Good question to ponder: why don't we write 'delete maze;'
     * rather than what's shown above?
     */
}

PROVIDED_TEST("Checks paths in the sample maze.") {
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN"));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES"));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW"));
    EXPECT(!isPathToFreedom(maze[2][2], "SWWN"));
    EXPECT(!isPathToFreedom(maze[2][2], "WNNE"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT(!isPathToFreedom(maze[2][2], "WW"));
    EXPECT(!isPathToFreedom(maze[2][2], "NN"));
    EXPECT(!isPathToFreedom(maze[2][2], "EE"));
    EXPECT(!isPathToFreedom(maze[2][2], "SS"));

    deleteMaze(maze);
}

PROVIDED_TEST("Can't walk through walls.") {
    auto maze = toMaze({"* S *",
                        "     ",
                        "W * P",
                        "     ",
                        "* * *"});

    EXPECT(!isPathToFreedom(maze[1][1], "WNEES"));
    EXPECT(!isPathToFreedom(maze[1][1], "NWSEE"));
    EXPECT(!isPathToFreedom(maze[1][1], "ENWWS"));
    EXPECT(!isPathToFreedom(maze[1][1], "SWNNEES"));

    deleteMaze(maze);
}

PROVIDED_TEST("Works when starting on an item.") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "EE"));
    EXPECT(isPathToFreedom(maze[0][1], "WEE"));
    EXPECT(isPathToFreedom(maze[0][2], "WW"));

    deleteMaze(maze);
}

