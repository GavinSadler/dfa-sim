The program that I engineered for this course emulates a deterministic finite automaton by simply implementing the mathematical definition for the DFA using tools provided by the C++ standard library.

The architecture of my simulator revolves around a DFA class that encapsulated the essential elements of a deterministic finite automaton. States were represented as a set of strings, allowing for flexible definition of DFAs with varying numbers of states. The alphabet is represented as a set of characters, accommodating different input symbols. The program supports an arbitrary number of states and alphabet sizes, allowing users to define and simulate any DFA. Additionally, as detailed in the course textbook, each DFA has some start state, and a set of accept states. The transition function was implemented using maps, and associates states and symbols with a corresponding next state. One final aspect of the DFA class that is not outlined in the textbook is the way the current state is stored, which I do using a member string which stores what the current state is.

In terms of program structure, the main driver was separated from the DFA functionality. The main driver is responsible for user interaction and instantiates a DFA object passing user-defined inputs in the form of .dfa files to the DFA object which parses the file and populates the object. The executable, by default named dfa-sim, follows the same functionality as outlined in the assignment instructions document. It’s functionality can be queried using ./dfa-sim -h.

Sample machines are provided, with a .dfa machine definition file, a .in sample input file, and a .out expected output sample. The program is written in C++ and supports both Windows and Linux. Building the program can be done via this command:

`~/dfa-sim-submission$ mkdir build && cd build && cmake ../ && cmake --build .`