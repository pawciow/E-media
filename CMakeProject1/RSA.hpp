//
// Created by pawci on 18.05.2019.
//

#ifndef CMAKEPROJECT1_RSA_HPP
#define CMAKEPROJECT1_RSA_HPP

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cmath>

// SOURCE FOR THIS FUNCTION: https://don.p4ge.me/modular-exponentiation/programming
int modExp(int b, int e, int m)
{
    int remainder;
    int x = 1;

    while (e != 0)
    {
        remainder = e % 2;
        e= e/2;

        if (remainder == 1)
            x = (x * b) % m;
        b= (b * b) % m; // New base equal b^2 % m
    }
    return x;
}

template <typename  T> class RSA
{
public:
    RSA() = delete;
    RSA(T numberToFind, std::string  Message) : _message{Message}
    {
        Erastotenes(numberToFind);
        p = *(primeNumbers.end() - 1);
//        q = *(primeNumbers.end() - 2);
        q = 53;
        std::cout << " p: " << p <<" q:  " << q;


        _publicKey.n = p*q;
        _privateKey.n = p*q;

        _totient = (p-1)*(q-1);
    }
    std::vector<T> Encrypt();
    void Decrypt(std::vector<T> encryptedMessage);
private:
    void Erastotenes(T numberToFind);
    std::vector<T> primeNumbers;

    /*Helpers in encryption*/
   std::string  _message;
    T p, q;
    T _totient;

    struct PublicKey{
        T n, e;
    };
    /*To count public key*/
    PublicKey _publicKey;
    void countPublicKey();
    bool isCoPrime(T a, T b);
    T greatestCommonDivisor(T a, T b);

    struct PrivateKey
    {
        T n, d;
    };
    PrivateKey _privateKey; // Public key is coprime to totient;
    void countPrivateKey();
    //k can be any arbitrary value
    T k = 2;

};


template <typename T>
T RSA<T>::greatestCommonDivisor(T a, T b)
{
    T x;
    while (b)
    {
        x = a % b;
        a = b;
        b = x;
    }
    return a;
}

template <typename T>
bool RSA<T>::isCoPrime(T a, T b)
{
    return (greatestCommonDivisor(a, b) == 1);
}

template <typename T>
void RSA<T>::countPublicKey()
{
    T tmp = 2;
    while (tmp < _totient)
    {
        if(isCoPrime(tmp,_totient))
        {
            _publicKey.e = tmp;
            break;
        } else
        {
            tmp++;
        }
    }
}

template <typename T>
void RSA<T>::countPrivateKey()
{
    _privateKey.d = (k*_totient + 1) / _publicKey.e;
}

template <typename T>
std::vector<T>RSA<T>::Encrypt()
{
    countPublicKey();
    countPrivateKey();
    std::cout << "\n Public key:  n: " << _publicKey.n << " e: " << _publicKey.e << std::endl;
    std::cout << "Private key:  n: " << _privateKey.n << " d: " <<  _privateKey.d << std::endl;

    std::vector<T> encryptedMessage;
    for(auto e : _message)
    {
        auto tmp = modExp(e,_publicKey.e,_publicKey.n);
        encryptedMessage.push_back(tmp);
    }

    std::cout << "Encrypted message: ";
    for(auto e: encryptedMessage)
        std::cout << e;
    return encryptedMessage;
}

template <typename T>
void RSA<T>::Decrypt(std::vector<T> encryptedMessage)
{
    std::cout << "\n Decrypted message: ";
    for(auto e: encryptedMessage)
    {
        auto tmp = modExp(e,_privateKey.d,_privateKey.n);
        std::cout  << (char)tmp;
    }

    std::cout <<  "\n And it should be: ";
    for(auto e : _message)
    {
        std::cout << e;
    }
}



template <typename T>
void RSA<T>::Erastotenes(T numberToFind)
{
    std::vector<T>  allNumbers(numberToFind-2);


    std::iota(allNumbers.begin(),allNumbers.end(),2);

    std::map<T,bool> isPrime;
    for(auto e: allNumbers)
        isPrime[e] = true;

    unsigned int threshold;
    threshold = static_cast<unsigned int> (sqrt((numberToFind)));


    for(unsigned int i = 2; i <= threshold; i++)
    {
        if(isPrime[i])
        {
            unsigned int w = i*i;
            while(w <= allNumbers.size()+1)
            {
                isPrime[w] = false;
                w+=i;
            }
        }
    }


    for(auto e: allNumbers)
    {
        if(isPrime[e])
        {
//            std::cout<<" " << e <<std::endl;
            primeNumbers.push_back((e));
        }
    }
}
#endif //CMAKEPROJECT1_RSA_HPP
