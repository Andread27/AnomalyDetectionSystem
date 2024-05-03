#ifndef AVERAGE_HPP
#define AVERAGE_HPP

#include <map>
#include <string>
#include <vector>

using namespace std;

class AveragesLab {
private:
    map<string, double> avrg;
    vector<string> anmly;
    
public:
    
    map<string, double> getAvrgs()  { return this->avrg; }
    
    void addAvrg (string sensor, double avrg) { this->avrg[sensor] = avrg; }
    
    double getAvrg (string sensor) { return this->avrg[sensor]; }
    
    int getSize() const { return static_cast<int>(this->avrg.size()); }
      
    vector<string> getAnmly() { return this->anmly; }
    
    void resetAnmly() { this->anmly.clear(); } 
    
    void addAnmly(string sensor) { this->anmly.push_back(sensor); }
    
    int sizeAnmly() { return static_cast<int>(this->anmly.size()); }
    
    bool isAnmly(string sensor) { 
        for (const auto& sens : this->anmly) { if (sens.compare(sensor) == 0) { return true; } }
        return false; }
    
};

#endif
