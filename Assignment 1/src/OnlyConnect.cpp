/* File: OnlyConnect.cpp
 *
 * interesting or noteworthy in my implementation:
 * Ans: My student testing code checks for the alpha-numeric combination and
 * boundary condition of empty strings and blank spaces.
 *
 * Puzzle: How to simplify the problem if the we were asked to capitalize all but vowels: i.e. capitalize Consonants
 * and leave special character as it is.
 */
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"
#include "strlib.h"
#include <cctype>
using namespace std;

string isConsonant(char ch);

string onlyConnectize(string phrase) {
    if  (phrase == "") {
        return "";
    } else {
        return isConsonant(phrase[0]) + onlyConnectize(phrase.substr(1));
    }
}

string isConsonant(char ch) {
    ch = toLowerCase(ch);
    if ((isalpha(ch) != 0) && (ch != 'a') && (ch != 'e') && (ch != 'i') && (ch != 'o') && (ch != 'u')) {
        return toUpperCase(charToString(ch));
    }
    return "";
}

/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

/* * * * * * Student Test Cases * * * * * */

STUDENT_TEST("Alpha-numeric") {
    EXPECT_EQUAL(onlyConnectize("caT@123"), "CT");
    EXPECT_EQUAL(onlyConnectize("b@t_$"), "BT");
}

STUDENT_TEST("Empty String & blank spaces") {
    EXPECT_EQUAL(onlyConnectize(""), "");
    EXPECT_EQUAL(onlyConnectize(" "), "");
}

STUDENT_TEST("All Vowels test") {
    EXPECT_EQUAL(onlyConnectize("AeIoU"), "");
}

STUDENT_TEST("All Consonant test") {
    EXPECT_EQUAL(onlyConnectize("BcDfghjkLm"), "BCDFGHJKLM");
}
