#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <winbase.h> //libloaderapi.h


void get_proc_id(const char* window_title, DWORD &process_id)
{
    GetWindowThreadProcessId(FindWindow(NULL, window_title),&process_id);
}

void error(const char* error_title,const char* error_message)
{
    MessageBox(0, error_message, error_title, 0);
    exit(-1);

}

bool check_for_DLL(string file_name)
{
    struct stat buffer;
    return (stat(file_name.c_str(), &buffer) == 0);
}

main(){

}