/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/src/execute.cpp                                                     #
# Project: /Users/leonexxe/code/JSIS-Engine/src                                                              #
# Created Date: Wednesday, September 7th 2022, 7:31:25 pm                                                    #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2022 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#include "engine.h"
#include <cmath>
#include <thread>

namespace JSIS::engine::execute
{
    void error(u64* instructions,engine* e,thread* t,std::string msg,u64 errorCode)
    {
        r64* I = &t->enviornment.top().pc;
        e->error(errorCode,msg,e,t);
        t->enviornment.top().ret.push(*I+1);
        *I=t->enviornment.top().error.top();
    }

    namespace _error
    {
        u64 INVALID_STACK = 1;
        u64 INVALID_INTERRUPT = 2;
        u64 INVALID_INSTRUCTION = 3;
    }

    std::string getStackName(u64 r)
    {
        switch(r)
        {
            // specific stacks
            case(0x0): return "ret";
            case(0x1): return "rv";
            case(0x2): return "this";
            case(0x3): return "error";
            // gp stacks
            case(0x10): return "sax";
            case(0x11): return "sbx";
            case(0x12): return "scx";
            case(0x13): return "sdx";
            case(0x14): return "sex";
            case(0x15): return "sfx";
            case(0x16): return "sgx";
            case(0x17): return "shx";
            // global gp stacks
            case(0x18): return "gsax";
            case(0x19): return "gsbx";
            case(0x1A): return "gscx";
            case(0x1B): return "gsdx";
            case(0x1C): return "gsex";
            case(0x1D): return "gsfx";
            case(0x1E): return "gsgx";
            case(0x1F): return "gshx";
        }
        return "";
    }
    std::string getRegName(u64 r)
    {
        switch(r)
        {
            //local specific registers
            case(0x0): return "pc";
            case(0x1): return "oc";
            //local gp registers
            case(0x10): return "rax";
            case(0x11): return "rbx";
            case(0x12): return "rcx";
            case(0x13): return "rdx";
            case(0x14): return "rex";
            case(0x15): return "rfx";
            case(0x16): return "rgx";
            case(0x17): return "rhx";
            case(0x18): return "rix";
            case(0x19): return "rjx";
            case(0x1A): return "rkx";
            case(0x1B): return "rlx";
            case(0x1C): return "rmx";
            case(0x1D): return "rox";
            case(0x1E): return "rpx";
            case(0x1F): return "rqx";
            //global gp registers
            case(0x20): return "gax";
            case(0x21): return "gbx";
            case(0x22): return "gcx";
            case(0x23): return "gdx";
            case(0x24): return "gex";
            case(0x25): return "gfx";
            case(0x26): return "ggx";
            case(0x27): return "ghx";
            case(0x28): return "gix";
            case(0x29): return "gjx";
            case(0x2A): return "gkx";
            case(0x2B): return "glx";
            case(0x2C): return "gmx";
            case(0x2D): return "gox";
            case(0x2E): return "gpx";
            case(0x2F): return "gqx";
        }
        return "";
    }

