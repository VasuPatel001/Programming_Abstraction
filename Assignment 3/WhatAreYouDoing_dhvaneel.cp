/* Dhvaneel Visaria, CS106B, SL - Josh Francis
 * Code to list all possible combinations of lowercased and uppercased
 * words in a sentence using recrusion!
 */
#include "WhatAreYouDoing.h"
#include "strlib.h"
#include<cctype>
using namespace std;

/* Helper function to convert vector of strings to a single string
 * and output it as a set!
 */
Set<string> convertVectorToSet(const Vector<string>& done){
    Set<string> result;
    string sentence;
    for(int i = 0; i < done.size(); i++){
        sentence += done[i];
    }
    result = {sentence};
    return result;
}

/* Recursive function to enlist (and store in a set) all possible combinations
 * of lowercased and uppercased words in a sentence using two vectors for
 * strings whose decision is taken (done) and for strings whose decision
 * is yet to be taken (remaining)
 */
Set<string> allEmphasesOfRec(Vector<string> remaining, Vector<string> done){
    if (remaining.isEmpty()){ // base case
        Set<string> result = convertVectorToSet(done); // convert done vector to single string and add to set
        return result;
    } else { // recursive case
        Set<string> result; // to store all combinations of emphases     
        string word = remaining[0];
        remaining.remove(0);
        if (isalpha(word[0])) { // a string with letters can be capitalized
            result = allEmphasesOfRec(remaining, done + toUpperCase(word)); // capitalize word
        }
        result += allEmphasesOfRec(remaining, done + word); // don't capitalize word
        return result;
    }
}

/* Wrapper function to call the recursive function for the given task */
Set<string> allEmphasesOf(const string& sentence) {
    string lowerSentence = toLowerCase(sentence); // all words in sentence to lower case

    Vector<string> done;
    Vector<string> tokens;
    tokens = tokenize(lowerSentence);

    return allEmphasesOfRec(tokens, done);
}

/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */

STUDENT_TEST("All possible combinations equal to 2^{number of words}"){
    Set<string> result = allEmphasesOf("Dhvaneel is my name!");
    EXPECT_EQUAL(result.size(), pow(2, 4));
}


/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Enumerates all options in a simple case.") {
    Set<string> expected = {
        "hello",
        "HELLO",
    };

    EXPECT_EQUAL(allEmphasesOf("Hello"), expected);
}

PROVIDED_TEST("Each option has the right length.") {
    string sentence = "Hello, world!";
    for (string option: allEmphasesOf(sentence)) {
        EXPECT_EQUAL(option.length(), sentence.length());
    }
}

PROVIDED_TEST("Enumerates all options in a more typical case.") {
    Set<string> expected = {
        "you are?",
        "you ARE?",
        "YOU are?",
        "YOU ARE?"
    };

    EXPECT_EQUAL(allEmphasesOf("You Are?"), expected);
}

PROVIDED_TEST("Stress Test: Recursion only branches on words (should take under a second)") {
    /* We're producing a string consisting of fifty copies of the * character. This tokenizes
     * into fifty separate stars. A star is the same whether or not you capitalize it - there
     * is no such thing as an "upper-case" or "lower-case" star. Therefore, your code should
     * not try to form two versions of the sentence, one with the star capitalized and one
     * without, because the two versions will end up being the same and the work to compute
     * both options will dramatically increase the runtime.
     *
     * For reference, if you do try branching the recursion and checking what happens both if
     * you capitalize the star and if you don't, you'll try exploring 2^50 different possible
     * capitalizations. That's 1,125,899,906,842,624 options, and even doing a billion of
     * these a second is going to take over two years to generate them all! And of course,
     * that's all wasted work, since there's only one way to capitalize this sentence, and
     * that's just to leave it as-is.
     *
     * If your code is hanging when this test is running, it likely means that your code is
     * trying to enumerate all of these options. See if you can edit your code so that, if
     * you're given a non-word token, you just leave it as-is and don't change anything.
     */
    string punctuation(50, '*'); // 50 copies of *

    /* The only emphasis is itself. */
    Set<string> expected = {
        punctuation
    };

    EXPECT_EQUAL(allEmphasesOf(punctuation), expected);
}

PROVIDED_TEST("Stress test: Generates each option once (should take at most a few seconds)") {
    /* This sentence has 13 words in it. There are therefore 2^13 = 8192 possible emphases for
     * the words there, which is a big number but not so large that the computer can't handle
     * it if generates each emphasis exactly once.
     *
     * On the other hand, if your code tries to generate the same emphases multiple times,
     * this test may take a very, very long time to complete, and might even appear to freeze
     * up.
     *
     * If your code gets stuck in this test, trace through your code and confirm that you can't
     * produce the same emphasis multiple times. Check to make sure you aren't, for example,
     * looping over every token in the input sentence and deciding which one to capitalize
     * next. The recursion here follows more of an include/exclude type pattern (more like
     * subsets and combinations) than it does a "which is next?" type pattern (more like
     * permutations).
     */
    string yeats = "Turing and turning in a widening gyre / the falcon cannot hear the falconer.";
    EXPECT_EQUAL(allEmphasesOf(yeats).size(), 8192);
}
