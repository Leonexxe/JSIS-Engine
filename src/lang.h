/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/src/lang.h                                                          #
# Project: /Users/leonexxe/code/JSIS-Engine/src                                                              #
# Created Date: Wednesday, September 7th 2022, 7:24:05 pm                                                    #
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
    const u64 ASS_MOV         = 0x00; // mov [obj] [literal]         // writes a literal value to an address
    const u64 ASS_RET         = 0x01; // ret                         // jumps to the top of the ret stack
    const u64 ASS_WRITE       = 0x02; // write [obj] [obj]           // writes the value of the second to the first object
    const u64 ASS_PUSHA       = 0x03; // pusha                       // pushes an args object onto the args stack
    const u64 ASS_POPA        = 0x04; // popa                        // pops the args stack
    const u64 ASS_PUSH        = 0x05; // push [stack] [obj]          // pushes the objects value onto the stack
    const u64 ASS_POP         = 0x06; // pop  [stack]                // pops the stack
    const u64 ASS_JMP         = 0x07; // jmp  [symbol]               // jumps to a symbol
                                // ljmp [literal]              // jumps to a literal address
    const u64 ASS_VJMP        = 0x08; // vjmp [obj]                  // jumps to the address given by the objects value
    const u64 ASS_SET         = 0x09; // set  [settable] [literal]   // sets engine values such as the EOO to a literal value
    const u64 ASS_EMOV        = 0x0A; // emov [EO] [literal]         // write the value of an engine defined object to a literal
    const u64 ASS_EWRITE      = 0x0B; // ewrite [EO] [obj]           // write the value of an engine defined object to the value of an object
    const u64 ASS_CALL        = 0x0C; // call [EFN]                  // call a function defined and implemented by the engine by its number
    const u64 ASS_GET         = 0x0D; // get [obj] [EON]             // get the value of an engine defined object and write it to an object
    const u64 ASS_AWRITE      = 0x0E; // awrite [obj] [obj] [obj]    // write the value of the third object to obj1[obj2]
    const u64 ASS_ALWRITE     = 0x0F; // awrite [obj] [obj] [literal]// write a literal value to obj1[obj2]
    const u64 ASS_HLT         = 0x10; // hlt                         // halt execution
    const u64 ASS_PAUSE       = 0x11; // pause                       // pause execution until hit up by another thread
    const u64 ASS_EXEC        = 0x12; // exec [obj] [obj]            // kick of another thread at the address provided by the value of an object thread id will then be written to the second object
    const u64 ASS_RESUME      = 0x13; // resume [obj]                // resume execution on another thread
    const u64 ASS_MALLOC      = 0x14; // malloc [obj] [literal]      // tell the engine allocate a number of bytes for the object
    const u64 ASS_FREE        = 0x15; // free [obj]                  // tell the engine to deallocate (free) the memory that was allocated for the object
    const u64 ASS_INT         = 0x16; // int [literal]               // works like assembly interrupts, triggers engine defined behavior
    const u64 ASS_AEWRITE     = 0x17;
    const u64 ASS_AELWRITE    = 0x18;
    const u64 ASS_PUSHE       = 0x19; //pushe                         //pushes a new set of stacks and registers
    const u64 ASS_POPE        = 0x1A; //pope                          //pops the current set of stacks and registers
    const u64 ASS_RESET       = 0x1B; //reset                         //resets the current stacks and registers
    const u64 ASS_JNZ         = 0x1C;
    const u64 ASS_VJNZ        = 0x1D;
    const u64 ASS_UPDATE      = 0x1E;
    const u64 ASS_ADD         = 0x1F; //add [obj] [obj]
    const u64 ASS_SUB         = 0x20; //sub [obj] [obj]
    const u64 ASS_MUL         = 0x21; //mul [obj] [obj]
    const u64 ASS_DIV         = 0x22; //div [obj] [obj]
    const u64 ASS_MOD         = 0x23; //mod [obj] [obj]
}