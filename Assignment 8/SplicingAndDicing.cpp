/* File header: This file contains the functions for splicing and dicing of nucleotide using doubly-linked lists
*/
#include "SplicingAndDicing.h"
using namespace std;

/**
 * Frees all memory in the chain of nucleotides pointed at by dna. If the
 * input is a null pointer, this function has no effect.
 *
 * This function should run in time O(n) and should not use any containers
 * (e.g. Vector, HashSet, etc.).
 */
void deleteNucleotides(Nucleotide* dna) {
    while (dna != nullptr) {
        Nucleotide* next = dna->next;
        delete dna;
        dna = next;
    }
}

/**
 * Returns a string spelling out the contents of the nucleotide sequence passed
 * as a parameter.
 *
 * This function should run in time O(n) and should not use any containers
 * (e.g. Vector, HashSet, etc.).
 */
string fromDNA(Nucleotide* dna) {
    string result;
    if (dna == nullptr) return "";
    while (dna != nullptr) {
        result += dna->value;
        dna = dna->next;
    }
    return result;
}

/**
 * Produces a new strand of nucleotides spelling out the sequence given in
 * str.
 *
 * This function should run in time O(n) and should not use any containers
 * (e.g. Vector, HashSet, etc.).
 */
Nucleotide* toStrand(const string& str) {
    Nucleotide* tail;
    Nucleotide* dna = nullptr;
    for (char ch: str) {
        Nucleotide* newElem = new Nucleotide;
        newElem->value = ch;

        /* New newElem goes at the end. */
        newElem->next = nullptr;

        /* Case 1: dna is empty. */
        if (dna == nullptr) {
            dna = tail = newElem;
            newElem->prev = nullptr;
        }
        /* Case 2: dna already has some nucleotide */
        else {
            /* last nucleotide of dna should point to the new item. */
            tail->next = newElem;
            newElem->prev = tail;
            /* That new item is now the last newElem in the list. */
            tail = newElem;
        }
    }
    return dna;
}

/** Helper function for findFirst()
 * @brief checkWithinTarget: checks all the matching character in the target with dna in the order
 * @param dna: orginial dna provided to us
 * @param target
 * @return: true/false if all the characters in the target match with dna
 */
bool checkWithinTarget(Nucleotide* dna, Nucleotide* target) {
    // edge case: when the function call contains target as nullptr
    if (target == nullptr) return true;

    // loop current pointer over the dna nucleotoids to check for matching characters in a sequence
    for (Nucleotide* curr = dna; curr != nullptr; curr = curr->next) {
        // check for matching value of target and curr pointer
        if (curr->value == target->value) {
            // update target pointer
            target = target->next;
            // once finised checking all characters of target: return true
            if (target == nullptr) return true;
        }
        else return false;
    }
    return false;
}

/**
 * Searches dna for the first copy of the sequence target, returning a pointer
 * to that occurrence or nullptr if the target sequence isn't present.
 *
 * This function doesn't have any set big-O runtime target, but should be
 * fast enough to pass the stress tests in a few seconds each.
 *
 * This function should not use any containers (e.g. Vector, HashSet, etc.)
 */
Nucleotide* findFirst(Nucleotide* dna, Nucleotide* target) {
    if (target == nullptr) return dna;

    // loop current pointer over the dna nucleotoids to check for
    for (Nucleotide* curr = dna; curr != nullptr; curr = curr->next) {
        // Step 1: check if the first character of target is curr->value.
        if (curr->value == target->value) {
            // Step 2: check if all the character within target matches curr in the same order
            if (checkWithinTarget(curr->next, target->next)) return curr;
        }
    }
    return nullptr;
}

/** helper function for spliceFirst()
 * @brief lengthOf: computes lenght of input dna
 * @param target: input dna
 * @return: lenght of input dna
 */
int lengthOf(Nucleotide* dna) {
    int len = 0;
    while(dna != nullptr) {
        len += 1;
        dna = dna->next;
    }
    return len;
}

