/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/src/thread.cpp                                                      #
# Project: /Users/leonexxe/code/JSIS-Engine/src                                                              #
# Created Date: Wednesday, September 7th 2022, 7:33:32 am                                                    #
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
    thread::thread(std::string name,env enviornment)
        :name(name){
            this->enviornment.push(enviornment);
        }

    void thread::execute(u64 entry,engine* e)
    {
        this->enviornment.top().pc = entry;
        e->execute(e->instructions,e,this);
    }
}