    void debugPrintInstr(u64* instructions,engine* e,thread* t)
    {
        r64* I = &t->enviornment.top().pc;
        switch(instructions[*I])
        {
            case(ASS_WRITE):
                std::cout << "write " << instructions[*I+1] << instructions[*I+2] << std::endl;
                break;
            case(ASS_VJMP):
                std::cout << "vjmp " << instructions[*I+1] << std::endl;
                break;
            case(ASS_JMP):
                std::cout << "jmp " << instructions[*I+1] << std::endl;
                break;
            case(ASS_RET):
                std::cout << "return" << std::endl;
                break;
            case(ASS_RESET):
                std::cout << "reset" << std::endl;
                break;
            case(ASS_PUSHE):
                std::cout << "pushe" << std::endl;
                break;
            case(ASS_PUSHA):
                std::cout << "pusha" << std::endl;
                break;
            case(ASS_PUSH):
                std::cout << "push " << instructions[*I+1] <<" "<< instructions[*I+2] << std::endl;
                break;
            case(ASS_POPE):
                std::cout << "pope" << std::endl;
                break;
            case(ASS_POPA):
                std::cout << "popa" << std::endl;
                break;
            case(ASS_POP):
                std::cout << "pop " << instructions[*I+1] << std::endl;
                break;
            case(ASS_MOV):
                std::cout << "mov " << instructions[*I+1] <<" "<< instructions[*I+2] << std::endl;
                break;
            case(ASS_MALLOC):
                std::cout << "malloc " << instructions[*I+1] <<" "<< instructions[*I+2] << std::endl;
                break;
            case(ASS_INT):
                std::cout << "int " << instructions[*I+1] <<" "<< std::endl;
                break;
            case(ASS_HLT):
                std::cout << "hlt" << std::endl;
                break;
            case(ASS_FREE):
                std::cout << "free " << instructions[*I+1] << std::endl;
                break;
            case(ASS_EWRITE):
                std::cout << "ewrite " << instructions[*I+1] <<" "<< instructions[*I+2] << std::endl;
                break;
            case(ASS_EMOV):
                std::cout << "emov " << instructions[*I+1] <<" "<< instructions[*I+2] << std::endl;
                break;
            case(ASS_CALL):
                std::cout << "call " << instructions[*I+1] << std::endl;
                break;
            case(ASS_AWRITE):
                std::cout << "awrite " << instructions[*I+1] <<" "<< instructions[*I+2] <<" "<< instructions[*I+3] << std::endl;
                break;
            case(ASS_ALWRITE):
                std::cout << "alwrite " << instructions[*I+1] <<" "<< instructions[*I+2] <<" "<< instructions[*I+3] << std::endl;
                break;
            case(ASS_AEWRITE):
                std::cout << "aewrite " << instructions[*I+1] <<" "<< instructions[*I+2] <<" "<< instructions[*I+3] << std::endl;
                break;
            case(ASS_AELWRITE):
                std::cout << "aelwrite " << instructions[*I+1] << instructions[*I+2] << instructions[*I+3] << std::endl;
                break;
        }
    }