/**
 * Removes the first copy of the sequence target that appears in the sequence
 * of nucleotides given as the dna parameter. If the nucleotide pointed at
 * by dna was removed, dna is updated to point to the first nucleotide after
 * the removed sequence, or nullptr if the whole sequence was removed.
 *
 * This function doesn't have any set big-O runtime target, but should be
 * fast enough to pass the stress tests in a few seconds each.
 *
 * This function should not use any containers (e.g. Vector, HashSet, etc.)
 */
bool spliceFirst(Nucleotide*& dna, Nucleotide* target) {
    // When nothing needs to be searched from nothing - answer is true
    if ((dna == nullptr) && (target == nullptr)) return true;

    else if (findFirst(dna, target) != nullptr) {
        // pointer and variable initializaiton
        Nucleotide* head = findFirst(dna, target);
        Nucleotide* tail = head;
        Nucleotide* splice = head;
        int len = lengthOf(target);

        // Step 1: update tail pointer using len
        for (int i = 1; i < len; i++) {
            tail = tail->next;
        }

        // Step 2: Rewire head->prev and tail->next
        // Case 0: if target == nullptr
        if (target == nullptr) return true;

        // Case 1: if the target == dna
        else if ((head->prev == nullptr) && (tail->next == nullptr)) {
            dna = nullptr;
            deleteNucleotides(splice);
            return true;
        }

        // Case 2: target is at the START of dna
        else if (head->prev == nullptr) {
            dna = tail->next;
            tail->next->prev = nullptr;
            tail->next = nullptr;
            deleteNucleotides(splice);
            return true;
        }

        // Case 3: target is at the END of dna
        else if (tail->next == nullptr) {
            head->prev->next = nullptr;
            head->prev = nullptr;
            deleteNucleotides(splice);
            return true;
        }

        // Case 4: if target is in the MIDDLE
        else {
            head->prev->next = tail->next;
            tail->next->prev = head->prev;
            head->prev = nullptr;
            tail->next = nullptr;
            deleteNucleotides(splice);
            return true;
        }
    }
    else return false;
}


/* * * * * * Test Cases Below This Point * * * * * */
#include "GUI/SimpleTest.h"
Nucleotide* nth(Nucleotide* dna, int n);
/* TODO: Add your own custom tests here! */

STUDENT_TEST("deleteNucleotides cleans up a single element.") {
    Nucleotide* dna = new Nucleotide;
    dna->value = 'A';
    dna->prev = nullptr;
    dna->next = nullptr;
    deleteNucleotides(dna);
}

STUDENT_TEST("fromDNA handles special-character strings.") {
    Nucleotide* singleton = new Nucleotide;
    singleton->value = '$';
    singleton->next = singleton->prev = nullptr;

    EXPECT_EQUAL(fromDNA(singleton), "$");

    deleteNucleotides(singleton);
}

STUDENT_TEST("toStrand converts single-special character strings.") {
    Nucleotide* dna = toStrand("$");
    EXPECT(dna != nullptr);
    EXPECT_EQUAL(dna->value, '$');
    EXPECT_EQUAL(dna->next, nullptr);
    EXPECT_EQUAL(dna->prev, nullptr);

    deleteNucleotides(dna);
}

STUDENT_TEST("findFirst works for special character when target is in the middle.") {
    Nucleotide* dna    = toStrand("!@#$%^&*()");
    Nucleotide* target = toStrand("$%^&");

    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 3));

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

STUDENT_TEST("spliceFirst works for special character when removing the whole strand.") {
    Nucleotide* dna    = toStrand("!@#$%^&*()");
    Nucleotide* target = toStrand("!@#$%^&*()");

    EXPECT(spliceFirst(dna, target));
    EXPECT_EQUAL(dna, nullptr);

    deleteNucleotides(target);
}


