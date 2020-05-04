#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _BOOL_DEF_
    #define _BOOL_DEF_
    typedef int bool;
    #define false 0
    #define true 1
#endif

void renderMenu(); // function prototype

void clear() {
    system("cls");
}

void handleDirectory() {
    clear();
    puts("\nThis is still under construction...\n\nPress enter to return to the menu.");
    getchar();
    renderMenu();
}

void renderMenu() { 
    size_t input = 0;
    while(input != 1 || input != 2) {
        clear();
        printf("\n[ Key-Handle ] - By alta\n"
         "-------------------------------------------------------------------------------------\n"
         "Key-Handle is a simple key capturing program that runs as a process in the background\n"
         "and writes the keystrokes to a textfile in the directory the program was ran\n"
         "DISCLAIMER: alta is not responsible for any malicious use of this software,\n"
         "            it was made for educational purposes only.\n"
         "-------------------------------------------------------------------------------------\n\n"
         "1) Start capturing\n"
         "2) Configure write directory\n\n"
         "Input>%c", ' ');
        scanf("%d", input);

        if(input == 2) { handleDirectory(); }
    } 
    // If input == 1 we return to main.
}

int main(int argc, char* argv[]) {
    HWND window;
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", NULL);

    bool showMenu = true;

    while(1) {

        if(showMenu) { renderMenu(); }
        showMenu = false;
        
        ShowWindow(window,0);
        //close program when Esc pressed
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }
    }
    
    return EXIT_SUCCESS;
}