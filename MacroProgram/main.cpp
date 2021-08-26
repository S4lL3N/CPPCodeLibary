#include <iostream>
#include <Windows.h>
#include "Mykeyboard.h"
#include "MyMouse.h"

using namespace std;



main(){
    cout<<"\t\tWelcome to my Macro program!"<<endl;

    cout<<"\n\nUse Numpad to make selection.";
    cout<<"\n\n\t1. DirectX Simulate keyboard key press 'w'.";
    cout<<"\n\t2. old method of simulating key press 'd'.";
    cout<<"\n\t3. Get Mouse Position.";
    cout<<"\n\t4. Set Mouse Position.";
    cout<<"\n\n\t0. Exit Program.";


    MyKeyboard kb;
    MyMouse mo;

    while(true){

        if(GetAsyncKeyState(VK_NUMPAD0)){
            return 0;
        }
        if(GetAsyncKeyState(VK_NUMPAD1)){
            Sleep(1000); //to limit button presses
            kb.keypress();
            kb.pressKey();
            kb.anotherKeyPress();
        }
        if(GetAsyncKeyState(VK_NUMPAD3)){
            Sleep(1000);
            mo.getMousePOS();

        }
        if(GetAsyncKeyState(VK_NUMPAD4)){
            Sleep(1000);
            mo.setMousePOS();

        }
        if(GetAsyncKeyState(VK_NUMPAD5)){
            Sleep(1000);
            cout<<"\n\nEnter the cords to move mouse to seperated by spaces:";
            int x, y;
            cin>> x >> y;
            mo.inputMousePOS(x,y);
        }
    }

}// to compile:  g++ main.cpp MyKeyboard.cpp MyMouse.cpp -o MacroProgram