/* * * * * Provided Tests Below This Point * * * * */
#include "vector.h"
#include "strlib.h"
#include <fstream>

PROVIDED_TEST("deleteNucleotides cleans up a simple sequence.") {
    Nucleotide* dna = new Nucleotide;
    dna->value = 'A';
    dna->prev = nullptr;

    dna->next = new Nucleotide;
    dna->next->value = 'C';
    dna->next->prev = dna;
    dna->next->next = nullptr;

    /* Confirm that the cleanup procedure actually cleans things up. */
    deleteNucleotides(dna);
}

PROVIDED_TEST("deleteNucleotides handles empty sequences.") {
    deleteNucleotides(nullptr);
}

const int kLargeNumber = 300000;

/* Utility function that returns the contents of a file. If the last argument
 * is not -1, only that many characters will be returned.
 */
string contentsOf(const string& filename, int numChars = -1) {
    ifstream input(filename);
    if (!input) error("Cannot open file " + filename);

    ostringstream buffer;
    buffer << input.rdbuf();
    string result = trim(buffer.str());

    return numChars == -1? result : result.substr(0, numChars);
}

/* Utility function that manually constructs a chain of nucleotides holding
 * the given string. This function uses the Vector type, so you cannot use
 * the implementation strategy shown here in your implementation of toStrand.
 */
Nucleotide* vectorToStrand(const string& text) {
    Vector<Nucleotide*> cells;

    for (size_t i = 0; i < text.size(); i++) {
        cells += new Nucleotide;
    }
    for (size_t i = 0; i < text.size(); i++) {
        cells[i]->value = text[i];
        cells[i]->prev = (i == 0? nullptr : cells[i - 1]);
        cells[i]->next = (i == text.size() - 1? nullptr : cells[i + 1]);
    }

    return cells[0];
}

/* Utility function that returns the contents of the E. Coli genome. */
const string& eColiGenome() {
    static unique_ptr<string> theResult;
    if (!theResult) {
        theResult.reset(new string(contentsOf("res/EColi.dna", kLargeNumber)));
    }
    return *theResult;
}

PROVIDED_TEST("Stress Test: Can deallocate lengthy sequences.") {
    Nucleotide* ecoli = vectorToStrand(eColiGenome());

    /* Free all memory allocated. */
    deleteNucleotides(ecoli);
}

PROVIDED_TEST("fromDNA handles empty strings.") {
    EXPECT_EQUAL(fromDNA(nullptr), "");
}

PROVIDED_TEST("fromDNA handles single-character strings.") {
    Nucleotide* singleton = new Nucleotide;
    singleton->value = 'A';
    singleton->next = singleton->prev = nullptr;

    EXPECT_EQUAL(fromDNA(singleton), "A");

    deleteNucleotides(singleton);
}

PROVIDED_TEST("fromDNA handles multicharacter strings.") {
    Nucleotide* one   = new Nucleotide;
    Nucleotide* two   = new Nucleotide;
    Nucleotide* three = new Nucleotide;
    Nucleotide* four  = new Nucleotide;

    one->prev    = nullptr;
    one->next    = two;

    two->prev    = one;
    two->next    = three;

    three->prev  = two;
    three->next  = four;

    four->prev   = three;
    four->next   = nullptr;

    one->value   = 'A';
    two->value   = 'C';
    three->value = 'T';
    four->value  = 'G';

    EXPECT_EQUAL(fromDNA(one), "ACTG");
    deleteNucleotides(one);
}

PROVIDED_TEST("fromDNA doesn't allocate memory.") {
    Nucleotide* one   = new Nucleotide;
    Nucleotide* two   = new Nucleotide;
    Nucleotide* three = new Nucleotide;
    Nucleotide* four  = new Nucleotide;

    one->prev    = nullptr;
    one->next    = two;

    two->prev    = one;
    two->next    = three;

    three->prev  = two;
    three->next  = four;

    four->prev   = three;
    four->next   = nullptr;

    one->value   = 'A';
    two->value   = 'C';
    three->value = 'T';
    four->value  = 'G';

    int allocs = NucleotideAlloc::instances();
    string result = fromDNA(one);
    EXPECT_EQUAL(allocs, NucleotideAlloc::instances());

    deleteNucleotides(one);
}

