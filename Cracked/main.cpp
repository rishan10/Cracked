//#include "provided.h"
//#include <iostream>
//#include <string>
//#include <vector>
//#include <cstring>
//#include <cctype>
//#include <random>
//#include <algorithm>
//#include <numeric>
//#include <cassert> //make sure to remove later!
//#include "MyHash.h" //remove?
//using namespace std;
//
//const string WORDLIST_FILE = "/Users/rishangirish/Documents/Dev/cs32/Cracked/Cracked/wordlist.txt";
//
//string encrypt(string plaintext)
//{
//	  // Generate a to z
//    char plaintextAlphabet[26+1];
//	iota(plaintextAlphabet, plaintextAlphabet+26, 'a');
//	plaintextAlphabet[26] = '\0';
//
//	  // Generate permutation
//	string ciphertextAlphabet(plaintextAlphabet);
//	default_random_engine e((random_device()()));
//	shuffle(ciphertextAlphabet.begin(), ciphertextAlphabet.end(), e);
//
//	  // Run translator (opposite to the intended direction)
//	Translator t;
//	t.pushMapping(plaintextAlphabet, ciphertextAlphabet);
//	return t.getTranslation(plaintext);
//}
//
//bool decrypt(string ciphertext)
//{
//	Decrypter d;
//	if ( ! d.load(WORDLIST_FILE))
//	{
//		cout << "Unable to load word list file " << WORDLIST_FILE << endl;
//		return false;
//	}
//	for (const auto& s : d.crack(ciphertext))
//		cout << s << endl;
//	return true;
//}
//
//int main(int argc, char* argv[])
//{
////	if (argc == 3  &&  argv[1][0] == '-')
////	{
////		switch (tolower(argv[1][1]))
////		{
////		  case 'e':
////			cout << encrypt(argv[2]) << endl;
////			return 0;
////		  case 'd':
////			if (decrypt(argv[2]))
////				return 0;
////			return 1;
////		}
////	}
////
////	cout << "Usage to encrypt:  " << argv[0] << " -e \"Your message here.\"" << endl;
////	cout << "Usage to decrypt:  " << argv[0] << " -d \"Uwey tirrboi miyi.\"" << endl;
////	return 1;
//    
//    
//    //Decrypt Testing
//    Decrypter d;
//    d.load("/Users/rishangirish/Documents/Dev/cs32/Cracked/Cracked/wordlist.txt");
//    vector<string> sols = d.crack("y qook ra bdttook yqkook.");
//    vector<string>:: iterator it;
//    it = sols.begin();
//    
//    while(it != sols.end()) {
//        cout << *it << endl;
//        it++;
//    }
//  
//    //My hash testing:
////    MyHash<int, int> math32b;
////    math32b.associate(1, 1);
////    math32b.associate(31, 3);
////    math32b.associate(21, 4);
////    math32b.associate(72, 5);
////    math32b.associate(91, 6);
////    math32b.associate(81, 7);
////    math32b.associate(71, 8);
////    math32b.associate(61, 9);
////    math32b.associate(51, 10);
////    math32b.associate(41, 2);
////    math32b.associate(40, 17);
////    assert(*math32b.find(72) == 5);
////    assert(math32b.getNumItems() == 11);
////    assert(math32b.getLoadFactor() == 11.0/100.0);
//    //math32b.printHashTable();
//    
//    //Tokenizer testing...
////    Tokenizer t(" ,.!");
////    vector<string> v = t.tokenize("This,, is a test! It's the... best!");
////    // v now contains "This", "is", "a", "test", "It's", "the", and "best"
////    assert(v.size() == 7);
////    vector<string>::iterator it;
////    it = v.begin();
////    while(it != v.end()) {
////        cout << *it << endl;
////        it++;
////    }
////    string s = "!!!!!"; v = t.tokenize(s);
////    assert(v.size() == 0);
////    // v is now empty
//    
//    //Translate testing
////    Translator t;
////    string secret = "Hdqlx!";
////    string translated = t.getTranslation(secret);
////    cout << "The translated message is: " << translated;
////     //writes The translated message is: ?????!
//    
////    Translator t;
////    // Submit the mapping DàE, HàR, LàD
////    t.pushMapping("DHL", "ERD");
////    string secret = "Hdqlx!";
////    cout << t.getTranslation(secret) << endl; // writes Re?d?!
//    
////    Translator t;
////    // Submit the first collection of character mappings
////    t.pushMapping("DHL", "ERD"); // DàE, HàR, LàD
////    string secret = "Hdqlx!";
////    cout << t.getTranslation(secret) << endl; // writes Re?d?!
////    // Submit a second collection of character mappings
////    t.pushMapping("QX", "AY"); // QàA, XàY
////    
////    cout << t.getTranslation(secret) << endl; // writes Ready!
////    Translator t;
////    // Submit the first collection of mappings
////    t.pushMapping("DHL", "ERD"); // DàE, HàR, LàD
////    string secret = "Hdqlx!";
////    cout << t.getTranslation(secret) << endl; // writes Re?d?!
////    
////    // Submit a second collection of mappings
////    t.pushMapping("QX", "AY"); // QàA, XàY
////    
////    cout << t.getTranslation(secret) << endl; // writes Ready!
////    // Pop the most recently pushed collection
////    t.popMapping();
////    cout << t.getTranslation(secret) << endl; // writes Re?d?!
////    // Pop again
////    t.popMapping();
////    cout << t.getTranslation(secret) << endl; // writes ?????!
//    
////    Translator t;
////    t.pushMapping("DHL", "ERD"); // DàE, HàR, LàD
////    if ( ! t.pushMapping("QX", "RY")) // QàR, XàY
////        cout << "Both H and Q would map to R!" << endl;
////    // The current mapping is still DàE, HàR, LàD with no
////    // mapping for Q or X
////    cout << t.getTranslation("HDX") << endl; // writes RE?
////    if ( ! t.pushMapping("H", "S")) // HàS
////        cout << "H would map to both R and S!" << endl;
//    
//    
//        
////        WordList wl;
////        
////        if ( ! wl.loadWordList("/Users/rishangirish/Documents/Dev/cs32/Cracked/Cracked/wordlist.txt"))
////        {
////            cout << "Unable to load word list" << endl;
////            return 1;
////        }
////        
////        if (wl.contains("onomatopoeia"))
////            cout << "I found onomatopoeia!" << endl;
////        else
////            cout << "Onomatopoeia is not in the word list!" << endl;
////    
////        string cipher = "xyqbbq";
////        string decodedSoFar = "?r????";
////        vector<string> v = wl.findCandidates(cipher, decodedSoFar);
////    
////        if (v.empty())
////            cout << "No matches found" << endl;
////        else{
////            cout << "Found these matches:" << endl;
////            for (size_t k = 0; k < v.size(); k++)
////                cout << v[k] << endl; // writes grotto and troppo
////        }
//}
#include "provided.h"
#include "MyHash.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cassert>
using namespace std;

