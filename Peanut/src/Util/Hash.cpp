/*
* Author: wbq813 2018/3/20
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn 
*/

#include "Hash.h"

StringHash::StringHash(const long nTableLength /*= MAXTABLELEN*/)
{
    InitCryptTable();
    m_tablelength = (unsigned long) nTableLength;
    // Init hash table
    m_HashIndexTable = new HASHTABLE[nTableLength];
    for (int i = 0; i < nTableLength; i++)
    {
        m_HashIndexTable[i].nHashA = -1;
        m_HashIndexTable[i].nHashB = -1;
        m_HashIndexTable[i].bExists = false;
        m_HashIndexTable[i].value = "";
    }
}

StringHash::~StringHash()
{
    // Clean memory
    if (nullptr != m_HashIndexTable)
    {
        delete[]m_HashIndexTable;
        m_HashIndexTable = nullptr;
        m_tablelength = 0;
    }
}


/**
 * @Desc preProcess hash index table
 * */
void StringHash::InitCryptTable()
{
    unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;

    for (index1 = 0; index1 < 0x100; index1++)
    {
        for (index2 = index1, i = 0; i < 5; i++, index2 += 0x100)
        {
            unsigned long temp1, temp2;
            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp1 = (seed & 0xFFFF) << 0x10;
            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp2 = (seed & 0xFFFF);
            cryptTable[index2] = (temp1 | temp2);
        }
    }
}

/**
 * @Desc Get hash value;
 * */
unsigned long StringHash::HashString(const std::string &lpszString, unsigned long dwHashType)
{
    auto *key = (unsigned char *) (const_cast<char *>(lpszString.c_str()));
    unsigned long seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;
    int ch;

    while (*key != 0)
    {
        ch = toupper(*key++);

        seed1 = cryptTable[(dwHashType << 8) + ch] ^ (seed1 + seed2);
        seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
    }
    return seed1;
}


/**
 * @Desc Check if the string is hashed;
 * */
std::string StringHash::Hashed(std::string key)
{
    const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
    // Three hash to avoid conflict
    unsigned long nHash = HashString(key, HASH_OFFSET);
    unsigned long nHashA = HashString(key, HASH_A);
    unsigned long nHashB = HashString(key, HASH_B);
    unsigned long nHashStart = nHash % m_tablelength,
            nHashPos = nHashStart;

    while (m_HashIndexTable[nHashPos].bExists)
    {
        if (m_HashIndexTable[nHashPos].nHashA == nHashA && m_HashIndexTable[nHashPos].nHashB == nHashB)
        {
            return m_HashIndexTable[nHashPos].value;
        }
        else
        {
            nHashPos = (nHashPos + 1) % m_tablelength;
        }

        if (nHashPos == nHashStart)
        {
            break;
        }
    }

    return "-1";
}


/**
 * @Desc hash a string;
 * @return true:success, false:fail
 * */
bool StringHash::Hash(std::string key, std::string value)
{
    const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
    unsigned long nHash = HashString(key, HASH_OFFSET);
    unsigned long nHashA = HashString(key, HASH_A);
    unsigned long nHashB = HashString(key, HASH_B);
    unsigned long nHashStart = nHash % m_tablelength,
            nHashPos = nHashStart;

    while (m_HashIndexTable[nHashPos].bExists)
    {
        nHashPos = (nHashPos + 1) % m_tablelength;
        if (nHashPos == nHashStart)
        {
            // There is no space in hash table
            return false;
        }
    }
    m_HashIndexTable[nHashPos].bExists = true;
    m_HashIndexTable[nHashPos].nHashA = nHashA;
    m_HashIndexTable[nHashPos].nHashB = nHashB;
    m_HashIndexTable[nHashPos].value = value;
    return true;
}
