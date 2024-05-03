#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "Global.hpp"
#include "Utils.hpp"

using namespace std;

ifstream openfile();

void startRedis();

void sendRedis(string message);

void clientStart(ifstream& file);

int msleep(long msec);

#endif

