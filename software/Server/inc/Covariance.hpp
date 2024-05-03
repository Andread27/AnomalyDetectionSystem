#ifndef COVARIANCE_HPP
#define COVARIANCE_HPP

#include <string>
#include <map>
#include <string>
#include <utility>

using namespace std;

class CovariancesLab {
private:
    map<pair<string,string>, double> cov; 
    vector<pair<string,string>> anmly;
public:
    
    void addCov (string sens1, string sens2, double c)  { this->cov[make_pair(sens1, sens2)] = c; }

    double getCov(string sens1, string sens2) { 
       auto st = this->cov.find(make_pair(sens1, sens2));
       return st->second; 
    }
    
    vector<double> getCovs() {
        vector<double> covValues;
        for (const auto& pair : this->cov) { covValues.push_back(pair.second); }
        return covValues;
    }
    
    int getSize() const { return static_cast<int>(this->cov.size()); }
    
    bool isPresent(string sens1, string sens2) {
       if (sens1.compare(sens2) == 0) { return true; } 
       if (this->cov.find(make_pair(sens2, sens1)) != this->cov.end()) { return true; } 
       return false; }
    
    vector<pair<string,string>> getAnmly() { return this->anmly; }
    
    void resetAnmly() { this->anmly.clear(); } 
    
    void addAnmly(pair<string,string> sensors) { this->anmly.push_back(sensors); }
    
    int sizeAnmly() { return static_cast<int>(this->anmly.size()); }
    
    bool isAnmly(pair<string,string> sensors) { 
        for (const auto& pair : this->anmly) { if (pair == sensors) { return true; } }
        return false; }
    
};

#endif
