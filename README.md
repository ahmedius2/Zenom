# Zenom
Real-time HIL software.
* More information and tutorial on how to install is available at GitHub Wiki page.
* Zenom lets users to implement real-time programs with a programming model similar to Arduino (that has blocks like setup and loop). The user fills the blocks (initialize, setup, loop, stop, terminate) with C++ to implement a periodic algorithm with start and ending hooks and define the data that will be logged and manipulated during execution. Zenom opens the executable generated from user program and run it periodically while ploting the results using a Qt environmont.
* Zenom delivers real-time on Linux with PREEMPT-RT patch. It can also be compiled and run on the regular Linux systems without real-time guarantees.
* Only works for PC target (for now).
* HapticWand and Q8Driver include kernel and user space drivers for some devices.
* Written in C++.
* The first version ( with Xenomai ) authors are Cuneyt Ay and Husnu Karakucuk.

## Target

Zenom can communicate with external hardware via serial port. Currently a data
aqusition board that also developed in GTU can be used with Zenom. 
