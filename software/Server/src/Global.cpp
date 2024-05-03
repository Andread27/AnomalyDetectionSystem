#include "Global.hpp"

redisContext *c2r;

redisReply *reply;

Con2DB db1(LOCALHOST, DB_PORT, DB_USER, DB_PASS, DB_NAME);

int send_counter, read_counter = 0;

int pid;

int timestamp = 0;

char sqlcmd[1000];

char username[100];

int W;

char date[200];

long int nanos, last_nanos = 0;

long int  nanos_day;

double global_time_sec, timeadvance;

//double NONE = 0;

