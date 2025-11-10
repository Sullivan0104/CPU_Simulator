# Contributors
<pre>
Timothy Sullivan
Bobby Lin
</pre>
# Project Layout
<pre> 
.
├── makefile
├── README.md
├── src
│   ├── controller
│   │   ├── controller.cpp
│   │   └── controller.hpp
│   ├── main.cpp
│   ├── model
│   │   ├── alu.cpp
│   │   ├── alu.hpp
│   │   ├── cpuModel.cpp
│   │   ├── cpuModel.hpp
│   │   ├── memory.cpp
│   │   ├── memory.hpp
│   │   ├── registers.cpp
│   │   ├── registers.hpp
│   │   └── subject.hpp
│   └── view
│       ├── textView.cpp
│       └── textView.hpp
└── test
    └── input.dat

6 directories, 17 files
</pre>
# How to Build and Run
Complies the program. Creates cpu_sim in root directory.
<pre>
make all
</pre>
To run:
<pre>
./cpu_sim input.dat run|step
</pre>
# Cleaning
Removes object files (.o) and the executable (cpu_sim). 
<pre>
make clean
</pre>


Summary

Our project simulates the basic functionality of a simple CPU following the 
principles of a MVC (model, view, controller) with a object oriented design 
pattern for the system. The simulator executes small sets of assembly 
instructions and operates with the fetch-decode-execute cycle, including 
handling instructions, utilizing registers, memory operations, and arithmetic 
computation.

Our model layer covers the CPU components involved, including the cpuModel, 
memory, and registers classes.

Our view layer is implemented by the textView class, enabling viewers to view 
updates and results on a scoreboard as the program progresses.

Our controller layer manages different grandularities of runtime, in which it 
can run the entire program but we also have a mode to go "single-step" that 
does one at a time.

The program can read a .bin or .dat file produced by our Project 1 MIPS 
assembler and will print a scoreboard view of the contents of the PC, 
registers, and memory contents after every cycle.

It supports the following instructions:

load — Loads a value from memory into a register

store — Stores a register value into memory

add — adds two registers and stores the result in a destination register

sub — subtracts one register from another

addi — adds an immediate value to a register

and, or, slt — basic logical and comparison operations for value checking


Our formatting was seperated into multiple different classes for clarity 
purposes, separation of concerns and functions.

Our ALU class exemplifies this, as we seperate the computation it provides away 
from the instructions in cpuModel. It performs the operation it is told, 
returns it, and nothing more. Should any further testing need to be done, 
seperating these tasks enables a cleaner experience for later viewing and 
changes.

Our cpuModel class is used to manage registers, oversee the program counter,
instruction count, and the overall execution loop. The program counter is 
incremented in 4s specifically for our MIPS instructions. Immediate values are 
noted as signed integers to allow our addi operations to use them effectively. 
Halt messages are placed in order to catch any extraneous memory or instruction 
anomalies. Step() assists in this endeavor, allowing each instruction be 
executed per call to better hone in on actions taken and necessary halts should 
they occur. Careful use of signed and unsigned values helps in reducing any 
errors occuring from conflating unsigned memory addressed from the signed 
operations.

Our memory class is made to wrap around a memory array and enables the read and 
write functions. We utilized bounds checking in order to ensure we do not 
access space outside of bounds, utilized when reading and writing to prevent 
overflows that may halt our system. Big-Endian is preserved from the first 
project that this builds on.

The registers class is made with 32-bit signed integers to match MIPS 
specifications, registers initialized to zero with register 0 hardwired to stay 
zero. This is common procedure and serves to simplify many instructions, such 
as when the value of zero is necessary for an operation.

The textview class is made to display the output to us viewers- an observer 
that reacts to changes it is given and then processed into a viewable feed, in 
this case, a "scoreboard" for the viewer. As specified, it shows us the results 
of the tracked number of operations and cycles, as well as the contents of PC,
registers, and memory.

Lastly, our controller class is made to manage the program's different 
granularities of runtime, with 2 provided options of either running it all or 
in stepmode, which is guided by the user's input to control its pace.