
// dfa-sim
// Gavin Sadler
// May 23rd, 2023
// Foundations of Computer Science

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include "getopt.h"
#endif

#include "dfa.hpp"

using std::cout;
using std::string;

// Contains information about the input paramters
struct input_params
{
    string dfa_filename;
    bool verbose = false;
};

input_params parse_input_params(int argc, char *argv[]); // Grabs input parameters
void exit_usage();                                       // Prints out usage information and exits the program
void exit_help();                                        // Prints out help information and exits the program

int main(int argc, char *argv[])
{
    input_params p(parse_input_params(argc, argv));

    // p.verbose = true;

    std::ifstream inputFile(p.dfa_filename, std::ios::in);

    dfa machine(inputFile, p.verbose);

    if (p.verbose)
        cout << "---BEGIN DFA definition---\n"
             << machine << "---END DFA definition---\n\n";

    std::string nextLine;

    while (std::getline(std::cin, nextLine))
    {
        nextLine = nextLine.erase(nextLine.find_last_not_of(' ') + 1); // Remove trailing whitespace
        bool output = machine.stepString(nextLine);
        std::cout << nextLine << " --> " << (output ? "ACCEPT" : "NOT ACCEPT") << "\n";
        machine.reset();
    }

    return 0;
}

input_params parse_input_params(int argc, char *argv[])
{
    input_params p;
    char c;

    // Iterate through the different input parameter options
    while ((c = getopt(argc, argv, "hvd:")) != -1)
    {
        switch (c)
        {
        case 'h':
            exit_help();
            break;
        case 'v':
            p.verbose = true;
            break;
        case 'd':
            p.dfa_filename = string(optarg);
            break;
        case '?':
            exit_usage();
            break;
        }
    }

    // We must have recieved a filename to try to process, otherwise how would we run our DFA?
    if (p.dfa_filename.empty())
        exit_usage();

    return p;
}

void exit_usage()
{
    cout << "Usage: program [-v] [-h] -d <filename>\n";
    exit(EXIT_FAILURE);
}

void exit_help()
{
    // TODO: Flesh out help message
    const string help_message =
        "dfa-sim: A command-line tool that simulates deterministic finite automata.\n"
        "\n"
        "Usage: dfa-sim [-v] [-h] -d <filename>\n"
        "\n"
        "Options:\n"
        "  -v            Enable verbose output.\n"
        "  -h            Show this help message and exit.\n"
        "  -d <filename> Specify the filename of the DFA to simulate. The filename typically ends with .dfa.\n"
        "\n"
        "Input:\n"
        "  The input for the simulation is read from the standard input using the < command line operation. The input should consist of a string of symbols that belong to the alphabet of the DFA.\n"
        "\n"
        "Examples:\n"
        "  dfa-sim -d example.dfa < input.txt    Simulate the DFA defined in example.dfa with the input string from input.txt.\n"
        "  dfa-sim -v -d example.dfa < input.txt Simulate the DFA defined in example.dfa with the input string from input.txt and show verbose output.\n"
        "  dfa-sim -h                            Show this help message and exit.\n";

    cout << help_message;

    exit(EXIT_SUCCESS);
}