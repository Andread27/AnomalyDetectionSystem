#include "Main.hpp"

int main() {

    startRedis();
    
    serverStart();

    redisFree(c2r);
    
    db1.finish();
        
    return 0;
}
