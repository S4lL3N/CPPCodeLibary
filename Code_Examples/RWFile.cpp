#include <iostream>
#include <windows.h>
#include "RWFile.h"
#include <fstream>


void RWFile::createAndWrite()
{
    //opens file and writes to it but this will overwrite the file.
    std::ofstream myFile;
    myFile.open("Example.txt");
    myFile << "Writing this to file.\n";
    myFile.close();

  // Create and open a text file
  //std::ofstream MyFile("filename.txt");

  // Write to the file
  //MyFile << "Files can be tricky, but it is fun enough!";

  // Close the file
  //MyFile.close();

}

void RWFile::readFrom()
{
    std::string line;
    std::ifstream myfile ("Example.txt");
        if (myfile.is_open())
        {
            while ( getline (myfile,line) )
            {
                std::cout << line << '\n';
            }
            myfile.close();
        }

        else std::cout << "Unable to open file";
}

void RWFile::writeAppend()
{
    //this will open file and append to the file (not overwirte it).
    std::ofstream myFileA;
    myFileA.open("Example.txt", std::fstream::app);
    myFileA << "This will append to the file.";
    myFileA.close();
    
}