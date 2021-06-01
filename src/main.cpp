#include "chain.h"
#include "ecdsa/Ecdsa.h"
#include <iostream>
#include <random>
#include <unordered_map>

using namespace ::std;

//随机生成64位16进制私钥
string generatePrivateKey()
{
    string hex = "0123456789ABCDEF";
    string res;
    res.clear();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 15);
    for (int i = 0; i < 64; ++i)
    {
        int random = dis(gen);
        res.push_back(hex[random]);
    }
    return res;
}

int main()
{
    //储存所有用户的私钥，单机版使用，联网用户私钥应仅储存在本地
    unordered_map<string, string> privateKeys;

    //创建区块链并为用户生成私钥
    chain coinChain(3);
    string userName = "Artemis";
    string privateKey;
    if (privateKeys.count(userName))
    {
        privateKey = privateKeys[userName];
    }
    else
    {
        privateKey = generatePrivateKey();
        cout << "key1:" << privateKey << endl;
        privateKeys[userName] = privateKey;
    }
    userName = "Zeus";
    if (privateKeys.count(userName))
    {
        privateKey = privateKeys[userName];
    }
    else
    {
        privateKey = generatePrivateKey();
        cout << "key2:" << privateKey << endl;
        privateKeys[userName] = privateKey;
    }

    //用私钥生成公钥
    string publicKeySender = Ecdsa::privateKeyToPublicKeyHex(privateKeys["Artemis"]);
    string publicKeyReceiver = Ecdsa::privateKeyToPublicKeyHex(privateKeys["Zeus"]);
    string publicKeyMiner = Ecdsa::privateKeyToPublicKeyHex(privateKeys["Artemis"]);
    //用公钥创建transaction
    transaction t1(publicKeySender, publicKeyReceiver, 100);
    //用私钥给transaction添加数字签名
    t1.sign(privateKeys["Artemis"]);
    //将transaction添加到区块链并挖矿
    coinChain.addTransaction(t1);
    coinChain.mineTransationPool(publicKeyMiner);

    //查看挖矿结果并验证区块链合法性
    for (int i = 0; i < coinChain.size(); ++i)
    {
        block *b = coinChain.getBlock(i);
        cout << b->getHash() << endl;
    }
    cout << coinChain.validateChain() << endl;
    return 0;
}