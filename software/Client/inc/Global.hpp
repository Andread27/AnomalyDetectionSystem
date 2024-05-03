#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "../Con2redis/inc/con2redis.h"

#define READ_STREAM "streamClient"
#define WRITE_STREAM "streamServer"

#define LOCALHOST "127.0.0.1"

#define REDIS_PORT 6379

extern redisContext *c2r;

extern redisReply *reply;

extern int send_counter;

extern int read_counter;

extern char username[100];

// extern int W;

extern int pid;

#endif

