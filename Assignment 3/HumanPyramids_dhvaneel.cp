/* Dhvaneel Visaria, CS106B, SL - Josh Francis
 * Function to recursively calculate weight on back of person at given
 * coordinates (row, col)
 */
#include "HumanPyramids.h"
#include "error.h"
#include "map.h"
using namespace std;

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */
//double weightOnBackOf(int row, int col, int pyramidHeight) {
//    double weightHuman = 160;
//    if (row >= pyramidHeight || row < 0 || col < 0 || col > row){ // person out of bounds
//        error("Person out of bounds!");
//        return 0.0;
//    } else if (row == 0 && col == 0){ // base case - top of pyramid
//        return 0.0;
//    } else { // recursion
//        if (col == 0){ // start of pyramid row
//            return (weightHuman + weightOnBackOf(row - 1, col, pyramidHeight)) / 2.0;
//        } else if (col == row) { // end of pyramid row
//            return (weightHuman + weightOnBackOf(row - 1, col - 1, pyramidHeight)) / 2.0;
//        } else { // all other elements of pyramid row
//            return weightHuman + (weightOnBackOf(row - 1, col - 1, pyramidHeight) +
//                    weightOnBackOf(row - 1, col, pyramidHeight)) / 2.0;
//        }
//    }
//}

/* Function - to calcualte weight on back of a person recursively using memoization
 * Input: Map with 2-element vector as key and the (row, col) human location key
 * Output: Weight on back of person at (row, col)
 */
double weightOnBackOfRec(Vector<int> key, Map<Vector<int>, double>& lookUp){ // pass lookup table by reference
    double weightHuman = 160;
    double value = 0;

    int row = key[0];
    int col = key[1];

    if (row == 0 && col == 0){ // base case - top of pyramid
        return 0.0;
    } else if (lookUp.containsKey(key)) {
        return lookUp[key];
    } else {
        Vector<int> key1 = {row - 1, col}; // right shoulder
        Vector<int> key2 = {row - 1, col - 1}; // left shoulder

        if (col == 0){ // start of pyramid row
            value = (weightHuman + weightOnBackOfRec(key1, lookUp)) / 2.0;
        } else if (col == row) { // end of pyramid row
            value = (weightHuman + weightOnBackOfRec(key2, lookUp)) / 2.0;
        } else { // all other elements of pyramid row
            value = weightHuman + (weightOnBackOfRec(key1, lookUp) +
                                  weightOnBackOfRec(key2, lookUp)) / 2.0;
        }
        lookUp[key] = value; // add new key, value pair to lookup table
        return value;
    }
}

// wrapper function
double weightOnBackOf(int row, int col, int pyramidHeight) {
    if (row >= pyramidHeight || row < 0 || col < 0 || col > row){ // person out of bounds
        error("Person out of bounds!");
    } else { // call recursive function
        Map<Vector<int>, double> lookUp; // lookup table for memoization
        Vector<int> key = {row, col}; // lookup table key
        return weightOnBackOfRec(key, lookUp);
    }
}






/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

STUDENT_TEST("Function reports error for person out of bounds i.e. col > row."){
    EXPECT_ERROR(weightOnBackOf(10, 11, 20));
}

STUDENT_TEST("Large value expected for large pyramids."){
    EXPECT(weightOnBackOf(10,5,20) > 1000);
    EXPECT(weightOnBackOf(20,15,30) > 1000);
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
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */
    //SHOW_ERROR("This test is configured to always fail until you delete this line from\n         HumanPyramids.cpp. Once you have implemented memoization and want\n         to check whether it works correctly, remove the indicated line.");

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

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
