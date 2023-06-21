
#include "dfa.hpp"

#include <iostream>
#include <sstream>

dfa::dfa(std::istream &input, bool debugText)
{
    // Example dfa definition file m1.dfa
    //  # DFA M1 from Page 36 of ITC Text;
    //  states: q1 q2 q3
    //  alphabet: 0 1
    //  startstate: q1
    //  finalstate: q2
    //  transition: q1 0 q1
    //  transition: q1 1 q2
    //  transition: q2 0 q3
    //  transition: q2 1 q2
    //  transition: q3 0 q2
    //  transition: q3 1 q2

    string nextLine;

    while (std::getline(input, nextLine))
    {
        // Store the next line from input into another stream. This makes for easy access
        std::stringstream nextLineStream(nextLine);
        string nextWord;

        nextLineStream >> nextWord;

        if (nextWord[0] == '#')
            // If the next word in the line starts with a #, we can ignore everything after it as it is a comment
            continue;
        else if (nextWord == "states:")
            while (nextLineStream >> nextWord)
                if (states.find(nextWord) != states.end())
                {
                    std::cerr << "Error: recieved a duplicated state, \"" << nextWord << "\"\n";
                    exit(1);
                }
                else
                    states.emplace(nextWord);
        else if (nextWord == "alphabet:")
            while (nextLineStream >> nextWord)
                if (nextWord.length() > 1)
                {
                    std::cerr << "Error: alphabet symbols should be single characters, recieved \"" << nextWord << "\"\n";
                    exit(1);
                }
                else if (alphabet.find(nextWord[0]) != alphabet.end())
                {
                    std::cerr << "Error: recieved duplicated alphabet symbol, \"" << nextWord[0] << "\"\n";
                    exit(1);
                }
                else
                    alphabet.emplace(nextWord[0]);
        else if (nextWord == "startstate:" && nextLineStream >> nextWord)
            if (startState.length() != 0)
            {
                std::cerr << "Error: start state already defined as \"" << startState << "\", but recieved \"" << nextWord << "\" as well\n";
                exit(1);
            }
            else
                startState = nextWord;
        else if (nextWord == "finalstate:" || nextWord == "acceptstates:")
            while (nextLineStream >> nextWord)
                if (acceptStates.find(nextWord) != acceptStates.end())
                {
                    std::cerr << "Error: recieved duplicated alphabet symbol, \"" << nextWord[0] << "\"\n";
                    exit(1);
                }
                else
                    acceptStates.emplace(nextWord);
        else if (nextWord == "transition:")
        {
            string startState, symbolTemp, endState;
            char symbol;

            nextLineStream >> startState >> symbolTemp >> endState;

            if (symbolTemp.length() > 1)
            {
                std::cerr << "Error: symbol for transition between \"" << startState << "\" and \"" << endState << " is more than 1 character, \"" << symbolTemp << "\"\n";
                exit(1);
            }

            symbol = symbolTemp[0];

            if (transitionFunction.find(startState) != transitionFunction.end())
            {
                transitionFunction.at(startState).emplace(symbol, endState);
            }
            else
            {
                unordered_map<char, string> transition({{symbol, endState}});

                transitionFunction.emplace(startState, transition);
            }
        }
    }

    // Set the machine to its initial state
    reset();

    debugPrinting = debugText;
}

bool dfa::step(char nextInput)
{
    if (!isValidInput(nextInput))
    {
        std::cout << "Input \"" << nextInput << "\" is not a valid symbol in the input machine's alphabet, ignoring the rest of the input\n";
        return false;
    }

    string nextState;

    // If there is no defined transitions for the current state or the current input,
    // assume that this is just a self loop and stay at the current state
    if (transitionFunction.find(currentState) == transitionFunction.end() ||
        transitionFunction.at(currentState).find(nextInput) == transitionFunction.at(currentState).end())
    {
        if (debugPrinting)
            std::cout << "Warning: no transition found for state \"" << currentState << "\" and symbol '" << nextInput << "', assuming self loop\n";
        nextState = currentState;
    }
    else
        nextState = transitionFunction.at(currentState).at(nextInput);

    if (debugPrinting)
        std::cout << "Current state: " << currentState << " Symbol: " << nextInput << " -> New State: " << nextState << "\n";

    currentState = nextState;

    return true;
}

bool dfa::isOnAcceptState()
{
    return acceptStates.count(currentState);
}

bool dfa::stepString(string input)
{
    for (auto &symbol : input)
        if (!step(symbol))
            return false;

    return isOnAcceptState();
}

void dfa::reset()
{
    currentState = startState;
}

bool dfa::isValidInput(char c)
{
    return alphabet.find(c) != alphabet.end();
}

void dfa::printDebugText(bool option)
{
    debugPrinting = option;
}

std::ostream &operator<<(std::ostream &out, const dfa &machine)
{
    out << "States:\n  ";

    for (const auto &state : machine.states)
        out << state << " ";

    out << "\nAlphabet:\n  ";

    for (const auto &symbol : machine.alphabet)
        out << symbol << " ";

    out << "\nStart state:\n  " << machine.startState
        << "\nAccept states:\n  ";

    for (const auto &state : machine.acceptStates)
        out << state << " ";

    out << "\nTransitions:\n";

    for (const auto &statePair : machine.transitionFunction)
        for (const auto &transition : statePair.second)
            out << "  " << statePair.first << " " << transition.first << " " << transition.second << "\n";

    return out;
}
