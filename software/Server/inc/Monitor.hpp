#ifndef MONITORS_HPP
#define MONITORS_HPP

#include "Server.hpp"

bool monitor(AveragesLab avlab, CovariancesLab covlab);

bool monAvrg(AveragesLab avlab);

bool monitorCov(CovariancesLab covlab);

bool monitorAvrgAnmly(AveragesLab avlab);

bool monitorExecTime();

bool monitorResultTime();

#endif
