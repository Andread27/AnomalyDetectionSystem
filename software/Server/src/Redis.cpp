#include "Server.hpp"

void startRedis() {
   
   unsigned seed = (unsigned) time(NULL);  
    
   srand(seed);
   sprintf(username, "%u", rand());
   
   pid = getpid();
   
   cout << "\nmain(): pid " << pid << ": user " << username << ": connecting to redis ...\n";
   
   c2r = redisConnect(LOCALHOST, REDIS_PORT);

   cout << "main(): pid "<< pid << ": user " << username << ": connected to redis\n";
   
   // delete stream if it exists
   reply = RedisCommand(c2r, "DEL %s", READ_STREAM);
   assertReply(c2r, reply);
   dumpReply(reply, 0);
   reply = RedisCommand(c2r, "DEL %s", WRITE_STREAM);
   assertReply(c2r, reply);
   dumpReply(reply, 0);
   
   /* Create streams/groups */
   initStreams(c2r, READ_STREAM);
   initStreams(c2r, WRITE_STREAM);
}


void sendRedis(int size_avrg, int size_cov) {

	string avrg_message;
	if (size_avrg == 0) {
	    avrg_message = "\nNo Anomalous Average Values\n";
	} else {
	    avrg_message = "\nThe number of Anomalous Average Values is " + to_string(size_avrg) + "\n";
	}
	
	string cov_message;
	if (size_cov == 0) {
	    cov_message = "No Anomalous Covariances\n";
	} else {
	    cov_message = "The number of Anomalous Covariances is " + to_string(size_cov) + "\n";
	}
	
	string message = avrg_message + cov_message;
	
	cout << message;
	
	cout << "\nmain(): pid " << pid << ": user " << username << ": Trying to send msg " << send_counter << " to stream " << READ_STREAM << "\n";
	
	send_counter++;
	reply = RedisCommand(c2r, "XADD %s * %s %s %s %s",
		WRITE_STREAM, to_string(send_counter).c_str(), message.c_str(),"size_of_message ", to_string(message.size()).c_str());
	assertReplyType(c2r, reply, REDIS_REPLY_STRING);
	freeReplyObject(reply);	
}

string receiveRedis() {
        char streamname[100];
        int i, k;
        int block = 1000000000;
        
        reply = RedisCommand(c2r, "XREADGROUP GROUP diameter %s BLOCK %d COUNT 1 NOACK STREAMS %s >", 
               username, block, READ_STREAM);
	
        assertReply(c2r, reply);
        dumpReply(reply, 0);
        
        string message;
        
        char size_mess[10];

	for (k = 0; k < ReadNumStreams(reply); k++) {
	    
	    ReadStreamName(reply, streamname, k);
	    
	    for (i = 0; i < ReadStreamNumMsg(reply, k); i++) {
	        
		ReadStreamMsgVal(reply, k, i, 3, size_mess);
		
	        char fval[atoi(size_mess)];
	        
	        ReadStreamMsgVal(reply, k, i, 1, fval);
	        message = fval;
	    }
	}
        freeReplyObject(reply);
        return message;
}
