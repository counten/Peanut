/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn 
*/

#include "Conf.h"

Conf::Conf()
{
    setConfFile(CFG_DEFAULT_FILE);
}


std::string Conf::getConfFile()
{
    return confFile;
}


void Conf::setConfFile(std::string confFile)
{
    Conf::confFile = confFile;
}



std::map<std::string, std::string> resMap;

void Conf::initMimeType()
{
    resMap.insert(std::pair<std::string, std::string>("html", "text/html"));
    resMap.insert(std::pair<std::string, std::string>("htm", "text/html"));
    resMap.insert(std::pair<std::string, std::string>("txt", "text/plain"));
    resMap.insert(std::pair<std::string, std::string>("svg", "text/svg"));
    resMap.insert(std::pair<std::string, std::string>("css", "text/css"));
    resMap.insert(std::pair<std::string, std::string>("js", "text/javascript"));

    resMap.insert(std::pair<std::string, std::string>("jpeg", "image/jpeg"));
    resMap.insert(std::pair<std::string, std::string>("jpg", "image/jpeg"));
    resMap.insert(std::pair<std::string, std::string>("png", "image/png"));
    resMap.insert(std::pair<std::string, std::string>("gif", "image/gif"));
    resMap.insert(std::pair<std::string, std::string>("ico", "image/ico"));

    resMap.insert(std::pair<std::string, std::string>("woff", "application/woff;charset=UTF-8"));
    resMap.insert(std::pair<std::string, std::string>("wasm", "application/wasm"));
    resMap.insert(std::pair<std::string, std::string>("ttf", "application/x-font-ttf;charset=UTF-8"));
    resMap.insert(std::pair<std::string, std::string>("eot", "application/eot;charset=UTF-8"));
}

std::map<std::string, std::string> mnServerCfg;


int Conf::readConfAll()
{
    std::fstream cfgFile;
    cfgFile.open(getConfFile());
    if (!cfgFile.is_open())
    {
        Log::logError("Can not open config file!");
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
            mnServerCfg.insert(
                    std::pair<std::string, std::string>(
                            module + StrUtil::suEraseFlSpace(line.substr(0, pos)),
                            StrUtil::suEraseFlSpace(line.substr(pos + 1)))
            );
        }
    }
    cfgFile.close();
    return 0;
}


std::string Conf::getValue(std::string module, std::string key)
{
    key = "<" + module + ">" + key;
    return StrUtil::suGetValueMapKey(mnServerCfg, key);
}
