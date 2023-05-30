/* File: PlayingFair.cpp
 *
 * interesting or noteworthy in my implementation:
 * Ans: Interesting thing observed is the diagram pattern in the output console.
 */
#include "PlayingFair.h"
#include "GUI/SimpleTest.h"
#include "error.h"
#include <cmath>
using namespace std;

string aSequenceOfOrder(int n) {
    if (n == 0) {
        return "A";
    }
    else if (n < 0) {
        error("Please enter an integer >= 0");
    } else {
        return aSequenceOfOrder(n-1) + bSequenceOfOrder(n-1);
    }
}

string bSequenceOfOrder(int n) {
    if (n == 0) {
        return "B";
    }
    else if (n < 0) {
        error("Please enter an integer >= 0");
    } else {
        return bSequenceOfOrder(n-1) + aSequenceOfOrder(n-1);
    }
}



/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Sequences of order 3 are correct.") {
    /* Some very basic checks. */
    EXPECT_EQUAL(aSequenceOfOrder(3), "ABBABAAB");
    EXPECT_EQUAL(bSequenceOfOrder(3), "BAABABBA");
}

PROVIDED_TEST("Only characters should be As and Bs.") {
    for (int i = 0; i < 10; i++) {
        for (char ch: aSequenceOfOrder(i)) {
            EXPECT(ch == 'A' || ch == 'B');
        }
    }
}

PROVIDED_TEST("A-sequence of positive order should have equal As and Bs.") {
    /* Exclude the sequence of order 0, which is just a single character. */
    for (int i = 1; i < 10; i++) {
        int as = 0;
        int bs = 0;
        for (char ch: aSequenceOfOrder(i)) {
            if (ch == 'A') as++;
            else bs++;
        }

        EXPECT_EQUAL(as, bs);
    }
}

PROVIDED_TEST("Triggers error on negative inputs.") {
    /* The EXPECT_ERROR macro expects the given expression to call error(). Remember that
     * you need to guard against invalid inputs.
     */
    EXPECT_ERROR(aSequenceOfOrder(-137));
    EXPECT_ERROR(bSequenceOfOrder(-137));
}

/* * * * * * Student Test Cases * * * * * */

STUDENT_TEST("Test for length of a/b sequence to be 2^n") {
    for (int i = 0; i < 10; i++) {
        int len = aSequenceOfOrder(i).size();
        EXPECT_EQUAL(pow(2,i), len);
    }
}
