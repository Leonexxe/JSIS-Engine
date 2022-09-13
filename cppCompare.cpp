/*############################################################################################################
# File: /Users/leonexxe/code/JSIS-Engine/cppCompare.cpp                                                      #
# Project: /Users/leonexxe/code/JSIS-Engine                                                                  #
# Created Date: Tuesday, September 13th 2022, 6:00:35 pm                                                     #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2022 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#include <chrono>
#include <vector>
#include <iostream>
#include <fstream>

std::vector<unsigned long long> times;

void exec()
{
    for(int I = 0;I<1000000;I++)
        std::cout << (char)65;
    std::cout << (char)66 << (char)10;
}

int main(int argc,char** argv)
{
    int runs = 100;
    for(int I = 0;I<runs;I++)
    {
        std::cout <<std::endl<< "starting new run..." << std::endl;
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        exec();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() <<"[ns]"<< std::endl<<std::endl;
        times.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count());
    }
    //calculate average time
    unsigned long long dTotal = 0;
    for(unsigned long long I : times)
        dTotal+=I;
    auto total = std::chrono::nanoseconds(dTotal); 
    dTotal/=runs;
    auto avg = std::chrono::nanoseconds(dTotal);

    std::ofstream out("/users/leonexxe/code/JSIS-engine/compare/cpp.txt");

    out << "C++:" << std::endl;
    out << "total time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(total).count() << "[s]" << std::endl
        << std::chrono::duration_cast<std::chrono::milliseconds>(total).count() << "[ms]" << std::endl
        << std::chrono::duration_cast<std::chrono::microseconds>(total).count() << "[µs]" << std::endl
        << std::chrono::duration_cast<std::chrono::nanoseconds> (total).count() << "[ns]" << std::endl;

    out << "average time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(avg).count() << "[s]" << std::endl
        << std::chrono::duration_cast<std::chrono::milliseconds>(avg).count() << "[ms]" << std::endl
        << std::chrono::duration_cast<std::chrono::microseconds>(avg).count() << "[µs]" << std::endl
        << std::chrono::duration_cast<std::chrono::nanoseconds> (avg).count() << "[ns]" << std::endl;

    out.close();
}