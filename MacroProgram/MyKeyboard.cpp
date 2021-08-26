#include <iostream>
#include <Windows.h>
#include "Mykeyboard.h"

using namespace std;


    void MyKeyboard::keypress(){
        cout<<"\nrunning keypress code"<<endl;
    }

    void MyKeyboard::pressKey(){ //works with directx games
        SHORT key;
        UINT mappedkey;
        INPUT input = {0};
        key = VkKeyScan('w');
        mappedkey = MapVirtualKey(LOBYTE(key),0);
        input.type = INPUT_KEYBOARD;
        input.ki.dwFlags = KEYEVENTF_SCANCODE;
        input.ki.wScan = mappedkey;
        SendInput(1,&input, sizeof(input));
        Sleep(10);
        input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
        SendInput(1,&input, sizeof(input));
    }

    void MyKeyboard::anotherKeyPress(){ // another method of key press not working in games
        INPUT input = { 0 };
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = VkKeyScan('d');
        SendInput(1, &input, sizeof(input));
    }

   
    
