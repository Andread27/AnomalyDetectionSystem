#ifndef Data_hpp
#define Data_hpp

#include <string> 
#include <vector> 

using namespace std;

class Data {

    private:
    	vector<string> usedsensor;
    	
    	vector<string> message;
    	
    public:
    
        string timestamp;
        
   	string sensor;
   	
   	string value;
   	
   	string getData() { return (timestamp + "," + sensor + "," + value); }

    	void addUSensor() { this->usedsensor.push_back(sensor); }
    	
    	int  getSize() const { return (static_cast<int>(this->usedsensor.size())); }
    	
    	bool check() const {
    		auto find_sensor = find(this->usedsensor.begin(), this->usedsensor.end(), sensor);
    		if (find_sensor != this->usedsensor.end()) { return true; }
    		return false; 
    	}
              
       void addMssg(string mess) {this->message.push_back(mess); }
       
       vector<string> getMssg() { return this->message; }
       
       void rmMssg() { this->message.clear(); }
};

#endif
