#include "Time.hpp"

int long get_nanos(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ((long) (ts.tv_sec * 1000000000L + ts.tv_nsec));
}

void init_time() {
    last_nanos = get_nanos();
    global_time_sec = 0.0;
} 


long int get_day_nanos() {
   struct tm *info;
   struct timespec ts;

   timespec_get(&ts, TIME_UTC);
    
   info = localtime( &(ts.tv_sec) );
   // ISO	ISO 8601, SQL standard	1997-12-17 07:37:16-08
   sprintf(date, "%.4d-%.2d-%.2d %.2d:%.2d:%.2d",
	   info -> tm_year + 1900,
	   info -> tm_mon + 1,
	   info -> tm_mday,
	   info -> tm_hour,
	   info -> tm_min,
	   info -> tm_sec
	   );

   return (ts.tv_nsec);
}

void update_time() {
  
   nanos = get_nanos();

   timeadvance = ((double) (nanos - last_nanos))/((double) (1000000000L));
   global_time_sec = global_time_sec + timeadvance;
	  
   last_nanos = nanos;
}  

