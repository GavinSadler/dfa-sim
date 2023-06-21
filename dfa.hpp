
// dfa - deterministic finite automata
// implements the functionality of a deterministic finite automata

#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>

using std::string;
using std::unordered_set;
using std::unordered_map;

// HINT: Use a map to implement the transfer function

class dfa
{
public:
    dfa(std::istream& input, bool debugText=false);

    bool step(char nextInput); // Steps through the machine given the input symbol
    bool isOnAcceptState(); // Returns true if current state is an accept state
    bool stepString(string input); // Runs the string through the machine and returns true if the machine landed on an accept state
    void reset(); // Resets the machine to its initial starting state
    bool isValidInput(char c); // Checks to see if the character c is a valid input to the machine
    void printDebugText(bool option); // Sets weather or not to print debug text
    
    friend std::ostream& operator<<(std::ostream& out, const dfa& machine);

private:
    // The following member both stores the machine's alphabet and each symbol's transistion function
    unordered_set<string> states;
    unordered_set<char> alphabet;
    unordered_map<string, unordered_map<char, string>> transitionFunction;
    string startState;
    unordered_set<string> acceptStates;

    // In simulating the machine, stores the current state
    string currentState;

    bool debugPrinting;

    // Returns true if the machine is a valid DFA, otherwise will return false
    bool verifyMachine();
};

