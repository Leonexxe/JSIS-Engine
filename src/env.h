/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/src/env.h                                                           #
# Project: /Users/leonexxe/code/JSIS-Engine/src                                                              #
# Created Date: Wednesday, September 7th 2022, 7:33:45 am                                                    #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2022 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#include "engine.h"

namespace JSIS::engine
{
    class env
    {
    public:
        env();
        //specific stacks
        std::stack<u64> ret;
        std::stack<u64> rv;
        std::stack<u64> _this;
        std::stack<u64> error;
        std::stack<u64*> args;
        
        //gp stacks
        std::stack<r64> sax;
        std::stack<r64> sbx;
        std::stack<r64> scx;
        std::stack<r64> sdx;
        std::stack<r64> sex;
        std::stack<r64> sfx;
        std::stack<r64> sgx;
        std::stack<r64> shx;

        //specific register
        r64 pc = 0;

        //gp registers
        r64 rax = 0;
        r64 rbx = 0;
        r64 rcx = 0;
        r64 rdx = 0;
        r64 rex = 0;
        r64 rfx = 0;
        r64 rgx = 0;
        r64 rhx = 0;
        r64 rix = 0;
        r64 rjx = 0;
        r64 rkx = 0;
        r64 rlx = 0;
        r64 rmx = 0;
        r64 rox = 0;
        r64 rpx = 0;
        r64 rqx = 0;

        //env values
        u64 EOO = 1000000;
        u64 AAS = 0;
    };

    class gEnv
    {
    public:
        gEnv();
        //global specific stacks
        std::stack<r64> error;
        //global gp stacks
        std::stack<r64> gsax;
        std::stack<r64> gsbx;
        std::stack<r64> gscx;
        std::stack<r64> gsdx;
        std::stack<r64> gsex;
        std::stack<r64> gsfx;
        std::stack<r64> gsgx;
        std::stack<r64> gshx;

        //global specific registers
        r64 oc = 0;
        //global gp registers
        r64 gax = 0;
        r64 gbx = 0;
        r64 gcx = 0;
        r64 gdx = 0;
        r64 gex = 0;
        r64 gfx = 0;
        r64 ggx = 0;
        r64 ghx = 0;
        r64 gix = 0;
        r64 gjx = 0;
        r64 gkx = 0;
        r64 glx = 0;
        r64 gmx = 0;
        r64 gox = 0;
        r64 gpx = 0;
        r64 gqx = 0;
    };
}