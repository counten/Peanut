/*
* Author: wbq813 2018/01/25
* Env: debian 9, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_QUERYRESULT_H
#define MNSERVER_QUERYRESULT_H

#include <iostream>
#include <vector>

/**
 * @Desc QueryResult class
 * */
class QueryResult
{

private:

    std::vector<std::vector<std::string>> string_table;

public:

    /**
     * @return Row size;
     * */
    int getRowCount();

    /**
     * @return Column size;
     * */
    int getColumnCount();

    /**
     * @param row, column
     * @return Item map to row and column
     * */
    std::string getElement(int row, int column);

    /**
     * @param row
     * @return Item map to row
     * */
    std::vector<std::string> getRow(int row);


    /**
     * @Desc add a row
     * */
    void addRow(const std::vector<std::string> &row);

    /**
     * @return format str
     * */
    std::string getResultStr();

    std::vector<std::vector<std::string>> getResult();

};

#endif //MNSERVER_QUERYRESULT_H