// **************************************************************
//
// CHANGE TO false THE VARIABLES CORRESPONDING TO CLASSES YOU ARE *NOT*
// YET READY TO TEST

const bool shouldTestMyHash = true;
const bool shouldTestTokenizer = true;
const bool shouldTestWordList = true;
const bool shouldTestTranslator = true;
const bool shouldTestDecrypter = true;

// **************************************************************

const char* FILENAME = "sanityfile";

void testMyHash();
void testTokenizer();
void testWordList();
void testTranslator();
void testDecrypter();
bool createWordListFile();

int main()
{
    if (shouldTestMyHash    ) { testMyHash();     cout << "Passed MyHash tests" << endl; }
    if (shouldTestTokenizer ) { testTokenizer();  cout << "Passed Tokenizer tests" << endl; }
    if (shouldTestWordList  ) { testWordList();   cout << "Passed WordList tests" << endl; }
    if (shouldTestTranslator) { testTranslator(); cout << "Passed Translator tests" << endl; }
    if (shouldTestDecrypter ) { testDecrypter();  cout << "Passed Decrypter tests" << endl; }
}

void testMyHash()
{
    MyHash<int, string> m;
    m.associate(222, "Ethel");
    m.associate(333, "Lucy");
    m.associate(111, "Fred");
    assert(m.getNumItems() == 3);
    assert(abs(m.getLoadFactor() - 0.03) < 0.00001);
    string* s = m.find(333);
    assert(s != nullptr  &&  *s == "Lucy");
    m.associate(333, "Ricky");
    assert(m.getNumItems() == 3);
    const MyHash<int, string>& cm = m;
    const string* cs = cm.find(333);
    assert(cs != nullptr  &&  *cs == "Ricky");
    int x = 1776;
    for (int k = 0; k < 1000; k++)
    {
        m.associate(x, "Carey");
        x += 1789;
    }
    assert(m.getNumItems() == 1003);
    double lf = m.getLoadFactor();
    assert(lf >= 0.5/2  &&  lf <= 0.5);
    m.reset();
    m.associate(444, "David");
    assert(m.getNumItems() == 1);
    assert(abs(m.getLoadFactor() - 0.01) < 0.00001);
}

