#include "Monitor.hpp"

bool monitorAvrg(AveragesLab avlab) {
     PGresult *res;
     sprintf(sqlcmd, "SELECT sensor, average FROM Average where ((tmestamp = %d) AND (pid = %d))",timestamp, pid);
     res = db1.ExecSQLtuples(sqlcmd);
     int rows = PQntuples(res);
     for (int i = 0; i < rows; ++i) {
         string sensor = PQgetvalue(res, i, 0);
         string averageDB = PQgetvalue(res, i, 1);
         
         string average = to_string(avlab.getAvrg(sensor));
         if (average.compare(averageDB) != 0 ) {
             // Average contiene valori medi errati
             
             cout << "\n\nmonitorAvrg :" << sensor << "value = " << average << ", " <<  averageDB << "\n\n";
             PQclear(res);
             return false;
         }
     }
     PQclear(res);
     return true;
}

bool monitorCov(CovariancesLab covlab) {
     PGresult *res;
     sprintf(sqlcmd, "SELECT sensor1, sensor2, covariance FROM Covariance where ((tmestamp = %d) AND (pid = %d))",timestamp, pid);
     res = db1.ExecSQLtuples(sqlcmd);
     int rows = PQntuples(res);
     for (int i = 0; i < rows; ++i) {
         string sensor1 = PQgetvalue(res, i, 0);
         string sensor2 = PQgetvalue(res, i, 1);

         string covDB = PQgetvalue(res, i, 2);
         string cov = to_string(covlab.getCov(sensor1, sensor2));
                 
         if (cov.compare(covDB) != 0 && cov.compare(SMALLEST_VALUE) != 0) {
             // Covariance contiene covarianze errate
             cout << "\n\nmonitorCov :" << sensor1 << ", " << sensor2 << "value = " << cov << ", " <<  covDB << "\n\n";
             PQclear(res);
             return false;
         }
     }
     PQclear(res);
     return true;
}

bool monitorAvrgAnmly(AveragesLab avlab) {
     PGresult *res;
     sprintf(sqlcmd, "SELECT sensor FROM Average where ((tmestamp = %d) AND (pid = %d) AND (deviation > stddeviation))",timestamp, pid);
     
     res = db1.ExecSQLtuples(sqlcmd);
     int rows = PQntuples(res);
     
     // Se numero di sensori anomali != righe tupla -> return false
     if (rows != avlab.sizeAnmly()) { 
         cout << "\n\nmonitorAvrgAnmly rows:" << rows << ", " << avlab.sizeAnmly() << "\n\n";
         return false; 
     }
     
     for (int i = 0; i < rows; ++i) {
         string sensor = PQgetvalue(res, i, 0);
         if (!avlab.isAnmly(sensor)) {
             // Average contiene sensori anomali errati
             cout <<"\n\nmonitorAvrgAnmly sensore errato = " << sensor << "\n\n";
             PQclear(res);
             return false;
         }
     }
     PQclear(res);
     return true;
}

bool monitorExecTime() {
    PGresult *res;
     sprintf(sqlcmd, "SELECT exectime FROM LogTime");
     res = db1.ExecSQLtuples(sqlcmd);
     int rows = PQntuples(res);
     for (int i = 0; i < rows; ++i) {
         long long int exec_time = stoll(PQgetvalue(res, i, 0));
        
         if (exec_time > FIVE_SEC) {
             cout <<"\n\nmonitorLogTime exec_time = " << exec_time << "\n\n";
             PQclear(res);
             return false;
         }
     }
     PQclear(res);
     return true;
}

bool monitorResultTime() {
    PGresult *res;
     sprintf(sqlcmd, "SELECT result FROM LogTime");
     res = db1.ExecSQLtuples(sqlcmd);
     int rows = PQntuples(res);
     
     for (int i = 0; i < rows; ++i) {
         string result = PQgetvalue(res, i, 0);

         if (result.compare("True") != 0) {
             cout <<"\n\nmonitorLogTime result = " << result << "\n\n";
             PQclear(res);
             return false;
         }
     }
     PQclear(res);
     return true;
}

bool monitor(AveragesLab avlab, CovariancesLab covlab) {
    return (monitorAvrg(avlab) && monitorCov(covlab) && monitorAvrgAnmly(avlab) && monitorExecTime() && monitorResultTime()); 
}
