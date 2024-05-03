#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <unistd.h>

#include "Global.hpp"
#include "Average.hpp"
#include "SensorLab.hpp"
#include "Covariance.hpp"
#include "Time.hpp"
#include "Monitor.hpp"

extern vector<string> sensors_list;

void sendRedis(int size_avrg, int size_cov);

string receiveRedis();

void avrgCalc(SensorsLab slab, AveragesLab& avlab);

void covCalc(SensorsLab slab, AveragesLab avlab, CovariancesLab& covlab);

void avrgDev(AveragesLab& avlab);

void covDev(CovariancesLab& covlab);

void avrgDB(string sensor, double avrg, double std_dev, double dev);

void covDB(string sens1, string sens2, double cov, double std_dev, double dev);

void logTimeDB(bool success);


#endif
