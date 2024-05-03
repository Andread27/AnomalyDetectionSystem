#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "../Con2redis/inc/con2redis.h"
#include "../Con2db/inc/pgsql.h"
#include "Utils.hpp"

extern redisContext *c2r;

extern redisReply *reply;

extern Con2DB db1;

extern int send_counter, read_counter;

extern int timestamp;

extern char sqlcmd[1000];

extern int pid;

extern char username[100];

extern int W;

extern char date[200];

extern long int nanos, last_nanos;

extern long int nanos_day;

extern double global_time_sec, timeadvance;

//extern double NONE;


#endif

