#include "provided.h"
#include <string>
#include <unordered_map>
#include <list>
//#include <iostream> //remove later!
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    unordered_map<char, char> cipherToPlain;
    unordered_map<char, char> plainToCipher;
    list<unordered_map<char, char>> historyOfMappings; //represents our stack
    int m_npopped;
    int m_npushed;
    
};

TranslatorImpl::TranslatorImpl() {
    for(char ch = 'A'; ch <= 'Z'; ch++) {
        cipherToPlain.insert(pair<char,char>(ch, '?'));
    }
    //do we need to push this into the "stack"
    m_npopped = 0;
    m_npushed = 0;
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    //if parameters are not the same length
    if(ciphertext.size() != plaintext.size()) return false;
    //if either contains a non-letter:
    for(int i = 0; i < ciphertext.size(); i++) {
        if(!isalpha(ciphertext[i])) {
            return false;
        }
    }
    //inconsistent character mappings
    //a ciphertext letter cannot map to two or more plaintext letters
    //two or more ciphertext letters cannot map to the same plaintext letter
    for(int i = 0; i < ciphertext.size(); i++) {
        if(cipherToPlain.find(toupper(ciphertext[i]))->second != '?' && cipherToPlain.find(toupper(ciphertext[i]))->second != toupper(plaintext[i])) {
            return false;
        }
        
        if(plainToCipher.find(toupper(plaintext[i])) != plainToCipher.end() && plainToCipher.find(toupper(plaintext[i]))->second != toupper(ciphertext[i])) {
            return false;
        }
    }
    m_npushed++;
    //push a copy to the list
    unordered_map<char, char> cipherToPlainCopy = cipherToPlain;
    
    
    
    historyOfMappings.push_back(cipherToPlainCopy);
    
    //update the mapping
    for(int i = 0; i < ciphertext.size(); i++) {
        cipherToPlain.find(toupper(ciphertext[i]))->second = toupper(plaintext[i]);
        
        plainToCipher.insert(pair<char, char>(toupper(plaintext[i]), toupper(ciphertext[i])));
    }
    
    return true;  // This compiles, but may  be correct
}

bool TranslatorImpl::popMapping()
{
    if(m_npushed == m_npopped) return false;
    m_npopped++;
    
    unordered_map<char, char> mostRecentMapping = historyOfMappings.back();
    historyOfMappings.pop_back();
    
    cipherToPlain = mostRecentMapping;
    
    unordered_map<char, char> x;
    
    for(char ch = 'A'; ch <= 'Z'; ch++) {
        if(cipherToPlain.find(ch)->second != '?') {
            x.insert(pair<char,char>(cipherToPlain.find(ch)->second, ch));
        }
    }
    
    plainToCipher = x;
    
    
    return true;  // This compiles, but may  be correct
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string plainText = "";
    for(int i = 0; i < ciphertext.size(); i++) {
        if(isalpha(ciphertext[i])) {
            int cipherCh = ciphertext[i];
            int plainCh = cipherToPlain.find(toupper(cipherCh))->second;
            if(plainCh == '?') {
                plainText += '?';
                continue;
            }
            if(isupper(cipherCh)) {
                plainText += plainCh;
            }else{
                plainText += tolower(plainCh);
            }
        }else{
            plainText += ciphertext[i];
        }
    }
    return plainText; // This compiles, but may not be correct
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
