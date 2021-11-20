/*************************************************************************
	> File Name: main.cpp
	> Author: LiuYang
	> Mail: liuyang91
	> Created Time: Thu 11 Nov 2021 02:34:23 PM CST
 ************************************************************************/
#include <iostream>
#include "logSystem.hpp"
using std::cout;
using std::endl;

int main(int argc, char **argv){
    LOG_TRACE("print trace id %d.\n", 231);
    LOG_ERR("print error id %d.\n", 231);
    LOG_WARN("print warning id %d.\n", 231);
    LOG_INFO("print info id %d.\n", 231);
    LOG_DEBUG("print debug id %d.\n", 231);
    
    return 0;
}
