/** File Header: A simulator for rising sea level in the world.
 * Written code examplifies the use of Breadth First Seach using queues.
 */

#include "RisingTides.h"
#include "GUI/SimpleTest.h"
#include "queue.h"
using namespace std;

// Function prototype:
Vector<GridLocation> isInBounds(const Grid<bool>& flood, GridLocation cell);

/**
 * @brief floodedRegionsIn
 * @param terrain
 * @param sources
 * @param height
 * @return a Grid of type boolean indicating the locations which are flooded (i.e. true)
 */
Grid<bool> floodedRegionsIn(const Grid<double>& terrain,
                            const Vector<GridLocation>& sources,
                            double height) {

    //initializing variables
    Grid<bool> grid_flood(terrain.numRows(), terrain.numCols(), false);
    Queue<GridLocation> grid_loc;


    for (GridLocation source_cell: sources) {
        //check for in bounds of source cell
        if (! terrain.inBounds(source_cell.row, source_cell.col)) {
                error("Please enter source cell which is in terrain bound");
        }
        //source cell having value <= height is flooded and added to queue
        else if((terrain[source_cell.row][source_cell.col] <= height)) {
            grid_flood[source_cell.row][source_cell.col] = true;
            grid_loc.enqueue({source_cell.row,source_cell.col});
        }
    }

    //dequeue grid_loc for exploring adjoining cells using BFS
    while(! grid_loc.isEmpty()) {
        GridLocation cell = grid_loc.dequeue();
        Vector<GridLocation> cardinal_cell_vctr;

        //Generate "cardinal_cell_vctr" vector by checking cell inBounds and grid cells which haven't been flodded.
        cardinal_cell_vctr = isInBounds(grid_flood, cell);

        //check "cardinal_cell" having value <= height is flooded and added to queue
        for (GridLocation cardinal_cell: cardinal_cell_vctr) {
            if(terrain[cardinal_cell.row][cardinal_cell.col] <= height) {
                grid_flood[cardinal_cell.row][cardinal_cell.col] = true;
                grid_loc.enqueue({cardinal_cell.row,cardinal_cell.col});
            }
        }
    }
    return grid_flood;
}

/**
 * @brief isInBounds
 * @param flood
 * @param cell
 * @return a Vector of cardinal cells to the input "cell" if they are inBounds and are yet to be flooded.
 */

Vector<GridLocation> isInBounds(const Grid<bool>& flood, GridLocation cell) {
    Vector<GridLocation> cardinal;
    if ((flood.inBounds(cell.row+1, cell.col) && (flood[cell.row+1][cell.col] == false))) {
        cardinal.add({cell.row+1, cell.col});
    }
    if (flood.inBounds(cell.row-1, cell.col) && (flood[cell.row-1][cell.col] == false)) {
        cardinal.add({cell.row-1, cell.col});
    }
    if (flood.inBounds(cell.row, cell.col+1) && (flood[cell.row][cell.col+1] == false)) {
        cardinal.add({cell.row, cell.col+1});
    }
    if (flood.inBounds(cell.row, cell.col-1) && (flood[cell.row][cell.col-1] == false)) {
        cardinal.add({cell.row, cell.col-1});
    }
    return cardinal;
}

/***** Test Cases Below This Point *****/
PROVIDED_TEST("Nothing gets wet if there are no water sources.") {
    Grid<double> world = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        // empty
    };

    /* There are no water sources, so nothing should be underwater. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false, false, false },
        { false, false, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Everything gets wet if all locations are below the water level.") {
    Grid<double> world = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Everything should flood; there are no barriers to stop the water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true,  true },
        {  true,  true,  true },
        {  true,  true,  true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't cross a vertical levee.") {
    Grid<double> world = {
        { 0, 2, 0 },
        { 0, 2, 0 },
        { 0, 2, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Only locations to the left of the barrier should be under water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true, false, false },
        {  true, false, false },
        {  true, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't cross a diagonal levee.") {
    Grid<double> world = {
        { 0, 0, 2 },
        { 0, 2, 0 },
        { 2, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Water only flows in the four cardinal directions, so it can't
     * pass through the barrier. Only the top should be flooded.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true, false },
        {  true, false, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't flow diagonally.") {
    Grid<double> world = {
        { 0, 2, 0 },
        { 2, 0, 2 },
        { 0, 2, 0 }
    };

    Vector<GridLocation> sources = {
        { 1, 1 }
    };

    /* Water should be trapped in the center, since it can't move
     * diagonally.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false, false, false },
        { false,  true, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can flow in all cardinal directions.") {
    Grid<double> world = {
        { 2, 0, 2 },
        { 0, 0, 0 },
        { 2, 0, 2 }
    };

    Vector<GridLocation> sources = {
        { 1, 1 }
    };

    /* The water in this case should flow up, down, left, and right. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false,  true, false },
        {  true,  true,  true },
        { false,  true, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can flow from multiple sources.") {
    Grid<double> world = {
        { 0, 0, 2 },
        { 0, 2, 0 },
        { 2, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 },
        { 2, 2 }
    };

    /* Everything except the levee should be under water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true, false },
        {  true, false,  true },
        { false,  true,  true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Handles asymmetric worlds and non-square grids") {
    Grid<double> world = {
        { 3, 1, 4, 1 },
        { 5, 9, 2, 6 },
        { 5, 3, 5, 8 }
    };

    /* Initial test - water shouldn't leak out from the 2 if the height is 3.5. */
    Vector<GridLocation> sources = {
        { 1, 2 }
    };

    Grid<bool> expected = {
        { false, false, false, false },
        { false, false,  true, false },
        { false, false, false, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 3.5), expected);

    /* Now, increase the water height to 4.5. */
    expected = {
        {  true,  true,  true,  true },
        { false, false,  true, false },
        { false, false, false, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 4.5), expected);

    /* Now, increase the water height to 5.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true, false,  true, false },
        {  true,  true,  true, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 5.5), expected);

    /* Now, increase the water height to 6.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true, false,  true,  true },
        {  true,  true,  true, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 6.5), expected);

    /* Now, increase the water height to 9.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true,  true,  true,  true },
        {  true,  true,  true,  true },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 9.5), expected);
}

PROVIDED_TEST("Stress test: Handles a large, empty world quickly.") {
    Grid<double> world(100, 100); // Large world, everything defaults to 0 height.
    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* This may take a long time to complete if the solution is inefficient. Look
     * for things like
     *
     * 1. passing around large objects by *value* rather than by *reference*,
     * 2. revisiting the same squares multiple times (e.g. flooding the same
     *    cell many times due to not checking if something is flooded),
     *
     * etc.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    EXPECT_EQUAL(water.numRows(), world.numRows());
    EXPECT_EQUAL(water.numCols(), world.numCols());

    /* Everything should be flooded. */
    for (int row = 0; row < world.numRows(); row++) {
        for (int col = 0; col < world.numCols(); col++) {
            EXPECT_EQUAL(water[row][col], true);
        }
    }
}

STUDENT_TEST("Edge case of terrain only 1 cell with height > water height") {
    Grid<double> world = {
        { 2 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {false}
    };

    EXPECT_EQUAL(water, expected);
}

STUDENT_TEST("Edge case of terrain only 1 cell with height < water height") {
    Grid<double> world = {
        { 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {true}
    };

    EXPECT_EQUAL(water, expected);
}

STUDENT_TEST("Edge case of source being outside the terrain returns error") {
    Grid<double> world = {
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 2, 1 }
    };

    EXPECT_ERROR(floodedRegionsIn(world, sources, 1.0));
}
