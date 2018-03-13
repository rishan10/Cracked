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
#include "MyHash.h"
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
//    math32b.printHashTable();
}
