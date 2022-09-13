/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/src/thread.h                                                        #
# Project: /Users/leonexxe/code/JSIS-Engine/src                                                              #
# Created Date: Wednesday, September 7th 2022, 7:33:29 am                                                    #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2022 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once

namespace JSIS::engine
{
    class thread
    {
    public:
        std::stack<env> enviornment;
        std::string name;
        std::thread* t;

        thread(std::string name,env enviornment);

        void execute(u64 entry,engine* e);
    };
}