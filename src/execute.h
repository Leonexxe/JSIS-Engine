/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/src/execute.h                                                       #
# Project: /Users/leonexxe/code/JSIS-Engine/src                                                              #
# Created Date: Wednesday, September 7th 2022, 7:31:21 pm                                                    #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2022 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#include "engine.h"

namespace JSIS::engine::execute
{
    void debug(u64* instructions,engine* e,thread* t);
    void exec(u64* instructions,engine* e,thread* t);
}