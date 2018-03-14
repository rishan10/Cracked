#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include <random>
#include <algorithm>
#include <numeric>
#include <cassert> //make sure to remove later!
#include "MyHash.h" //remove?
using namespace std;

const string WORDLIST_FILE = "wordlist.txt";

string encrypt(string plaintext)
{
	  // Generate a to z
    char plaintextAlphabet[26+1];
	iota(plaintextAlphabet, plaintextAlphabet+26, 'a');
	plaintextAlphabet[26] = '\0';

	  // Generate permutation
	string ciphertextAlphabet(plaintextAlphabet);
	default_random_engine e((random_device()()));
	shuffle(ciphertextAlphabet.begin(), ciphertextAlphabet.end(), e);

	  // Run translator (opposite to the intended direction)
	Translator t;
	t.pushMapping(plaintextAlphabet, ciphertextAlphabet);
	return t.getTranslation(plaintext);
}

bool decrypt(string ciphertext)
{
	Decrypter d;
	if ( ! d.load(WORDLIST_FILE))
	{
		cout << "Unable to load word list file " << WORDLIST_FILE << endl;
		return false;
	}
	for (const auto& s : d.crack(ciphertext))
		cout << s << endl;
	return true;
}

int main(int argc, char* argv[])
{
//	if (argc == 3  &&  argv[1][0] == '-')
//	{
//		switch (tolower(argv[1][1]))
//		{
//		  case 'e':
//			cout << encrypt(argv[2]) << endl;
//			return 0;
//		  case 'd':
//			if (decrypt(argv[2]))
//				return 0;
//			return 1;
//		}
//	}
//
//	cout << "Usage to encrypt:  " << argv[0] << " -e \"Your message here.\"" << endl;
//	cout << "Usage to decrypt:  " << argv[0] << " -d \"Uwey tirrboi miyi.\"" << endl;
//	return 1;
  
    //My hash testing:
//    MyHash<int, int> math32b;
//    math32b.associate(1, 1);
//    math32b.associate(31, 3);
//    math32b.associate(21, 4);
//    math32b.associate(72, 5);
//    math32b.associate(91, 6);
//    math32b.associate(81, 7);
//    math32b.associate(71, 8);
//    math32b.associate(61, 9);
//    math32b.associate(51, 10);
//    math32b.associate(41, 2);
//    math32b.associate(40, 17);
//    assert(*math32b.find(72) == 5);
//    assert(math32b.getNumItems() == 11);
//    assert(math32b.getLoadFactor() == 11.0/100.0);
    //math32b.printHashTable();
    
    //Tokenizer testing...
//    Tokenizer t(" ,.!");
//    vector<string> v = t.tokenize("This,, is a test! It's the... best!");
//    // v now contains "This", "is", "a", "test", "It's", "the", and "best"
//    assert(v.size() == 7);
//    vector<string>::iterator it;
//    it = v.begin();
//    while(it != v.end()) {
//        cout << *it << endl;
//        it++;
//    }
//    string s = "!!!!!"; v = t.tokenize(s);
//    assert(v.size() == 0);
//    // v is now empty
    
    //Translate testing
//    Translator t;
//    string secret = "Hdqlx!";
//    string translated = t.getTranslation(secret);
//    cout << "The translated message is: " << translated;
//     //writes The translated message is: ?????!
    
//    Translator t;
//    // Submit the mapping DàE, HàR, LàD
//    t.pushMapping("DHL", "ERD");
//    string secret = "Hdqlx!";
//    cout << t.getTranslation(secret) << endl; // writes Re?d?!
    
//    Translator t;
//    // Submit the first collection of character mappings
//    t.pushMapping("DHL", "ERD"); // DàE, HàR, LàD
//    string secret = "Hdqlx!";
//    cout << t.getTranslation(secret) << endl; // writes Re?d?!
//    // Submit a second collection of character mappings
//    t.pushMapping("QX", "AY"); // QàA, XàY
//    
//    cout << t.getTranslation(secret) << endl; // writes Ready!
//    Translator t;
//    // Submit the first collection of mappings
//    t.pushMapping("DHL", "ERD"); // DàE, HàR, LàD
//    string secret = "Hdqlx!";
//    cout << t.getTranslation(secret) << endl; // writes Re?d?!
//    
//    // Submit a second collection of mappings
//    t.pushMapping("QX", "AY"); // QàA, XàY
//    
//    cout << t.getTranslation(secret) << endl; // writes Ready!
//    // Pop the most recently pushed collection
//    t.popMapping();
//    cout << t.getTranslation(secret) << endl; // writes Re?d?!
//    // Pop again
//    t.popMapping();
//    cout << t.getTranslation(secret) << endl; // writes ?????!
    
//    Translator t;
//    t.pushMapping("DHL", "ERD"); // DàE, HàR, LàD
//    if ( ! t.pushMapping("QX", "RY")) // QàR, XàY
//        cout << "Both H and Q would map to R!" << endl;
//    // The current mapping is still DàE, HàR, LàD with no
//    // mapping for Q or X
//    cout << t.getTranslation("HDX") << endl; // writes RE?
//    if ( ! t.pushMapping("H", "S")) // HàS
//        cout << "H would map to both R and S!" << endl;
    
    
        
        WordList wl;
        
        if ( ! wl.loadWordList("/Users/rishangirish/Documents/Dev/cs32/Cracked/Cracked/wordlist.txt"))
        {
            cout << "Unable to load word list" << endl;
            return 1;
        }
        
        if (wl.contains("onomatopoeia"))
            cout << "I found onomatopoeia!" << endl;
        else
            cout << "Onomatopoeia is not in the word list!" << endl;
    
        string cipher = "xyqbbq";
        string decodedSoFar = "?r????";
        vector<string> v = wl.findCandidates(cipher, decodedSoFar);
    
        if (v.empty())
            cout << "No matches found" << endl;
        else{
            cout << "Found these matches:" << endl;
            for (size_t k = 0; k < v.size(); k++)
                cout << v[k] << endl; // writes grotto and troppo
        }
}
