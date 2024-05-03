#include "Server.hpp"

void avrgCalc(SensorsLab slab, AveragesLab& avlab) {
    for (const auto& sensor : sensors_list) {
        int null = 0;
        double  sum = 0;
        for (const auto& value : slab.getValues(sensor)) {
    	    if (value != NONE) { sum += value; }
    	    else { null++; } 
    	}
    	int size = W - null;
    	if (size > 0) {
    	    double average = sum / size;
    	    avlab.addAvrg(sensor, average);
    	} else { 
    	    avlab.addAvrg(sensor, NONE); 
    	}
    }
    avrgDev(avlab);
}

void covCalc(SensorsLab slab, AveragesLab avlab, CovariancesLab& covlab) {
    for (const auto& sens1 : sensors_list) {
	for (const auto& sens2 : sensors_list) {
	    double cov = 0.0;
	    if (!covlab.isPresent(sens1, sens2)) {
	    	vector<double> val_sens1 = slab.getValues(sens1);
	    	vector<double> val_sens2 = slab.getValues(sens2);
	    	double av_sens1 = avlab.getAvrg(sens1);
	    	double av_sens2 = avlab.getAvrg(sens2);
	    	int null = 0;
	    	for (int i = 0; i < W; i++) {
	    	    if (val_sens1[i] != NONE && val_sens2[i] != NONE) {
	    	        cov += (val_sens1[i] - av_sens1) * (val_sens2[i] - av_sens2);
	    	    } 
	    	    else { null++; } 
	    	}
	    	int size = W - null;
	    	if (size > 0) {
		    cov /= size;
		    covlab.addCov(sens1, sens2, cov);
		} else { 
		    covlab.addCov(sens1, sens2, NONE); 
		}	
	     }
	}
    }
    covDev(covlab);
}