PROVIDED_TEST("Stress Test: fromDNA works on lengthy sequences.") {
    Nucleotide* dna = vectorToStrand(eColiGenome());

    string result = fromDNA(dna);
    EXPECT_EQUAL(result.length(), kLargeNumber);

    /* Don't use EXPECT_EQUAL; that will clobber the console. */
    EXPECT(result == eColiGenome());

    /* Free all memory allocated. */
    deleteNucleotides(dna);
}

PROVIDED_TEST("toStrand converts empty strings.") {
    Nucleotide* dna = toStrand("");

    EXPECT_EQUAL(dna, nullptr);
}

PROVIDED_TEST("toStrand converts single-character strings.") {
    Nucleotide* dna = toStrand("A");
    EXPECT(dna != nullptr);
    EXPECT_EQUAL(dna->value, 'A');
    EXPECT_EQUAL(dna->next, nullptr);
    EXPECT_EQUAL(dna->prev, nullptr);

    deleteNucleotides(dna);
}

/* Checks if a strand is linked correctly. */
bool isLinkedInStrand(Nucleotide* start) {
    /* If we're at the start of a strand, we should not have a previous pointer. */
    if (start != nullptr && start->prev != nullptr) {
        return false;
    }

    /* Walk the list, ensuring at each point that the next/prev pointers are
     * consistent with one another.
     */
    for (Nucleotide* curr = start; curr != nullptr; curr = curr->next) {
        if (curr->next != nullptr && curr->next->prev != curr) return false;
        if (curr->prev != nullptr && curr->prev->next != curr) return false;
    }

    return true;
}

PROVIDED_TEST("toStrand converts a multicharacter sequence.") {
    string original = "ACGT";
    Nucleotide* dna = toStrand(original);

    EXPECT(isLinkedInStrand(dna));

    /* Walk the sequence and confirm we see the letters we want. */
    Nucleotide* curr = dna;
    for (char ch: original) {
        /* Confirm the data here is correct. */
        EXPECT(curr != nullptr);
        EXPECT_EQUAL(curr->value, ch);

        curr = curr->next;
    }

    /* Confirm we just walked off the end. */
    EXPECT_EQUAL(curr, nullptr);

    deleteNucleotides(dna);
}

PROVIDED_TEST("Stress Test: Can load/convert E.Coli DNA (should take at most a few seconds).") {
    Nucleotide* dna = toStrand(eColiGenome());
    EXPECT(isLinkedInStrand(dna));

    /* We deliberately don't use EXPECT_EQUAL here because if this test fails, we don't
     * want to dump gigantic strings to the console.
     */
    EXPECT(fromDNA(dna) == eColiGenome());
    EXPECT(isLinkedInStrand(dna));

    deleteNucleotides(dna);
}

/* Returns a pointer to the nth cell in the nucleotide chain. */
Nucleotide* nth(Nucleotide* dna, int n) {
    for (int i = 0; i < n; i++) {
        if (dna == nullptr) error("Unexpected end of list.");
        dna = dna->next;
    }
    return dna;
}

