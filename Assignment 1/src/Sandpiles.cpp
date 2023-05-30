/* File: Sandpiles.cpp
 *
 * interesting or noteworthy in my implementation:
 * 1. Recursion structure for this code is a bit different than one taught in class (uses nested if instead of if...else)
 * 2. multiple recursoins calls (4 times) to test distribution of each of the 4 grains
 */
#include "Sandpiles.h"
#include "GUI/SimpleTest.h"
using namespace std;

void dropSandOn(Grid<int>& world, int row, int col) {
    //simplest step: check for inbound and add 1 grain to that cell
    if (world.inBounds(row,col)) {
        world[row][col] += 1;

        //check if cell > 3, then distribute the grain to adjoining cells using recursion
        if (world[row][col] == 4) {
            world[row][col] = 0;
            dropSandOn(world, row-1, col);
            dropSandOn(world, row+1, col);
            dropSandOn(world, row, col-1);
            dropSandOn(world, row, col+1);
        }
    }
}

/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Dropping into an empty cell only changes that cell.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 0, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 3, 3 },
        { 3, 1, 3 },
        { 3, 3, 3 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Non-chaining topples work.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0 },
        { 1, 3, 1 },
        { 0, 2, 0 }
    };
    Grid<int> after = {
        { 0, 1, 0 },
        { 2, 0, 2 },
        { 0, 3, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Two topples chain.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0, 0 },
        { 0, 3, 3, 0 },
        { 0, 0, 0, 0 }
    };
    Grid<int> after = {
        { 0, 1, 1, 0 },
        { 1, 1, 0, 1 },
        { 0, 1, 1, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}


/* * * * * * Student Test Cases * * * * * */

STUDENT_TEST("1X1 world (extremely small world case") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 3 }
    };
    Grid<int> after = {
        { 0 }
    };

    dropSandOn(before, 0, 0);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

STUDENT_TEST("Five-level Chaining topples work.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 3, 3, 2 },
        { 2, 3, 3 },
        { 0, 2, 3 }
    };
    Grid<int> after = {
        { 1, 3, 0 },
        { 1, 0, 3 },
        { 2, 1, 1 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}
