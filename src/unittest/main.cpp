/*************************************************************************
	> File Name: main.cpp
	> Author: LiuYang
	> Mail: liuyang91
	> Created Time: Thu 11 Nov 2021 02:34:23 PM CST
 ************************************************************************/
#include "logSystem.hpp"

#include <cstdio>

#include <thread>
#include <random>

void test_multi_thread(int num)
{
    LOG_TRACE("print num: %d.\n", num);
    //LOG_INFO("print num: %d.\n", num);
}

int main(int argc, char **argv){
    LOG_TRACE("print trace id %d.\n", 231);
    LOG_TRACE("print trace .\n" );
    LOG_ERR("print error id %d.\n", 231);
    LOG_ERR("print error id %%d.\n");
    LOG_WARN("print warning id %d.\n", 231);
    LOG_INFO("print info id %d.\n", 231);
    LOG_DEBUG("print debug id %d.\n", 231);

    LOG_ENTER();
    LOG_EXIT();

    std::thread ttest[10];
    std::uniform_int_distribution<unsigned int> u(0,9);
    std::default_random_engine e;
    for(int i = 0; i < 10; i++){
        int rand = u(e);
        ttest[i] = std::thread(test_multi_thread, rand); 
    } 

    for (int i=0; i < 10; i++){
        ttest[i].join();
    }
    
    return 0;
}
