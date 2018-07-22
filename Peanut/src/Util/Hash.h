/*
* Author: micle 2018/3/20
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/


#ifndef PEANUT_HASH_H
#define PEANUT_HASH_H

#include <string>

#define MAXTABLELEN 1024    // 默认哈希索引表大小

/** Hash Index table*/
typedef struct _HASHTABLE
{
    long nHashA;
    long nHashB;
    bool bExists;
    std::string value;

} HASHTABLE;

class StringHash
{
private:

    unsigned long cryptTable[0x500];

    unsigned long m_tablelength;    // 哈希索引表长度

    HASHTABLE *m_HashIndexTable;

/**
 * @Desc preProcess hash index table
 * */
    void InitCryptTable();

public:

/**
 * @Desc Get hash value;
 * */
    unsigned long HashString(const std::string &, unsigned long );

/**
 * @Desc hash a string;
 * @return true:success, false:fail
 * */
    bool Hash(std::string key, std::string value);

/**
 * @Desc Check if the string is hashed;
 * */
    std::string Hashed(std::string);

    StringHash(const long nTableLength = MAXTABLELEN);

    ~StringHash(void);
};

#endif //PEANUT_HASH_H
