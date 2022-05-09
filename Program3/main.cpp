//Author: Cody Chinothai
//San Diego State university
// CS210/496: Data Structures
//
// Password Generator: Reads text file input and uses data structures to formulate twenty
// passwords that includes spaces and words that are easy to memorize while also being
// protected against brute forcing.

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;
vector<string> words; //adds the words from raw input
std::vector<string> validWords; //takes from words vector the words that meet requirements
std::set<string> setOfUniqueWords;

//check for words with non-alphabetical characters
//check for words that meet minimum length requirements
//then: add them into a set (removes duplicates)
void format(string word) {
    bool nonAlphabetical = find_if(word.begin(), word.end(),
                                   not1(ptr_fun((int (*)(int)) isalpha))) != word.end();


    if (!nonAlphabetical && word.length() >= 6) {
        //casing format: first let upper case, rest lowercase
        std::transform(word.begin(), word.end(), word.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        std::transform(word.begin(), word.begin() + 1, word.begin(),
                       [](unsigned char c) { return std::toupper(c); });

        //Add word to both the set and the vector (vector copies from set to avoid duplicates)
        if(!setOfUniqueWords.count(word)){
            setOfUniqueWords.insert(word);
            validWords.push_back((word));
        }
    }

}

//reads in file word by word, placing string into the "words" vector<string>
void parse(string name) {
    std::ifstream ifile(name);

    //check if file is open before placing contents into string
    if (ifile.is_open()) {
        string word;
        while (ifile >> word) {
            words.push_back(word);
        }
    }



}
//random index selection by uniform int distribution
vector<int> randIndex(int range){

    vector<int> indexes;

    static default_random_engine generator;
    uniform_int_distribution<int> distribution(0, range);
    for(int i = 0; i < 4; i++){
        int randIndex = distribution(generator);
        indexes.push_back(randIndex);
    }
    distribution.reset();
    return indexes;

}
//calls helper method to randomly select indexes.
//prints out password format
string generatePasswords(vector<string> uniqueWords) {
    int len = uniqueWords.size();

    for(int i = 0; i < 20; i++) {
        //vector of 4 random indexes
        vector<int> randIndexes = randIndex(len-1);
        cout << uniqueWords[randIndexes[0]] + " " + uniqueWords[randIndexes[1]] + " " + uniqueWords[randIndexes[2]] +
                " " + uniqueWords[randIndexes[3]] + "1" << endl;


    }
}

int main() {
    //read file input, put words into a vector
    string fileName = "./input.txt";
    parse(fileName);

    //iterates through the "words" vector to find the proper words to generate passwords from
    for (const auto &i: words) {
        format(i);
    }

    //creates 20 different passwords with correct format and prints it out.
    generatePasswords(validWords);




}

