# Zenom
Hard real-time HIL software.
* Zenom gives you an implementation file similar to Arduino that has blocks (like setup and loop).  After you write and compile your project, it will give you an executable. Open Zenom and select your compiled project. It will run your hard-real time task periodically and will plot the results using a Qt environmont.
* The hard-real time system is provided by PREEMPT-RT patched Linux.
* Only work on PC target (for now).
* HapticWand and Q8Driver include kernel and user space drivers for some devices.
* Written purely in C++
* The first version authors are Cuneyt Ay and Husnu Karakucuk.