PROVIDED_TEST("findFirst works for single nucleotide searching.") {
    Nucleotide* dna    = toStrand("ATATA");
    Nucleotide* target = toStrand("A");

    /* Search from each position to make sure we find what we expect. */
    EXPECT_EQUAL(findFirst(nth(dna, 0), target), nth(dna, 0));
    EXPECT_EQUAL(findFirst(nth(dna, 1), target), nth(dna, 2));
    EXPECT_EQUAL(findFirst(nth(dna, 2), target), nth(dna, 2));
    EXPECT_EQUAL(findFirst(nth(dna, 3), target), nth(dna, 4));
    EXPECT_EQUAL(findFirst(nth(dna, 4), target), nth(dna, 4));
    EXPECT_EQUAL(findFirst(nth(dna, 5), target), nullptr);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst works when target not present.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAAA");

    EXPECT_EQUAL(findFirst(dna, target), nullptr);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst works when target is at front.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAA");

    EXPECT_EQUAL(findFirst(dna, target), dna);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst works when target is at the back.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("CGGG");

    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 8));

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst works when target is in the middle.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("ATT");

    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 2));

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst works when target is empty.") {
    Nucleotide* dna = toStrand("AAATTTCCCGGG");

    EXPECT_EQUAL(findFirst(dna, nullptr), dna);
    deleteNucleotides(dna);
}

