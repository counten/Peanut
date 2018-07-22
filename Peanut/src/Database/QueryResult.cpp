/*
* Author: wbq813 2018/01/25
* Env: debian 9, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include "QueryResult.h"


int QueryResult::getRowCount()
{
    return string_table.size();
}


int QueryResult::getColumnCount()
{
    return string_table[0].size();
};


std::string QueryResult::getElement(int row, int column)
{
    return string_table[row][column];
}


void QueryResult::addRow(const std::vector<std::string> &row)
{
    string_table.push_back(row);
}


std::string QueryResult::getResultStr()
{
    std::string result = "";
    int row = getRowCount();
    int column = getColumnCount();

    for(int i = 0; i < row; i++)
    {
        for(int j  = 0; j < column; j ++)
        {
            result.append(string_table[i][j]);
            result.append("\t");
        }
        result.append("\r\n");
    }
    return result;
}

std::vector<std::string> QueryResult::getRow(int row) {
    return string_table[row];
}

std::vector<std::vector<std::string>> QueryResult::getResult(){
    return string_table;
}

