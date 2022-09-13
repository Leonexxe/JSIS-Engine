/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/src/interrupts.cpp                                                  #
# Project: /Users/leonexxe/code/JSIS-Engine/src                                                              #
# Created Date: Friday, September 9th 2022, 12:31:04 am                                                      #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2022 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#include "engine.h"

namespace JSIS::engine::interrupts
{
    void int_0x0(JSIS_ENGINE_INT_ARGS)
    {
        char c = t->enviornment.top().rax;
        *(e->out) << (u8)c;
    }

    void int_0x1(JSIS_ENGINE_INT_ARGS)
    {
        char* str = (char*)(e->objects[t->enviornment.top().rax]);
        *(e->out) << str;
    }

    void int_0x2(JSIS_ENGINE_INT_ARGS)
    {
        t->enviornment.top().rax = 1;
    }
}