Key-Handle
==========
### A hidden keyboard-input monitoring application for Windows.

This program uses a Win32API global (system-wide) hook to capture all keyboard input regardless of the active window, it will then process/format the input prior to writing it to a log.txt file in the directory the program was run. **I wont be held responsible for any malicious modification of this program/code provided. This was just a fun hobbyist project for educational purposes in an effort to familiarise myself more with the Win32API and hooking in general.**

### Example of typing on different windows with key-handle running in background:
![google](https://i.imgur.com/R9zgWV1.png)
![discord](https://i.imgur.com/CKBF8Ev.png)
### When the user presses F9 to close the program and create a log.txt file.
![log.txt](https://i.imgur.com/cg13bE5.png)
