#include "provided.h"
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include "MyHash.h"
using namespace std;

class WordListImpl
{
public:
    WordListImpl();
    ~WordListImpl();
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
    
private:
    MyHash<string, vector<string>>* words;
    string getPattern(string word) const;
    bool isWord(string word) const;
    bool isWord(string word, char extraChar) const;
    string allLowercase(string word) const;
    
};



WordListImpl::WordListImpl() {
    words = new MyHash<string, vector<string>>;
}

WordListImpl::~WordListImpl() {
    delete words;
}

bool WordListImpl::isWord(string word) const{
    for(int i = 0; i < word.size(); i++) {
        if(word[i] != 39 && !isalpha(word[i]))
            return false;
    }
    
    return true;
}

bool WordListImpl::isWord(string word, char extraChar) const{
    for(int i = 0; i < word.size(); i++) {
        if(word[i] != 39 && !isalpha(word[i]) && word[i] != extraChar)
            return false;
    }
    
    return true;
}

string WordListImpl:: allLowercase(string word) const {
    string res = "";
    for(int i = 0; i < word.size(); i++) {
        res += tolower(word[i]);
    }
    return res;
}

bool WordListImpl::loadWordList(string filename)
{
    //must load words from list into data structures
    //must discard data structures and start fresh
    words->reset();
    ifstream infile(filename);    // infile is a name of our choosing
    if (!infile)		        // Did opening the file fail?
    {
        return false;
    }
    
    string word = "";
    while(getline(infile, word)) {
        //grabs word from the text file
        if(isWord(word)) {
            string pattern = getPattern(word);
            cout << pattern << endl;
            if(words->find(pattern) == nullptr) {
                //if pattern is new
                vector<string> v;
                v.push_back(word);
                //cout << pattern << endl;
                words->associate(pattern, v); //now pattern is added with the vector
            }else{
                //if pattern is already there
                words->find(pattern)->push_back(word);
            }
        }
    }
    
    infile.close();
    return true;  // This compiles, but may  be correct
}

bool WordListImpl::contains(string word) const
{
    string pattern = getPattern(word);
    if(words->find(pattern) == nullptr) {
        return false;
    }else{
        vector<string> v = *words->find(pattern);
        vector<string>:: iterator it;
        it = v.begin();
        while(it != v.end()) {
            //convert to lowecase
            string inspect = allLowercase(*it);
            string w = allLowercase(word);
            if(w == inspect) return true;
            it++;
        }
    }
    
    return false; // This compiles, but may  be correct
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    vector<string> candidates;
    if(isWord(cipherWord) && isWord(currTranslation, '?') && currTranslation.size() == cipherWord.size()) {
        string pattern  = getPattern(cipherWord);
        vector<string>* v = words->find(pattern);
        if(v == nullptr) return vector<string>();
        vector<string>:: iterator it;
        it = v->begin();
        while(it != v->end()) {
            string w = *it;
            for(int i = 0; i < currTranslation.size(); i++) {
                char ct = currTranslation[i];
                if(isalpha(ct)) {
                    //if it is a letter, then w[i] just also be the same letter
                    char ct1 = tolower(ct);
                    char cp = tolower(w[i]);
                    if(cp != ct1)
                        break; //current word is not a right candidate
                    if(!isalpha(cipherWord[i])) return vector<string>(); //if ciphertext is not alpha return mt
                        
                }else if(ct == '?'){
                    //if it is a ?
                    if(!isalpha(w[i]))
                        break; //current word is not a right candidate
                    if(!isalpha(cipherWord[i])) return vector<string>(); //if ciphertext is not alpha return mt
                }else if(ct == 39) {
                    //if an apostrophe
                    if(w[i] != 39)
                        break; //current word is not a right candidate
                    if(cipherWord[i] != 39) return vector<string>(); //if ciphertext is not apostrfe, return mt
                }
            }
            candidates.push_back(w); //w is a right candidate
            it++;
        }
        return candidates;
    }else{
        return vector<string>();
    }
      // This compiles, but may not be correct
}

string WordListImpl::getPattern(string word) const {
    string pattern = "";
    char index = 'A';
    MyHash<char, char> charMap;
    for(int i = 0; i < word.size(); i++) {
        if(charMap.find(word[i]) == nullptr) {
            //character is distinct since we havent added it before
            pattern += index; //add new mapping
            charMap.associate(word[i], index); //push mapping
            index++; //change mapping
        }else{
            //character is not distinct...we added it before
            //need to get old mapping
            char oldMapping = *charMap.find(word[i]);
            pattern += oldMapping; //add to pattern
        }
    }
    return pattern;
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}