PROVIDED_TEST("findFirst works when DNA is empty.") {
    Nucleotide* target = toStrand("AAATTTCCCGGG");
    EXPECT_EQUAL(findFirst(nullptr, target), nullptr);
    EXPECT_EQUAL(findFirst(nullptr, nullptr), nullptr);

    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst works when target is the original sequence.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAATTTCCCGGG");

    EXPECT_EQUAL(findFirst(dna, target), dna);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst doesn't find string longer than original strand.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAATTTCCCGGGG");

    Nucleotide* result = findFirst(dna, target);
    EXPECT_EQUAL(result, nullptr);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

/* Frees the old strand and replaces it with a new one. */
void reset(Nucleotide*& dna, const string& strand) {
    deleteNucleotides(dna);
    dna = toStrand(strand);
}

PROVIDED_TEST("findFirst works when partial matches exist.") {
    /* A partial match occurs when the first characters of the target string
     * match the first characters of the DNA strand. For example, the strand
     * AAAAC matches the target AAC, but has many places where AAC "almost"
     * matches.
     *
     * This test explores a sampler of those options.
     */
    Nucleotide* dna    = toStrand("AAC");
    Nucleotide* target = toStrand("AC");

    /* Should match at position 1. */
    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 1));

    /* Expand the strand and try again. */
    reset(dna, "AAAC");
    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 2));

    /* Try AAAC versus AAC. */
    reset(dna, "AAAC");
    reset(target, "AAC");
    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 1));

    /* AAAAC versus AAC. */
    reset(dna, "AAAAC");
    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 2));

    /* Now, a trickier pattern: Try ATATATC
     *                                ATATC
     */
    reset(dna,    "ATATATC");
    reset(target,   "ATATC");
    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 2));

    /* ATATATATC
     *     ATATC
     */
    reset(dna,    "ATATATATC");
    reset(target,     "ATATC");
    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 4));

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("Stress Test: Can find at end of E.Coli (should take at most a few seconds).") {
    Nucleotide* dna = toStrand(eColiGenome());

    string tail = eColiGenome().substr(eColiGenome().size() - 80);
    Nucleotide* target = toStrand(tail);

    EXPECT(findFirst(dna, target) != nullptr);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("Stress Test: Can find E.Coli in itself (should take at most a few seconds).") {
    Nucleotide* dna    = toStrand(eColiGenome());
    Nucleotide* target = toStrand(eColiGenome());

    EXPECT_EQUAL(findFirst(dna, target), dna);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst on a missing sequence has no effect.") {
    Nucleotide* dna    = toStrand("TAGCATGATTACA");
    Nucleotide* target = toStrand("ATCG");

    /* Count number of allocations at this point. */
    int allocs = NucleotideAlloc::instances();

    /* Ensure the remove fails. Make sure that, in the course of doing so, we didn't
     * change where DNA was pointing.
     */
    Nucleotide* originalDNA = dna;
    EXPECT(!spliceFirst(dna, target));
    EXPECT_EQUAL(dna, originalDNA);

    /* Confirm the link structure is valid. */
    EXPECT(isLinkedInStrand(dna));

    /* Confirm we didn't leak any memory. If we did, it means that spliceFirst
     * either allocated or deallocated something, which it shouldn't have done
     * in this case.
     */
    EXPECT_EQUAL(allocs, NucleotideAlloc::instances());
    EXPECT_EQUAL(fromDNA(dna), "TAGCATGATTACA");

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst works in the middle of a strand.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("TTTCCC");

    /* Remove the sequence. Make sure that we didn't change where DNA was
     * pointing.
     */
    Nucleotide* originalDNA = dna;
    EXPECT(spliceFirst(dna, target));

    /* Confirm the link structure is still good. */
    EXPECT(isLinkedInStrand(dna));

    EXPECT_EQUAL(fromDNA(dna), "AAAGGG");
    EXPECT_EQUAL(dna, originalDNA);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst works at the end of a strand.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("CCCGGG");

    /* Remove the sequence. Make sure that we didn't change where DNA was
     * pointing.
     */
    Nucleotide* originalDNA = dna;
    EXPECT(spliceFirst(dna, target));

    /* Confirm the strand wiring is still correct. */
    EXPECT(isLinkedInStrand(dna));

    EXPECT_EQUAL(fromDNA(dna), "AAATTT");
    EXPECT_EQUAL(dna, originalDNA);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst works at the beginning of a strand.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAATTT");

    /* In this case, we should change where DNA is pointing. */
    Nucleotide* originalDNA = dna;
    EXPECT(spliceFirst(dna, target));
    EXPECT(isLinkedInStrand(dna));

    EXPECT_EQUAL(fromDNA(dna), "CCCGGG");
    EXPECT(dna != originalDNA);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst works when removing the whole strand.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAATTTCCCGGG");

    EXPECT(spliceFirst(dna, target));
    EXPECT_EQUAL(dna, nullptr);

    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst handles the empty string.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("");

    /* Confirm that, in doing this, we didn't change where DNA was pointing. */
    Nucleotide* originalDNA = dna;
    EXPECT(spliceFirst(dna, target));
    EXPECT(isLinkedInStrand(dna));

    EXPECT_EQUAL(fromDNA(dna), "AAATTTCCCGGG");
    EXPECT_EQUAL(dna, originalDNA);

    /* Also try removing from an empty sequence, which should succeed because
     * the empty sequence appears at the front of the empty sequence.
     */
    Nucleotide* empty = nullptr;
    EXPECT(spliceFirst(empty, target));
    EXPECT_EQUAL(empty, nullptr);

    deleteNucleotides(dna);
}

PROVIDED_TEST("spliceFirst leaves DNA unmodified except at remove site.") {
    /* Write out all the linked list cells in DNA in a Vector, just to make sure the
     * cells we're getting back match the cells we expected to see.
     */
    Nucleotide* dna = toStrand("AAACCCTTTGGG");
    Vector<Nucleotide*> nucleotides;
    for (Nucleotide* curr = dna; curr != nullptr; curr = curr->next) {
        nucleotides += curr;
    }

    /* Try removing nothing from DNA and confirm that we match the old strand. */
    Nucleotide* target = toStrand("GGGG");
    EXPECT(!spliceFirst(dna, target));

    int i = 0;
    for (Nucleotide* curr = dna; curr != nullptr; curr = curr->next) {
        EXPECT(i < nucleotides.size());
        EXPECT_EQUAL(curr, nucleotides[i]);
        i++;
    }
    EXPECT_EQUAL(i, nucleotides.size());

    deleteNucleotides(target);
    target = toStrand("CCC");

    /* Remove the C nucleotides. */
    EXPECT(nucleotides.size() >= 6);
    nucleotides.remove(3);
    nucleotides.remove(3);
    nucleotides.remove(3);
    EXPECT(spliceFirst(dna, target));

    i = 0;
    for (Nucleotide* curr = dna; curr != nullptr; curr = curr->next) {
        EXPECT(i < nucleotides.size());
        EXPECT_EQUAL(curr, nucleotides[i]);
        i++;
    }
    EXPECT_EQUAL(i, nucleotides.size());

    deleteNucleotides(target);

    /* Once more, except this time we'll remove from the front. */
    target = toStrand("AAA");

    /* Remove the A nucleotides. */
    EXPECT(nucleotides.size() >= 3);
    nucleotides.remove(0);
    nucleotides.remove(0);
    nucleotides.remove(0);

    EXPECT(spliceFirst(dna, target));
    i = 0;
    for (Nucleotide* curr = dna; curr != nullptr; curr = curr->next) {
        EXPECT(i < nucleotides.size());
        EXPECT_EQUAL(curr, nucleotides[i]);
        i++;
    }
    EXPECT_EQUAL(i, nucleotides.size());

    deleteNucleotides(target);
    deleteNucleotides(dna);
}

PROVIDED_TEST("Repeated calls to spliceFirst work on strands.") {
    string dnaStrand = "ATGATAGCCATTAGCATATAAT";
    Nucleotide* dna    = toStrand(dnaStrand);
    Nucleotide* target = toStrand("AT");

    /* Keep removing ATs until none exist. */
    while (true) {
        bool exists = (dnaStrand.find("AT") != string::npos);
        EXPECT_EQUAL(spliceFirst(dna, target), exists);
        EXPECT(isLinkedInStrand(dna));

        /* No match? Then we're done. */
        if (!exists) break;

        auto position = dnaStrand.find("AT");
        dnaStrand.erase(position, 2);
    }

    /* Confirm that we can't then pull out one more. */
    EXPECT(!spliceFirst(dna, target));

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst works when target is longer than the original strand.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAATTTCCCGGGG");

    Nucleotide* oldDNA = dna;
    EXPECT(!spliceFirst(dna, target));
    EXPECT_EQUAL(dna, oldDNA);
    EXPECT(isLinkedInStrand(dna));

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst can remove all but the first/list nucleotide.") {
    Nucleotide* dna    = toStrand("AAAAC");
    Nucleotide* target = toStrand("AAAC");

    EXPECT(spliceFirst(dna, target));
    EXPECT(isLinkedInStrand(dna));
    EXPECT_EQUAL(dna->value, 'A');
    EXPECT_EQUAL(dna->next,  nullptr);

    reset(dna,   "CAAAA");
    reset(target,"CAAA" );

    Nucleotide* expected = nth(dna, 4);
    EXPECT(spliceFirst(dna, target));
    EXPECT(isLinkedInStrand(dna));
    EXPECT_EQUAL(dna, expected);
    EXPECT_EQUAL(dna->value, 'A');
    EXPECT_EQUAL(dna->next, nullptr);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("Stress Test: Can spliceFirst tail of E.Coli (should take at most a few seconds).") {
    Nucleotide* dna = toStrand(eColiGenome());

    string tail = eColiGenome().substr(eColiGenome().size() - 80);
    Nucleotide* target = toStrand(tail);

    Nucleotide* originalDNA = dna;
    EXPECT(spliceFirst(dna, target));
    EXPECT(isLinkedInStrand(dna));

    /* We intentionally don't use EXPECT_EQUAL here, since otherwise if this test were
     * to fail we'd dump a huge string to the console.
     */
    EXPECT(fromDNA(dna) == eColiGenome().substr(0, eColiGenome().size() - tail.size()));

    EXPECT_EQUAL(dna, originalDNA);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("Stress Test: Can spliceFirst E.Coli from itself (should take at most a few seconds).") {
    Nucleotide* dna    = toStrand(eColiGenome());
    Nucleotide* target = toStrand(eColiGenome());

    EXPECT(spliceFirst(dna, target));
    EXPECT(isLinkedInStrand(dna));

    EXPECT_EQUAL(dna, nullptr);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}
