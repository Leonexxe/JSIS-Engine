/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/src/engine.cpp                                                      #
# Project: /Users/leonexxe/code/JSIS-Engine/src                                                              #
# Created Date: Wednesday, September 7th 2022, 7:31:48 am                                                    #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2022 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once

#include "engine.h"
#include <thread>
#include <cstdio>
namespace JSIS::engine
{
    engine::engine(){}

    engine::engine(std::string binary,interrupt* interrupts)
    {
        //initialize instructions
        u64 fileSize = 0;
        FILE * file = fopen(binary.c_str(), "r+");
        if (file == NULL)
        {
            std::cout << "error opening file: " << binary << std::endl;
            exit(-1);
        }
        fseek(file, 0, SEEK_END);
        fileSize = ftell(file);
        fclose(file);
        // Reading data to array of unsigned chars
        file = fopen(binary.c_str(), "r+");
        unsigned char * in = (unsigned char *)malloc(fileSize);
        int bytes_read = fread(in, sizeof(unsigned char), fileSize, file);
        fclose(file);

        this->iSize = fileSize/8;//number of 64 bit instructions
        this->instructions = (u64*)malloc(fileSize);
        memcpy(this->instructions,in,fileSize);

        //initialize interrupts
        if(interrupts != nullptr)
        {
            this->interrupts = interrupts;
            this->externalInterrupts = true;
        }
        else
        {
            //init to defaults
            this->interrupts = (interrupt*)malloc(sizeof(interrupt)*0xF);

            this->interrupts[0x0] = JSIS::engine::interrupts::int_0x0;
            this->interrupts[0x1] = JSIS::engine::interrupts::int_0x1;
            this->interrupts[0x2] = JSIS::engine::interrupts::int_0x2;
            this->interrupts[0x3] = nullptr;
            this->interrupts[0x4] = nullptr;
            this->interrupts[0x5] = nullptr;
            this->interrupts[0x6] = nullptr;
            this->interrupts[0x7] = nullptr;
            this->interrupts[0x8] = nullptr;
            this->interrupts[0x9] = nullptr;
            this->interrupts[0xA] = nullptr;
            this->interrupts[0xB] = nullptr;
            this->interrupts[0xC] = nullptr;
            this->interrupts[0xD] = nullptr;
            this->interrupts[0xE] = nullptr;
            this->interrupts[0xF] = nullptr;

            //setup env stack
            this->enviornment.push(gEnv());
        }
    }

    engine::~engine()
    {
        free(this->objects);
        //~this->__internal_threads;
        if(!this->externalInterrupts)
            free(this->interrupts);

        this->clean();
    }

    void engine::clean()
    {
        this->gFreeze = true;
        for(std::thread* I : this->__internal_dead_threads)
        {
            std::cout << "waiting on thread to close..." << std::endl;
            I->join();
            delete I;
        }
        this->__internal_dead_threads.clear();
        this->gFreeze = false;
    }

    bool engine::start(std::string name,u64 entry,env enviornment)
    {
        if(running)
            return 0;
        this->objects = (void**)malloc(0);
        this->startThread(name,entry,enviornment);
        return 1;
    }

    void threadStartHelper(thread* t,u64 entry,engine* e)
    {
        t->execute(entry,e);
    }

    u64 engine::startThread(std::string name,u64 entry,env enviornment)
    {
        this->gFreeze = true;
        thread t(name,enviornment);
        this->threads.push_back(t);
        std::thread* thr = new std::thread(threadStartHelper,&this->threads.back(),entry,this);
        this->threads.back().t = thr;
        u64 tid = threads.size()-1;
        this->rt++;
        this->gFreeze = false;
        return tid;
    }
}