#include "Server.hpp"

vector<string> sensors_list;

void serverStart() {

     init_time();
    
     nanos = get_nanos();

     SensorsLab slab;
     
     AveragesLab avlab;
     
     CovariancesLab covlab;
     
     while (1) {
     	
     	string block = receiveRedis(); 
     	
     	if (block.compare("") != 0) {
     	    cout << "\nmain(): pid " << pid << ": user " << username << ": Trying to read msg " << read_counter << " from stream " << READ_STREAM << "\n";
     	    
     	    if (W != 0) {
     	        nanos_day = get_day_nanos();
     	
     	        logTimeDB(true);
     	    }
     	    read_counter++;
     	     	
     	    istringstream ss_block(block);
     	
     	    string message; 
     	
     	    while (getline(ss_block, message, ';')) {
     	        stringstream ss(message);
     	    
     	        string tmsp_str, sensor, value_str;
    	        getline(ss, tmsp_str, ',');
    	        getline(ss, sensor, ',');
    	        getline(ss, value_str);
    
    	        if (sensor.compare("timer") == 0) {
	            W = atoi(tmsp_str.c_str());
	            cout << "\nReceived temporal window " << W << " from client\n";
	            nanos_day = get_day_nanos();
     	            logTimeDB(true);
    	        }
    	        else {
    	            timestamp = atoi(tmsp_str.c_str());
    	            double value;
    	
    	            if (value_str.compare("NULL") == 0) {value = NONE;}
    	            else { value = atof(value_str.c_str());}
    	
    	            if (!slab.isSensor(sensor)) {
    	                if (sensor.compare("") != 0) {
    	                    slab.newSensor(sensor);
    	                    sensors_list.push_back(sensor);
    	                }
    	            }              
        
                    if (slab.isSensor(sensor)) {
    	                slab.saveValue(sensor, value);
     	            }   
                 }
             }
             cout << "\nThis is Timestamp "<< timestamp << ":\n";
             avrgCalc(slab, avlab);
             covCalc(slab, avlab, covlab); 
             
             
             if (!monitor(avlab, covlab)) {
                 // c'è stato un malfunzionamento durante il salvataggio dei dati nel DB
                 cout << "\n!! Data has not been saved correctly in the database !!\n";
             }
             
             sendRedis(avlab.sizeAnmly(), covlab.sizeAnmly());
             
             covlab.resetAnmly();
             avlab.resetAnmly();                
             slab.resetSensors();
             update_time();
         }
         
     }
}


