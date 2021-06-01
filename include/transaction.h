#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "ecdsa/hash/Sha256.h"
#include <string>

using namespace ::std;

class transaction
{
private:
    string src;          //付款者公钥
    string dst;          //收款者公钥
    unsigned int amount; //转账金额
    string signature;    //付款者数字签名

public:
    transaction(string src, string dst, unsigned int amount);
    ~transaction();
    /*
     *  功能：将transaction转换为string
     *  输入：无
     *  返回：转换后的string
    */
    string toString();
    /*
     *  功能：计算transaction的hash值，使用sha256算法
     *  输入：无
     *  返回：transaction的hash值
    */
    string computeHash();
    /*
     *  功能：给transaction添加数字签名
     *  输入：签名者的私钥
     *  返回：无
    */
    void sign(string privateKey);
    string computeHash();
    /*
     *  功能：验证transaction是否合法
     *  输入：无
     *  返回：true 合法 false 非法
    */
    bool validateTransaction();
};

#endif