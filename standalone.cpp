/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/standalone.cpp                                                      #
# Project: /Users/leonexxe/code/JSIS-Engine                                                                  #
# Created Date: Tuesday, September 13th 2022, 7:44:24 pm                                                     #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2022 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#include "src/engine.h"
#include "src/env.cpp"
#include "src/interrupts.cpp"
#include "src/execute.cpp"
#include "src/thread.cpp"
#include "src/engine.cpp"
#include <csignal>

using namespace JSIS::engine;

bool quit = 0;
void sigHandler(int sig)
{
    quit = 1;
}

bool f_Debug = false;
std::string inputFile = "";

i64 parseFlags(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "error: not enough arguments to run the JSIS compiler!" << std::endl;
        return -1;
    }

    for(int I = 1;I<argc;I++)
    {
        if(argv[I][0] == '-')
        {
            if(argv[I][1] == 'D')
                f_Debug = true;
        }
        else
        {
            inputFile = argv[I];
        }
    }
    return 0;
}

void error(u64 errorCode,std::string& msg,engine* e,thread* t)
{
    std::cout << msg << std::endl;
}

int main(int argc,char** argv)
{
    for(int I = 0;I<64;I++)
        signal(I,&sigHandler);
    std::cout << "executing JSIS engine..." << std::endl;
    parseFlags(argc,argv);
    engine e(inputFile,nullptr);
    if(argc < 2)
        goto skipFlags;
    if(f_Debug)
        e.execute = JSIS::engine::execute::debug;
    else
        e.execute = JSIS::engine::execute::execute;
    goto completeFlags;
    skipFlags: ;
    e.execute = JSIS::engine::execute::execute;
    completeFlags: ;
    e.error = error;

    u64 t = e.start("main",0,env());
    while(!quit&&e.rt != 0);
    e.quit = true;
    e.clean();
}