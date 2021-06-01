#ifndef BLOCK_H
#define BLOCK_H

#include "ecdsa/hash/Sha256.h"
#include "transaction.h"
#include <string>
#include <vector>

using namespace ::std;

class block
{
private:
    vector<transaction> transactions; //block数据区，包含多个transaction
    string previousHash;              //区块链上前驱block的hash值
    int timeStamp;                    //创建block的时间戳
    int random;                       //挖矿时为了使hash值变化使用的随机数，为了简便这里使用挖矿次数表示
    string hash;                      //block的hash值

public:
    block(vector<transaction> transactions, string previousHash);
    ~block();
    /*
     *  功能：计算block的hash值，使用sha256算法
     *  输入：无
     *  返回：当前block的hash值
    */
    string computeHash();
    /*
     *  功能：获取previousHash值
     *  输入：无
     *  返回：block的previousHash
    */
    string getPreviousHash();
    /*
     *  功能：获取hash值
     *  输入：无
     *  返回：block的hash
    */
    string getHash();
    /*
     *  功能：挖矿
     *  输入：当前问题难度
     *  返回：无
    */
    void mine(int difficulty);
    /*
     *  功能：验证block的transactions是否合法
     *  输入：无
     *  返回：true 合法 false 非法
    */
    bool validateTransactions();
};

#endif