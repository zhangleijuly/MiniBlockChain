#include "chain.h"
#include <iostream>

chain::chain(int difficulty)
{
    blocks.clear();
    transactionPool.clear();
    this->minerReward = 50;
    this->difficulty = difficulty;
}

chain::~chain()
{
}

void chain::addTransaction(transaction t)
{
    if (t.validateTransaction())
    {
        transactionPool.push_back(t);
    }
    else
    {
        cout << "Warning, adding an invalid transaction to transaction pool." << endl;
    }
}

string chain::getLastBlockHash()
{
    string res;
    if (!blocks.empty())
    {
        block *lastBlock = blocks[blocks.size() - 1];
        res = lastBlock->getHash();
    }
    return res;
}

void chain::mineTransationPool(string miner)
{
    //首先添加系统给矿工的奖励到transactionPool
    transaction minerRewardTransaction("", miner, this->minerReward);
    this->transactionPool.push_back(minerRewardTransaction);

    //从transactionPool取出transactions作为block数据区内容
    //为了简便这里直接使用整个transactionPool
    block *newBlock = new block(this->transactionPool, this->getLastBlockHash());
    //挖矿
    newBlock->mine(this->difficulty);

    //挖矿成功后将新block加入区块链，并清空transactionPool
    blocks.push_back(newBlock);
    transactionPool.clear();
}

block *chain::getBlock(int id)
{
    if (id < blocks.size())
    {
        return blocks[id];
    }
    else
    {
        return nullptr;
    }
}

bool chain::validateChain()
{
    if (blocks.empty())
    {
        return true;
    }
    else
    {
        for (int i = 0; i < blocks.size(); ++i)
        {
            //检查block的transactions是否合法
            if (!blocks[i]->validateTransactions())
            {
                cout << "Invalid transaction found in block " << i << endl;
                return false;
            }
            //检查block的数据是否被篡改
            if (blocks[i]->getHash() != blocks[i]->computeHash())
            {
                cout << "The data of block " << i << " has been changed!" << endl;
                return false;
            }
            //检查区块链是否断裂
            if (i)
            {
                if (blocks[i]->getPreviousHash() != blocks[i - 1]->getHash())
                {
                    cout << "Block " << i - 1 << " and block " << i << " has disconnected!";
                    return false;
                }
            }
        }
        return true;
    }
}

int chain::size()
{
    return blocks.size();
}