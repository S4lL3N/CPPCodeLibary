#include <iostream>
#include <windows.h>

#include "VectorsEx.h"
#include "CleanUp.h"
#include "RWFile.h"



main(){
    std::cout<<"\n\t\t\t\tWelcome to Shae's C++ Code Examples!";
    std::cout<<"\n\n***Use Numpad to make selection.***"<<std::endl;

    std::cout<<"\n\n\t\t1. Vectors";
    std::cout<<"\n\n\t\t2. Create and write to file";
    std::cout<<"\n\n\t\t3. Read from file.";
    std::cout<<"\n\n\t\t4.";
    std::cout<<"\n\n\t\t5.";
    std::cout<<"\n\n\t\t6.";
    std::cout<<"\n\n\t\t7.";
    std::cout<<"\n\n\t\t8.";
    std::cout<<"\n\n\t\t9.";

    std::cout<<"\n\n\n\nPress the Escape(ESC) key to EXIT.\n";

    VectorsEx V_Ex;
    CleanUp clean;
    RWFile file;

    while(true){
        if(GetAsyncKeyState(VK_ESCAPE)){
            return 0;
        }
        if(GetAsyncKeyState(VK_NUMPAD1)){
            Sleep(1000);
            std::cout<<"Loading Vector Examples...\n\n";
            V_Ex.loadVector();
            main();
        }
        if(GetAsyncKeyState(VK_NUMPAD2)){
            Sleep(1000);
            std::cout<<"Loading Create and write file...";
            file.createAndWrite();
            main();
        }
        if(GetAsyncKeyState(VK_NUMPAD3)){
            Sleep(1000);
            std::cout <<"Loading Read from file.";
            file.readFrom();
            main();

        }
        if(GetAsyncKeyState(VK_NUMPAD4)){
            Sleep(1000);

        }
        if(GetAsyncKeyState(VK_NUMPAD5)){
            Sleep(1000);

        }
        if(GetAsyncKeyState(VK_NUMPAD6)){
            Sleep(1000);

        }
        if(GetAsyncKeyState(VK_NUMPAD7)){
            Sleep(1000);

        }
        if(GetAsyncKeyState(VK_NUMPAD8)){
            Sleep(1000);

        }
        if(GetAsyncKeyState(VK_NUMPAD9)){
            Sleep(1000);

        }  
        if(GetAsyncKeyState(VK_SUBTRACT)){
            Sleep(1000);
            std::cout<<"Cleaning Console...";
            clean.clear();
            main();
        }
    }
}//to compile:  g++ main.cpp vectorsEx.cpp CleanUp.cpp RWFile.cpp -std=c++11 -o Code_Examples