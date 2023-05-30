/* File Header: This file contains the code for evaluating the weight on the
 * shoulder of a given person in a pyramid.
*/
#include "HumanPyramids.h"
#include "error.h"
#include <tuple>
#include "map.h"
using namespace std;

/** Recursive function to evaluate the weight on the back of a person in a pyramid.
 * @brief weightOnBackOfRec
 * @param row
 * @param col
 * @param table
 * @return weight on the back of a given person
 */
double weightOnBackOfRec(int row, int col, Map<tuple<int, int>, double>& table) {
    tuple<int, int> arg = make_tuple(row, col);
    double personWeight = 160;
    if (row == 0) {
        table[arg] = 0;
        return 0;
    }
    else if(table.containsKey(arg)) return table[arg];
    else {
        double weightOnBack = 0;
        if (col != 0) {
            weightOnBack += (personWeight/2) + weightOnBackOfRec(row -1, col - 1, table)/2;
        }
        if (col != row) {
            weightOnBack += (personWeight/2) + weightOnBackOfRec(row-1, col, table)/2;
        }
        table[arg] = weightOnBack;
        return weightOnBack;
    }
}


//tuple<int, int> arg = make_tuple(row, col);
//double personWeight = 160;
//// Base Case: person on top of the pyramid has 0 weight on his/her back
//if (row == 0) {
//    table[arg] = 0;
//    return 0;
//}
//// Base Case: check for the weight on back of (x, y)th position person using a provided map
//else if (table.containsKey(arg)) {
//    return table[arg];
//} else {
//    double weightSupported = 0;
//    // Case 1: check for weight on the Left shoulder
//    if (col != 0) {
//        weightSupported += (personWeight / 2) + (weightOnBackOfRec(row - 1, col - 1, table) / 2);
//    }
//    // Case 2:check for weight on the Right shoulder
//    if (col != row) {
//        weightSupported += (personWeight / 2) + (weightOnBackOfRec(row - 1, col, table) / 2);
//    }
//    table[arg] = weightSupported;
//    return weightSupported;
//}
/** Wrapper function to call the weightOnBackOfRec();
 * @brief weightOnBackOf
 * @param row
 * @param col
 * @param pyramidHeight
 * @return weight on the back of a given person
 */
double weightOnBackOf(int row, int col, int pyramidHeight) {
    Map<tuple<int, int>, double> memoization;
    if ((row >= pyramidHeight) || (col > row) || (row < 0) || (col < 0)) {
        error("Index out of bounds");
    } 
    return weightOnBackOfRec(row, col, memoization);
}


/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"


STUDENT_TEST("Check Person A (0, 0)") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(0, 0, 5), 0);
}


/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

STUDENT_TEST("Memoization test for edge cases") {
    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT_EQUAL(weightOnBackOf(0, 0, 200), 0);
    EXPECT(weightOnBackOf(209, 5, 210) > 1000);
}
