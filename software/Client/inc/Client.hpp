#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

#include "Data.hpp"
#include "Tmstmp.hpp"
#include "Global.hpp"
#include "Utils.hpp"

void clientStart(ifstream& file);

string receiveRedis();

void sendRedis(vector<string> msg);

#endif
