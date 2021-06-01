#include "transaction.h"
#include "ecdsa/Ecdsa.h"
#include <sstream>
#include <iostream>

using namespace ::std;

transaction::transaction(string src, string dst, unsigned int amount)
{
    this->src = src;
    this->dst = dst;
    this->amount = amount;
}

transaction::~transaction()
{
}

string transaction::toString()
{
    string res = this->src;
    res += this->dst;
    stringstream ss;
    ss << this->amount;
    res += ss.str();
    return res;
}

string transaction::computeHash()
{
    return sha256(this->toString());
}

void transaction::sign(string privateKey)
{
    string hashValue = this->computeHash();
    this->signature = Ecdsa::sign(privateKey, hashValue);
}

bool transaction::validateTransaction()
{
    string publicKey = this->src;
    //如果付款者公钥为空，说明是系统发放
    if (publicKey.empty())
    {
        return true;
    }
    //如果付款者公钥非空，就必须有数字签名
    if (this->signature.empty())
    {
        cout << "Signature is missing!" << endl;
        return false;
    }
    string hashValue = this->computeHash();
    return Ecdsa::verify(publicKey, hashValue, this->signature);
}