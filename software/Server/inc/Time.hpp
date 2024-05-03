#ifndef TIME_HPP
#define TIME_HPP

#include <ctime> 
#include <cstdio>

#include "Global.hpp" 

int long get_nanos(void);

long int get_day_nanos();

void init_time();

void update_time();

#endif
