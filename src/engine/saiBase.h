////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _BASE_H
#define _BASE_H

#include <stdio.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <dirent.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_rwops.h>


//loads a textfile into a vector
std::vector<std::string> loadTextfile(std::string fname);

//gets the names of all files in a directory
std::vector<std::string> getFilesFromDir(std::string dirname);

std::string getParam(std::string p_string);

#endif // _BASE_H