    void debug(u64* instructions,engine* e,thread* t)
    {
        r64* I = &t->enviornment.top().pc;
        // std::cout << "[INFO] "<<std::endl
        while(!(*I>=e->iSize))
        {
            if(e->quit)
            {
                std::cout << "[ERROR] execution terminated unexpectedly" << std::endl;
                break;
            }
            while(e->gFreeze);
            debugPrintInstr(instructions,e,t);
            switch(instructions[*I])
            {
                case(ASS_WRITE):
                    *(u64*)e->objects[instructions[*I+1]] = *(u64*)e->objects[instructions[*I+2]];
                    std::cout << "[INFO] set value of "<<instructions[*I+1]<<" to value of "<<instructions[*I+2]<<std::endl;
                    *I+=3;
                    continue;
                case(ASS_JMP):
                    std::cout << "[INFO] jumped to "<<*I<<std::endl;
                    *I=instructions[*I+1];
                    continue;
                case(ASS_VJMP):
                    std::cout << "[INFO] jumped to "<<*I<<std::endl;
                    *I=*(u64*)e->objects[instructions[*I+1]];
                    continue;
                case(ASS_RET):
                    *I=t->enviornment.top().ret.top();
                    std::cout << "[INFO] jumped to "<<*I<<" through return"<<std::endl;
                    continue;
                case(ASS_PUSHA):
                    std::cout << "[INFO] pushing args stack" << std::endl;
                    t->enviornment.top().args.push((u64*)malloc(sizeof(void*)*t->enviornment.top().AAS));
                    (*I)++;
                    continue;
                case(ASS_POPA):
                    std::cout << "[INFO] popping args stack" << std::endl;
                    t->enviornment.top().args.pop();
                    (*I)++;
                    continue;
                case(ASS_PUSH):{
                    std::stack<u64>* stack = nullptr;
                    switch(instructions[*I+1])
                    {
                        // specific stacks
                        case(0x0): stack = &t->enviornment.top().ret;break;
                        case(0x1): stack = &t->enviornment.top().rv;break;
                        case(0x2): stack = &t->enviornment.top()._this;break;
                        case(0x3): stack = &e->enviornment.top().error;break;
                        // gp stacks
                        case(0x10): stack = &t->enviornment.top().sax;break;
                        case(0x11): stack = &t->enviornment.top().sbx;break;
                        case(0x12): stack = &t->enviornment.top().scx;break;
                        case(0x13): stack = &t->enviornment.top().sdx;break;
                        case(0x14): stack = &t->enviornment.top().sex;break;
                        case(0x15): stack = &t->enviornment.top().sfx;break;
                        case(0x16): stack = &t->enviornment.top().sgx;break;
                        case(0x17): stack = &t->enviornment.top().shx;break;
                        // global gp stacks
                        case(0x18): stack = &t->enviornment.top().sax;break;
                        case(0x19): stack = &t->enviornment.top().sbx;break;
                        case(0x1A): stack = &t->enviornment.top().scx;break;
                        case(0x1B): stack = &t->enviornment.top().sdx;break;
                        case(0x1C): stack = &t->enviornment.top().sex;break;
                        case(0x1D): stack = &t->enviornment.top().sfx;break;
                        case(0x1E): stack = &t->enviornment.top().sgx;break;
                        case(0x1F): stack = &t->enviornment.top().shx;break;

                        //error
                        default:
                            error(instructions,e,t,"stack not found: "+std::to_string(instructions[*I+1]),_error::INVALID_STACK);
                            *I+=3;
                            continue;
                    }
                    //stack->push(*(u64*)e->objects[instructions[*I+2]]);
                    std::cout << "[INFO] pushing "<<instructions[*I+2]<<" to stack "<<getStackName(instructions[*I+1])<<std::endl;
                    stack->push(instructions[*I+2]);
                    *I+=3;
                    continue;}
                case(ASS_POP):{
                    std::stack<r64>* stack = nullptr;
                    switch(instructions[*I+1])
                    {
                        // specific stacks
                        case(0x0): stack = &t->enviornment.top().ret;break;
                        case(0x1): stack = &t->enviornment.top().rv;break;
                        case(0x2): stack = &t->enviornment.top()._this;break;
                        case(0x3): stack = &e->enviornment.top().error;break;
                        // gp stacks
                        case(0x10): stack = &t->enviornment.top().sax;break;
                        case(0x11): stack = &t->enviornment.top().sbx;break;
                        case(0x12): stack = &t->enviornment.top().scx;break;
                        case(0x13): stack = &t->enviornment.top().sdx;break;
                        case(0x14): stack = &t->enviornment.top().sex;break;
                        case(0x15): stack = &t->enviornment.top().sfx;break;
                        case(0x16): stack = &t->enviornment.top().sgx;break;
                        case(0x17): stack = &t->enviornment.top().shx;break;
                        // global gp stacks
                        case(0x18): stack = &e->enviornment.top().gsax;break;
                        case(0x19): stack = &e->enviornment.top().gsbx;break;
                        case(0x1A): stack = &e->enviornment.top().gscx;break;
                        case(0x1B): stack = &e->enviornment.top().gsdx;break;
                        case(0x1C): stack = &e->enviornment.top().gsex;break;
                        case(0x1D): stack = &e->enviornment.top().gsfx;break;
                        case(0x1E): stack = &e->enviornment.top().gsgx;break;
                        case(0x1F): stack = &e->enviornment.top().gshx;break;

                        //error
                        default:
                            error(instructions,e,t,"stack not found: "+std::to_string(instructions[*I+1]),_error::INVALID_STACK);
                            *I+=2;
                            continue;
                    }
                    std::cout << "[INFO] popping stack "<<getStackName(instructions[*I+1])<<std::endl;
                    stack->pop();
                    *I+=2;

                    continue;}
                case(ASS_INT):{
                    interrupt _int_ = e->interrupts[instructions[*I+1]];
                    if(_int_ == nullptr)
                        error(instructions,e,t,"invalid interrupt: "+std::to_string(instructions[*I+1]),_error::INVALID_INTERRUPT);
                    std::cout << "calling interrupt " << std::to_string(instructions[*I+1]) << std::endl;
                    _int_(instructions,e,t);
                    *I+=2;
                    continue;}
                case(ASS_EMOV):{
                    r64* reg = nullptr;
                    switch(instructions[*I+1])
                    {
                        //specific registers
                        case(0x0): reg=&t->enviornment.top().pc;break;
                        case(0x1): reg=&e->enviornment.top().oc;break;
                        //local gp registers
                        case(0x10): reg=&t->enviornment.top().rax;break;
                        case(0x11): reg=&t->enviornment.top().rbx;break;
                        case(0x12): reg=&t->enviornment.top().rcx;break;
                        case(0x13): reg=&t->enviornment.top().rdx;break;
                        case(0x14): reg=&t->enviornment.top().rex;break;
                        case(0x15): reg=&t->enviornment.top().rfx;break;
                        case(0x16): reg=&t->enviornment.top().rgx;break;
                        case(0x17): reg=&t->enviornment.top().rhx;break;
                        case(0x18): reg=&t->enviornment.top().rix;break;
                        case(0x19): reg=&t->enviornment.top().rjx;break;
                        case(0x1A): reg=&t->enviornment.top().rkx;break;
                        case(0x1B): reg=&t->enviornment.top().rlx;break;
                        case(0x1C): reg=&t->enviornment.top().rmx;break;
                        case(0x1D): reg=&t->enviornment.top().rox;break;
                        case(0x1E): reg=&t->enviornment.top().rpx;break;
                        case(0x1F): reg=&t->enviornment.top().rqx;break;
                        //global gp registers
                        case(0x20): reg=&e->enviornment.top().gax;break;
                        case(0x21): reg=&e->enviornment.top().gbx;break;
                        case(0x22): reg=&e->enviornment.top().gcx;break;
                        case(0x23): reg=&e->enviornment.top().gdx;break;
                        case(0x24): reg=&e->enviornment.top().gex;break;
                        case(0x25): reg=&e->enviornment.top().gfx;break;
                        case(0x26): reg=&e->enviornment.top().ggx;break;
                        case(0x27): reg=&e->enviornment.top().ghx;break;
                        case(0x28): reg=&e->enviornment.top().gix;break;
                        case(0x29): reg=&e->enviornment.top().gjx;break;
                        case(0x2A): reg=&e->enviornment.top().gkx;break;
                        case(0x2B): reg=&e->enviornment.top().glx;break;
                        case(0x2C): reg=&e->enviornment.top().gmx;break;
                        case(0x2D): reg=&e->enviornment.top().gox;break;
                        case(0x2E): reg=&e->enviornment.top().gpx;break;
                        case(0x2F): reg=&e->enviornment.top().gqx;break;

                        //error
                        default:
                            error(instructions,e,t,"register not found: "+std::to_string(instructions[*I+1]),_error::INVALID_STACK);
                            *I+=3;
                            continue;
                    }
                    std::cout << "[INFO] set value of "<<getRegName(instructions[*I+1])<<" to "<<instructions[*I+2]<<std::endl;
                    *reg = instructions[*I+2];
                    *I+=3;
                    continue;}
                case(ASS_JNZ):
                {
                    if(*(u64*)e->objects[instructions[*I+1]] != 0)
                    {
                        std::cout << "jumped to " << instructions[*I+2] << " through jnz" << std::endl;
                        *I=instructions[*I+2];//jump
                    }
                    else
                    {
                        std::cout << "[INFO] " << *(u64*)e->objects[instructions[*I+1]] << " != 0" << std::endl;
                        *I+=3;
                    }
                    continue;
                }
                case(ASS_VJNZ):
                {
                    if(*(u64*)e->objects[instructions[*I+1]] != 0)
                    {
                        *I=*(u64*)e->objects[instructions[*I+2]];//jump
                        std::cout << "[INFO] jumped to " << *(u64*)e->objects[instructions[*I+2]] << " through vjnz" << std::endl;
                    }
                    else
                    {
                        std::cout << "[INFO] " << *(u64*)e->objects[instructions[*I+1]] << " != 0" << std::endl;
                        *I+=3;
                    }
                    continue;
                }
                case(ASS_UPDATE):
                {
                    e->objects = (u64**)realloc(e->objects,e->enviornment.top().oc*sizeof(u64));
                    std::cout << "updated objects array to size of " << e->enviornment.top().oc << std::endl;
                    *I+=1;
                    continue;
                }
                case(ASS_ADD):
                {
                    *(u64*)e->objects[instructions[*I+1]] += *(u64*)e->objects[instructions[*I+2]];
                    *I+=3;
                    continue;
                }
                case(ASS_SUB):
                {
                    *(u64*)e->objects[instructions[*I+1]] -= *(u64*)e->objects[instructions[*I+2]];
                    *I+=3;
                    continue;
                }
                case(ASS_MUL):
                {
                    *(u64*)e->objects[instructions[*I+1]] *= *(u64*)e->objects[instructions[*I+2]];
                    *I+=3;
                    continue;
                }
                case(ASS_DIV):
                {
                    *(u64*)e->objects[instructions[*I+1]] /= *(u64*)e->objects[instructions[*I+2]];
                    *I+=3;
                    continue;
                }
                case(ASS_MOD):
                {
                    //_ *(u64*)e->objects[instructions[*I+1]] target
                    //_ *(u64*)e->objects[instructions[*I+2]] mod
                    *(u64*)e->objects[instructions[*I+1]] -= floor(*(u64*)e->objects[instructions[*I+1]] / *(u64*)e->objects[instructions[*I+2]]);
                    *I+=3;
                    continue;
                }
                case(ASS_MOV):
                {
                    *(u64*)e->objects[instructions[*I+1]] = instructions[*I+2];
                    *I+=3;
                    continue;
                }
                case(ASS_MALLOC):
                {
                    e->objects[instructions[*I+1]] = malloc(instructions[*I+2]);
                    *I+=3;
                    continue;
                }
                case(ASS_HLT):
                    *I+=1;
                    std::cout << "[INFO] execution halted" << std::endl;
                    goto endLoop;
                default:
                    error(instructions,e,t,"invalid instruction"+std::to_string(instructions[*I]),_error::INVALID_INSTRUCTION);
                    goto end;
            }
        }
        end: ;
        std::cout << "[INFO] execution complete, end of code!" << std::endl;
        endLoop: ;
        e->__internal_dead_threads.push_back(t->t);
        e->rt--;
    }

    u64 getValue(u64 source){}
    void writeMem(u64 address,u64 value){}
    void copyMem(u64 source,u64 dest,u64 size){}
    void copy(u64 source,u64 dest){}
    void readRegister(u64 reg,u64 dest){}
    void writeRegister(u64 reg,u64 source){}
    void readStack(u64 stack,u64 dest){}
    void writeStack(u64 stack, u64 source){}

    void execute(u64* instructions,engine* e,thread* t)
    {
        r64* I = &t->enviornment.top().pc;
        switch(instructions[*I])
        {
            case(ASS_MOV):{
                writeMem(instructions[*I+2],instructions[*I+1]);
                *I+=3;
            }
            case(ASS_WRITE):{
                copy(instructions[*I+1],instructions[*I+1]);
                *I+=3;
            }
        }
    }
}