void testTokenizer()
{
    Tokenizer t(".#");
    vector<string> v = t.tokenize("this.is##.#a#SILLY test#..");
    const char* expected[4] = { "this", "is", "a", "SILLY test" };
    assert(v.size() == 4  && equal(v.begin(), v.end(), expected));
}

void testWordList()
{
    if ( ! createWordListFile())
    {
        cout << "Cannot complete WordList test" << endl;
        exit(1);
    }
    WordList wl;
    assert(wl.loadWordList(FILENAME));
    assert(wl.contains("expel"));//expel
    assert(!wl.contains("extol"));
    vector<string> v = wl.findCandidates("wpxWv", "?x???");
    const char* expected[] = { "excel", "expel" };
    assert(v.size() == 2);
    for (auto& w : v)
        transform(w.begin(), w.end(), w.begin(), [](char c) { return tolower(c); });
    assert(equal(v.begin(), v.end(), expected) || equal(v.rbegin(), v.rend(), expected));
    v = wl.findCandidates("wpxwv", "?????");
    assert(v.size() == 4);
    v = wl.findCandidates("wpxwv", "?s??y");
    assert(v.size() == 0);
    remove(FILENAME);
}

void testTranslator()
{
    const char* q5bang = "?????" "!";  // Avoid trigraph
    Translator t;
    assert(t.getTranslation("Hdqlx!") == q5bang);
    assert( ! t.popMapping());
    assert(t.getTranslation("Hdqlx!") == q5bang);
    assert(t.pushMapping("dhL", "Erd"));
    assert(t.getTranslation("Hdqlx!") == "Re?d?!");
    assert( ! t.pushMapping("QX", "RY"));
    assert(t.getTranslation("Hdqlx!") == "Re?d?!");
    assert( ! t.pushMapping("H", "S"));
    assert(t.getTranslation("Hdqlx!") == "Re?d?!");
    assert(t.pushMapping("QX", "AY"));
    assert(t.getTranslation("Hdqlx!") == "Ready!");
    assert(t.popMapping());
    assert(t.getTranslation("Hdqlx!") == "Re?d?!");
    assert(t.popMapping());
    assert(t.getTranslation("Hdqlx!") == q5bang);
    assert( ! t.popMapping());
}

void testDecrypter()
{
    
    if ( ! createWordListFile())
    {
        cout << "Cannot complete Decrypter test" << endl;
        exit(1);
    }
    Decrypter d;
    assert(d.load(FILENAME));
    
    vector<string> v = d.crack("smxsdg SGOSDG gfvgx!!");
    const char* expected[] = {
        "ablate AERATE excel!!",
        "ablate AERATE expel!!",
        "purple PEOPLE eater!!",
        "purple PEOPLE ether!!"
    };
    assert(v.size() == 4  &&  equal(v.begin(), v.end(), expected));
    assert(d.crack("smxsdg SGOSDG gfvgy!!").empty());
    
    remove(FILENAME);
}

bool createWordListFile()
{
    ofstream ofs(FILENAME);
    if ( ! ofs)
    {
        cout << "Cannot create word list file named " << FILENAME << endl;
        return false;
    }
    const char* words[] = {
        "people", "aerate", "ether", "essay", "eater",
        "excel", "Expel", "ablate", "purple"
    };
    for (auto w : words)
        ofs << w << endl;
    return true;
}

