# Zenom
Hard real-time HIL software.
* A tutorial for how to install and use will be available in a few months.
* Zenom gives you an implementation file similar to Arduino that has blocks (like setup and loop). Fill the block with your real-time algorithm implementation and compile it. Open Zenom and select your compiled project. It will run your hard-real time task periodically and will plot the results using a Qt environmont.
* The hard-real time system is provided by PREEMPT-RT patched Linux.
* Only work on PC target (for now).
* HapticWand and Q8Driver include kernel and user space drivers for some devices.
* Written in C++
* The first version authors are Cuneyt Ay and Husnu Karakucuk.

