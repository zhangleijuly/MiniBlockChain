#ifndef CHAIN_H
#define CHAIN_H

#include "block.h"
#include <vector>

using namespace ::std;

class chain
{
private:
    vector<block *> blocks;              //区块链上的所有blocks
    vector<transaction> transactionPool; //区块链上的所有transactions
    int minerReward;                     //矿工奖励
    int difficulty;                      //当前问题难度

public:
    chain(int difficulty = 0);
    ~chain();
    /*
     *  功能：添加一个transaction到区块链
     *  输入：待添加transaction
     *  返回：无
    */
    void addTransaction(transaction t);
    /*
     *  功能：获取最后一个block的hash值
     *  输入：无
     *  返回：最后一个block的hash值
    */
    string getLastBlockHash();
    /*
     *  功能：挖transactionPool
     *  输入：矿工公钥
     *  返回：无
    */
    void mineTransationPool(string miner);
    /*
     *  功能：获取区块链上的一个block
     *  输入：block编号
     *  返回：block指针
    */
    block *getBlock(int id);
    /*
     *  功能：验证区块链是否合法
     *  输入：无
     *  返回：true 合法 false 非法
    */
    bool validateChain();
    /*
     *  功能：获取区块链长度
     *  输入：无
     *  返回：区块链长度
    */
    int size();
};

#endif