#include "Server.hpp"

void avrgDB(string sensor, double avrg, double std_dev, double dev) {
    PGresult *res;
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
    sprintf(sqlcmd,"INSERT INTO Average VALUES (%d, \'%s\', %f, %d, %f, %f) ON CONFLICT DO NOTHING",
    		pid, sensor.c_str(), avrg, timestamp, std_dev, dev);    
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
 }  

void covDB(string sens1, string sens2, double cov, double std_dev, double dev) {
    PGresult *res;
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
    sprintf(sqlcmd,"INSERT INTO Covariance VALUES (%d, \'%s\', \'%s\', %f, %d, %f, %f) ON CONFLICT DO NOTHING",
    		pid, sens1.c_str(), sens2.c_str(), cov, timestamp, std_dev, dev);     
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
 } 
 
 
 void logTimeDB (bool success) {
    PGresult *res;
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
    sprintf(sqlcmd, "INSERT INTO LogTime VALUES (\'%s\', %ld, %d, %d, %d, \'%s\') ON CONFLICT DO NOTHING",
	  date,
	  nanos_day,
	  pid,
	  timestamp,
	  W,
	  success ? "True" : "False"
	  );    
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}
