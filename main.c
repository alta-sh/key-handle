#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _BOOL_DEF_
    #define _BOOL_DEF_
    typedef int bool;
    #define false 0
    #define true 1
#endif

void renderMenu() { 
    puts("[ Key-Handle ] - By alta\n"
         "-------------------------------------------------------------------------------------\n"
         "Key-Handle is a simple key capturing program that runs as a process in the background\n"
         "and writes the keystrokes to a textfile in the directory the program was ran\n"
         "DISCLAIMER: alta is not responsible for any malicious use of this software,\n"
         "            it was made for educational purposes only.\n"
         "-------------------------------------------------------------------------------------\n"
         "1) Start capturing\n"
         "2) Configure write directory\n");

    getchar();
}

int main(int argc, char* argv[]) {
    HWND window;
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", NULL);

    bool showMenu = true;

    while(1) {

        if(showMenu) { renderMenu(); }

        //close program when Esc pressed
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }
    }
    
    return EXIT_SUCCESS;
}