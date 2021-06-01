#include "block.h"
#include <sstream>
#include <iostream>
#include <time.h>

using namespace ::std;

block::block(vector<transaction> transactions, string previousHash)
{
    this->transactions = transactions;
    this->previousHash = previousHash;
    this->timeStamp = (int)time(nullptr);
    this->random = 0;
    this->hash = computeHash();
}

block::~block()
{
}

string block::computeHash()
{
    string temp;
    for (int i = 0; i < this->transactions.size(); ++i)
    {
        temp += this->transactions[i].toString();
    }
    temp += this->getPreviousHash();
    stringstream ss;
    ss << this->timeStamp << this->random;
    temp += ss.str();
    return sha256(temp);
}

string block::getPreviousHash()
{
    return this->previousHash;
}

string block::getHash()
{
    return this->hash;
}

void block::mine(int difficulty)
{
    //如果transactions非法则停止挖矿
    if (!this->validateTransactions())
    {
        cout << "Invalid transaction found, stop mining." << endl;
        return;
    }
    string pattern(difficulty, '0');
    while (true)
    {
        string hash = this->computeHash();
        if (hash.substr(0, difficulty) == pattern)
        {
            this->hash = this->computeHash();
            break;
        }
        else
        {
            this->random++;
        }
    }
    cout << "Success! Mining " << this->random << " time(s), the final hash is" << endl;
    cout << this->hash << endl;
}

bool block::validateTransactions()
{
    for (auto t : transactions)
    {
        if (!t.validateTransaction())
        {
            cout << "Invalid transaction found in transactions." << endl;
            return false;
        }
    }
    return true;
}