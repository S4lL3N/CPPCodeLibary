#include <iostream>
#include <windows.h>
#include "MyMouse.h"
using namespace std;

    void MyMouse::getMousePOS(){
        cout<<"\nGetting Mouse Location...";
        HWND  hWND;
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(hWND, &p);
        cout << "\nX-Pos: " << p.x << " | Y-Pos: " << p.y <<endl;
    }

    void MyMouse::setMousePOS(){
        cout<<"\nSetting mouse location...";

        cout<<"\nSetting mouse position to (350,350)"<<endl;

        int x = 1422;
        int y = 10;
 
        // Get total screen coordinates
        int screen_x = GetSystemMetrics(SM_CXSCREEN);
        int screen_y = GetSystemMetrics(SM_CYSCREEN);
 
        WINDOWPLACEMENT wp;
        //GetWindowPlacement(hWND, &wp);
            
        long xConverted = (65535 * (x + wp.rcNormalPosition.left)) / screen_x;
        long yConverted = (65535 * (y + wp.rcNormalPosition.top)) / screen_y;
 
        INPUT iNPUT = { 0 };
        iNPUT.type = INPUT_MOUSE;
        iNPUT.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
        iNPUT.mi.dx = xConverted;
        iNPUT.mi.dy = yConverted;
        SendInput(1, &iNPUT, sizeof(iNPUT));
    }

    void MyMouse::inputMousePOS(int x,int y){

        cout<<"\nSetting mouse position to: " << x <<","<< y <<endl;
 
        // Get total screen coordinates
        int screen_x = GetSystemMetrics(SM_CXSCREEN);
        int screen_y = GetSystemMetrics(SM_CYSCREEN);
 
        WINDOWPLACEMENT wp;
        //GetWindowPlacement(hWND, &wp);
            
        long xConverted = (65535 * (x + wp.rcNormalPosition.left)) / screen_x;
        long yConverted = (65535 * (y + wp.rcNormalPosition.top)) / screen_y;
 
        INPUT iNPUT = { 0 };
        iNPUT.type = INPUT_MOUSE;
        iNPUT.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
        iNPUT.mi.dx = xConverted;
        iNPUT.mi.dy = yConverted;
        SendInput(1, &iNPUT, sizeof(iNPUT));

    }