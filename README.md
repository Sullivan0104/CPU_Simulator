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

