#include "Server.hpp"

void avrgDev(AveragesLab& avlab) {   
     double mean = 0.0;   
     int size = 0;
     for (const auto& sensor : sensors_list) {
    	 if (avlab.getAvrg(sensor) != NONE) {
    	    mean += avlab.getAvrg(sensor);
    	    size++;
    	 }
     }
     mean /= size;
     
     double var = 0.0;

     for (const auto& sensor : sensors_list) {
    	 if (avlab.getAvrg(sensor) != NONE) {
             var += pow(avlab.getAvrg(sensor) - mean, 2);
         }
     }
     var /= size;
     
     double std_dev = sqrt(var) * AVRG_THOLD;
     
     cout << "Insert in Database Average Values\n";
     for (const auto& sensor : sensors_list) {
          if (avlab.getAvrg(sensor) != NONE) {
               double this_dev = fabs(avlab.getAvrg(sensor) - mean);
               if (this_dev > std_dev) { 
                    avlab.addAnmly(sensor);
               }
               avrgDB(sensor, avlab.getAvrg(sensor), std_dev, this_dev);
          }
     }
}


void covDev(CovariancesLab& covlab) {
    double mean = 0.0;
    int size = 0;

    for (const auto& cov : covlab.getCovs()) {
    	if (cov != NONE) {
    	    mean += cov;
    	    size++;
    	}
    }

    mean /= size;
    
    double var = 0.0;
    
    for (const auto& cov : covlab.getCovs()) {
    	if (cov != NONE) {
    	    var += pow(cov - mean, 2);
        }
    }
    var /= size;

    double std_dev = sqrt(var) * COV_THOLD;
    
    cout << "Insert in Database Covariances\n";
    for (const auto& sens1 : sensors_list) {
        for (const auto& sens2 : sensors_list) {
            if (!covlab.isPresent(sens1, sens2)) {
	        if (covlab.getCov(sens1, sens2) != NONE) {
	             double this_dev = fabs(covlab.getCov(sens1, sens2) - mean);
    		     if (this_dev > std_dev) {
    		         covlab.addAnmly(make_pair(sens1, sens2));
		     }
		     covDB(sens1, sens2, covlab.getCov(sens1, sens2), std_dev, this_dev);
	        }
	    
            }
        }
    }
}
