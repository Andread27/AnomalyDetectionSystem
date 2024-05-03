#ifndef Tmstmp_hpp
#define Tmstmp_hpp

#include <string> 
#include <vector> 

using namespace std;

class Tmstmp {
    private:
    	vector <int> tms;
    	
    	int t;
    	
    public:
    	 bool exist() const { return !this->tms.empty(); }
    	 
    	 bool exist(int tmsp) const {
	    for (int tm : this->tms) { if (tm == tmsp) { return true; } }
	    return false; }
	    
	 void addTm(int timestamp) {this->tms.push_back(timestamp); }
	 
	 void removeTm() { if (!this->tms.empty()) { this->tms.erase(this->tms.begin()); }}
	 
	 int getSize() const { return static_cast<int>(this->tms.size()); }
	 
	 void setTmsp(int t) {this->t = t; }
	 
	 int getTmsp() {return this->t; }

};

#endif
