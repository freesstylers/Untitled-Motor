// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Entity.h"

#include <stdio.h>
#include <OgreRoot.h>
#include <SDL.h>

#ifdef  _DEBUG
    int main(int argc, char* argv[])
#else
    #include <Windows.h>
    int WINAPI
    WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
    Ogre::Root* root;

#ifdef  _DEBUG
    root = new Ogre::Root("plugins_d.cfg");
#else
    root = new Ogre::Root("plugins.cfg");
#endif



    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file