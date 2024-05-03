
-- database already exists
\c :dbname 

-- Crea i domini e i tipi di dato
CREATE DOMAIN  FloatValue AS NUMERIC NOT NULL;
CREATE DOMAIN  SensorName AS VARCHAR(30) NOT NULL;
CREATE DOMAIN  TimePoint AS timestamp NOT NULL;

CREATE TYPE  ErrorMessage AS ENUM ('True', 'False');

-- Crea le tabelle se non esistono già

CREATE TABLE IF NOT EXISTS Average (
        pid int NOT NULL,
        sensor SensorName,
        average FloatValue,
        tmestamp int NOT NULL,
        stddeviation FloatValue,
        deviation FloatValue,
        PRIMARY KEY (pid, sensor, tmestamp)
);

CREATE TABLE IF NOT EXISTS Covariance (
        pid int NOT NULL,
        sensor1 SensorName,        
	sensor2 SensorName,
	covariance FloatValue,
	tmestamp int NOT NULL, 
	stddeviation FloatValue,
	deviation FloatValue,
        PRIMARY KEY (pid, sensor1, sensor2, tmestamp)
);

CREATE TABLE IF NOT EXISTS LogTime (
	timevalue TimePoint,
	exectime bigint NOT NULL,
	pid int NOT NULL,
	tmestamp int NOT NULL,
	windowsize int NOT NULL, 
 	result ErrorMessage, 
	PRIMARY KEY (timevalue, exectime, pid, tmestamp)
);

