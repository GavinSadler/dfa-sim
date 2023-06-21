The program that I engineered for this course emulates a deterministic finite automaton by simply implementing the mathematical definition for the DFA using tools provided by the C++ standard library.

The architecture of my simulator revolves around a DFA class that encapsulated the essential elements of a deterministic finite automaton. States were represented as a set of strings, allowing for flexible definition of DFAs with varying numbers of states. The alphabet is represented as a set of characters, accommodating different input symbols. The program supports an arbitrary number of states and alphabet sizes, allowing users to define and simulate any DFA. Additionally, as detailed in the course textbook, each DFA has some start state, and a set of accept states. The transition function was implemented using maps, and associates states and symbols with a corresponding next state. One final aspect of the DFA class that is not outlined in the textbook is the way the current state is stored, which I do using a member string which stores what the current state is.

In terms of program structure, the main driver was separated from the DFA functionality. The main driver is responsible for user interaction and instantiates a DFA object passing user-defined inputs in the form of .dfa files to the DFA object which parses the file and populates the object. The executable, by default named dfa-sim, follows the same functionality as outlined in the assignment instructions document. It’s functionality can be queried using ./dfa-sim -h.

Sample machines are provided, with a .dfa machine definition file, a .in sample input file, and a .out expected output sample. The program is written in C++ and supports both Windows and Linux. Building the program can be done via this command:

`~/dfa-sim-submission$ mkdir build && cd build && cmake ../ && cmake --build .`

Ideas to improve:
- Set up CI/CD to automatically build when new changes are pushed/merged into master
- Set up CI/CD to automatically publish binaries on master
- Flesh out this README file
- Provide more input machines
- Support for NFAs
- Better support for different machine input types (json...)
- Decouple DFA and parsing logic
- DFA object should be able to verify if the machine is valid (all transitions accounted for)
- Implement a lenient mode allowing a machine to be described with just a certain set of transitions rather than a full description of states/alphabet etc.
- Better command line interfacing
- Optimize for larger, more complex machines
- Convert regex to a machine
- Interactive mode
- Proper user interface
- Either update getopt.c/h to come in as a separate library or properly attribute them
