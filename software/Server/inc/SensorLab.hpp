#ifndef SENSORLAB_HPP
#define SENSORLAB_HPP

#include <map>
#include <vector>
#include <string>

using namespace std;

class SensorsLab {
private:
    map<string, vector<double>> data;    	
public:

    bool isSensor(const string sensor) { return (this->data.find(sensor) != this->data.end()); }
    
    void newSensor (const string sensor) { this->data[sensor] =  vector<double>(); } 
    
    void saveValue(const string sensor, double value){
    	this->data[sensor].push_back(value); }   

    vector<double> getValues(const string sensor) {
    	return this->data.at(sensor); }
    
    void resetSensors() { 
        for (auto& sensor : this->data) {
            if (!sensor.second.empty()) { sensor.second.erase(sensor.second.begin()); } } }

};

#endif
