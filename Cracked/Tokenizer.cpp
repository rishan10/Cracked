#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const string& s) const;
private:
    string m_separators;
    bool isSeparator(char ch) const;
};

TokenizerImpl::TokenizerImpl(string separators)
{
    m_separators = separators;
}

vector<string> TokenizerImpl::tokenize(const string& s) const
{
    vector<string> words;
    string word = "";
    int i = 0;
    bool hitASeparator = false;
    while(i < s.size()) {
        if(isSeparator(s[i])) {
            hitASeparator = true;
            if(word != "") words.push_back(word);
            word = "";
        }else{
            word += s[i];
            hitASeparator = false;
        }
            
        i++;
    }
    
    if(!hitASeparator) words.push_back(word);
    
    return words;  // This compiles, but may not be correct
}

bool TokenizerImpl::isSeparator(char ch) const {
    for(int i = 0; i < m_separators.size(); i++) {
        if(ch == m_separators[i]) {
            return true;
        }
    }
    
    return false;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const string& s) const
{
    return m_impl->tokenize(s);
}
