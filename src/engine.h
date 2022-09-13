/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/src/engine.h                                                        #
# Project: /Users/leonexxe/code/JSIS-Engine/src                                                              #
# Created Date: Wednesday, September 7th 2022, 7:32:01 am                                                    #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2022 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "fixedInt.h"
namespace JSIS::engine
{
    class engine;
    class thread;
    #define JSIS_ENGINE_INT_ARGS u64* instructions,JSIS::engine::engine* e,JSIS::engine::thread* t
    typedef void (*interrupt)(u64*,JSIS::engine::engine*,JSIS::engine::thread*);
}
#include "lang.h"
#include "env.h"
#include "thread.h"
#include "interrupts.h"
#include "execute.h"

namespace JSIS::engine
{

    class engine
    {
    protected:

    public:
        std::vector<thread> threads;
        bool running = false;
        bool gFreeze = false;
        bool quit = false;
        bool externalInterrupts = 0;
        void** objects;
        std::vector<std::thread*> __internal_dead_threads;
        std::ostream* out = &std::cout;
        interrupt* interrupts;
        u64 iSize = 0;
        u64 rt = 0;
        u64* instructions;
        std::stack<gEnv> enviornment;

        engine();
        ~engine();
        engine(std::string binary,interrupt* interrupts);
        
        bool start(std::string name,u64 entry,env enviornment);
        void clean();
        u64 startThread(std::string name,u64 entry,env enviornment);

        void(*execute)(u64* instructions,engine* e,thread* t);
        void(*error)(u64 errorCode,std::string& errorMSG,engine* e,thread* t);
    };
}
