/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/src/env.cpp                                                         #
# Project: /Users/leonexxe/code/JSIS-Engine/src                                                              #
# Created Date: Wednesday, September 7th 2022, 7:33:49 am                                                    #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2022 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once

namespace JSIS::engine
{
    env::env()
    {
        this->sax.push(0);
        this->sbx.push(0);
        this->scx.push(0);
        this->sdx.push(0);
        this->sex.push(0);
        this->sfx.push(0);
        this->sgx.push(0);
        this->shx.push(0);
        this->error.push(0);
        this->ret.push(0);
        this->rv.push(0);
        this->_this.push(0);
        this->args.push(nullptr);
    }

    gEnv::gEnv()
    {
        this->gsax.push(0);
        this->gsbx.push(0);
        this->gscx.push(0);
        this->gsdx.push(0);
        this->gsex.push(0);
        this->gsfx.push(0);
        this->gsgx.push(0);
        this->gshx.push(0);
    }
}
