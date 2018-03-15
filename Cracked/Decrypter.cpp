#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class DecrypterImpl
{
public:
    DecrypterImpl();
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
    WordList wl;
    Tokenizer t;
    Translator trans;
    string pickLongestUntranslatedWord(vector<string> v);
    void crackHelper(const string& ciphertext_message, vector<string>& output);
    bool checkTranslatedWordsInList(vector<string> translation);
    bool completelyTranslated(string s);
    bool allCompletelyTranslatedWordsFound(vector<string> words);
};

bool DecrypterImpl:: completelyTranslated(string s) {
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '?') return false;
    }
    
    return true;
}

bool DecrypterImpl:: allCompletelyTranslatedWordsFound(vector<string> words) {
    vector<string>:: iterator it;
    it = words.begin();
    while(it != words.end()) {
        string w = *it;
        if(completelyTranslated(w) && !wl.contains(w)) return false;
        it++;
    }
    return true;
}

bool DecrypterImpl::checkTranslatedWordsInList(vector<string> translation) {
    vector<string>:: iterator it;
    it = translation.begin();
    while(it != translation.end()) {
        string word = *it;
        bool fullyTranslated = true;
        for(int i = 0; i < word.size(); i++) {
            if(word[i] == '?') {
                fullyTranslated = false;
                break;
            }
        }
        if(fullyTranslated) {
            if(!wl.contains(word)) {
                return false;
            }
        }
        it++;
    }
    
    return true;
}

string DecrypterImpl::pickLongestUntranslatedWord(vector<string> v) {
    vector<string>:: iterator it;
    it = v.begin();
    string maxWord = *it;
    int count = 0;
    int maxCount = 0;
    while(it != v.end()) {
        string ww = *it;
        string w = trans.getTranslation(ww);
        for(int i = 0; i < w.size(); i++) {
            if(w[i] == '?') {
                count++;
            }
        }
        if(count > maxCount) {
            maxWord = ww;
            maxCount = count;
        }
        count = 0;
        it++;
    }
    
    return maxWord;
}

DecrypterImpl::DecrypterImpl(): t(",;:.!()[]{}-\"#$%^& 0123456789") {
    
}

bool DecrypterImpl::load(string filename)
{
    return wl.loadWordList(filename);
}

void DecrypterImpl::crackHelper(const string& ciphertext_message, vector<string>& output) {
    if(!checkTranslatedWordsInList(t.tokenize(trans.getTranslation(ciphertext_message)))) {
        //there is at least one fully translated word that is not in the word list
        //pop the current translation map
        trans.popMapping();
        return;
    }
    
    vector<string> cipherTextVector = t.tokenize(ciphertext_message); //tokenize message
    string longestUntranslated = pickLongestUntranslatedWord(cipherTextVector); // pick longest unused, untranslated word
    string translatedWord = trans.getTranslation(longestUntranslated);
    vector<string> candidates = wl.findCandidates(longestUntranslated, translatedWord);
    if(candidates.empty()) {
        //if there are no possible candidates, then mapping must be wrong
        //throw it away and return to previous call
        trans.popMapping();
        return;
        
    }
    
    vector<string>:: iterator candidateIterator;
    candidateIterator = candidates.begin();
    while(candidateIterator != candidates.end()) {
        trans.pushMapping(longestUntranslated, *candidateIterator);
        
        //translate entire ciphertext into proposed plain text
        string proposedPlainText = trans.getTranslation(ciphertext_message);
        if(!checkTranslatedWordsInList(t.tokenize(proposedPlainText))) {
            //there is at least one fully translated word that is not in the word list
            //pop the current translation map
            trans.popMapping();
            candidateIterator++;
            continue;
        }
        //continue codes here...
        if(allCompletelyTranslatedWordsFound(t.tokenize(proposedPlainText))) {
            if(completelyTranslated(proposedPlainText)) {
                output.push_back(proposedPlainText);
                trans.popMapping();
                candidateIterator++;
                continue;
            }else{
                //do we really need to push the mapping?
                crackHelper(ciphertext_message, output);
                 //do we really need this?
            }
        }
        
        candidateIterator++;
    }
    
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    vector<string> solutions;
    crackHelper(ciphertext, solutions);
    sort(solutions.begin(), solutions.end());
    return solutions;
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
