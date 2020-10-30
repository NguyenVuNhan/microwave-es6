#include "../utils/logging.h"
#include "memoryHandler.h"

#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>

#define MICROWAVERC ".microwaverc"

using namespace logging;

LPCMemoryHandler::LPCMemoryHandler()
{
    std::string   line;
    std::ifstream ifile(MICROWAVERC);
    if (ifile.is_open())
    {
        getline(ifile, line);
        this->power = atoi(line.c_str());
        getline(ifile, line);
        this->duration = (time_t) atoi(line.c_str());
        ifile.close();
    }
    else
    {
        LOG_ERROR("Unable to open file");
    }
}

time_t LPCMemoryHandler::getDuration()
{
    return this->duration;
}

int LPCMemoryHandler::getPower()
{
    return this->power;
}

void LPCMemoryHandler::save(unsigned int power, time_t duration)
{
    this->power = power;
    this->duration = duration;

    std::ofstream ofile(MICROWAVERC, std::ios::trunc);
    if (ofile.is_open())
    {
        ofile << this->power << " \n";
        ofile << this->duration << " \n";
        ofile.close();
    }
    else
    {
        LOG_ERROR("Unable to open file");
    }
}
