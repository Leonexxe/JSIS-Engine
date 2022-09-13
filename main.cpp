/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/main.cpp                                                            #
# Project: /Users/leonexxe/code/JSIS-Engine                                                                  #
# Created Date: Wednesday, September 7th 2022, 7:53:54 pm                                                    #
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
#include <chrono>
#include <fstream>

using namespace JSIS::engine;

bool quit = 0;
void sigHandler(int sig)
{
    quit = 1;
}

void error(u64 errorCode,std::string& msg,engine* e,thread* t)
{
    std::cout << msg << std::endl;
}

engine e("./bin/out",nullptr);

std::vector<u64> times;

void exec()
{
    u64 t = e.start("main",0,env());
    while(!quit&&e.rt != 0);
    //e.quit = true;
    e.running = false;
    e.clean();
}

int main(int argc,char** argv)
{
    for(int I = 0;I<64;I++)
        signal(I,&sigHandler);
    std::cout << "executing JSIS engine..." << std::endl;
    if(argc < 2)
        goto skipFlags;
    if(std::string(argv[1]) == "-debug")
    {
        e.execute = JSIS::engine::execute::debug;
    }
    else
    {
        e.execute = JSIS::engine::execute::execute;
    }
    goto completeFlags;
    skipFlags: ;
    e.execute = JSIS::engine::execute::execute;
    completeFlags: ;
    e.error = error;

    int runs = 100;
    for(int I = 0;I<runs;I++)
    {
        std::cout <<std::endl<< "starting new run..." << std::endl;
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        exec();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() <<"[ns]"<< std::endl<<std::endl;
        times.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count());
    }
    //calculate average time
    u64 dTotal = 0;
    for(u64 I : times)
        dTotal+=I;
    auto total = std::chrono::nanoseconds(dTotal);
    dTotal/=runs;
    auto avg = std::chrono::nanoseconds(dTotal);

    std::ofstream out("/users/leonexxe/code/JSIS-engine/compare/JSIS.txt");

    out << "JSIS:" << std::endl;
    out << "total time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(total).count() << "[s]" << std::endl
        << std::chrono::duration_cast<std::chrono::milliseconds>(total).count() << "[ms]" << std::endl
        << std::chrono::duration_cast<std::chrono::microseconds>(total).count() << "[µs]" << std::endl
        << std::chrono::duration_cast<std::chrono::nanoseconds> (total).count() << "[ns]" << std::endl;

    out << "average time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(avg).count() << "[s]" << std::endl
        << std::chrono::duration_cast<std::chrono::milliseconds>(avg).count() << "[ms]" << std::endl
        << std::chrono::duration_cast<std::chrono::microseconds>(avg).count() << "[µs]" << std::endl
        << std::chrono::duration_cast<std::chrono::nanoseconds> (avg).count() << "[ns]" << std::endl;   

    out.close();
}