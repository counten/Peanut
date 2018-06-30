/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn 
*/

#include "Conf.h"

// Inner Project
#include "Defination.h"
#include "../Util/StrUtil.h"
#include "../Log/Log.h"


std::map<std::string, std::string> _confValue;


int Peanut::readConfAll()
{
    std::fstream cfgFile;
    cfgFile.open(CFG_FILE);
    if (!cfgFile.is_open())
    {
        logError("Can not open config file!");
        return 1;
    }

    char tmp[1000];
    int Flag = 1; // 1 start record, 0:end record;
    std::string module;
    while (!cfgFile.eof())
    {
        cfgFile.getline(tmp, 1000);

        // Jump the comment
        if (tmp[0] == '#')
        {
            continue;
        }

        // start and end module
        if (tmp[0] == '<')
        {
            if (tmp[1] == '/')
            {
                Flag = 0;
                continue;
            }
            Flag = 1;
            module = tmp;
            continue;
        }
        std::string line(tmp);

        // Find '=' to divide and store them;
        if (Flag == 1)
        {
            size_t pos = line.find('=');
            if (pos == std::string::npos)
            {
                continue;
            }
            _confValue.insert(
                    std::pair<std::string, std::string>(
                            module + Peanut::eraseFlSpace(line.substr(0, pos)),
                            Peanut::eraseFlSpace(line.substr(pos + 1)))
            );
        }
    }
    cfgFile.close();
    return 0;
}


std::string Peanut::getValue(std::string module, std::string key)
{
    key = "<" + module + ">" + key;
    return Peanut::getValueMapKey(_confValue, key);
}
