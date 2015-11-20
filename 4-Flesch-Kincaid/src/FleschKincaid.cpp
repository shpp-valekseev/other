#include <iostream>
#include <fstream>
#include <cctype>
#include <stdio.h>

#include "console.h"
#include "tokenscanner.h"
#include "strlib.h"
using namespace std;

/**
 * This program makes the calculation complexity
 * of the text. When you start the program,
 * enter the name of a text file, and the program
 * displays the total number of sentences,
 * the number of words, syllables and complexity of the text.
 */

bool checkFileName(string fileName);
void processText(TokenScanner & scanner);
int checkSentences(string token);
bool checkWords(string token);
int colSyllable(string token);
bool checkVowel(char letter, int i, int len, string word);
double getGrade(int sentences, int words, int syllable);


/**
 * The main method of the program, which prompts the user for a file name,
 * until he enters a valid file, and then transmits the information to the
 * file method processText (), which will handle it.
 */
int main() {
    string fileName;
    while (true){
        cout << "Enter the file name: ";
        cin >>  fileName;
        bool enter = checkFileName(fileName);
        if(enter)break;
        cout << "Enter the correct file name" << endl;
    }

    ifstream file(fileName);
    TokenScanner scanner (file);

    processText(scanner);
    return 0;
}

/**
 * Accepts the name of the file, and returns a
 * boolean result of the existence of such a file.
 */
bool checkFileName(string fileName){
    bool res = true;
    ifstream file(fileName);
    if (!file.is_open()) res = false;
    return res;
}

/**
 * Receive information from file, processes and displays the result on the screen.
 */
void processText(TokenScanner & scanner){
    int counterSentences = 0;
    int counterWords = 0;
    int counterSyllable = 0;
    double grade = 0.0;

    scanner.ignoreWhitespace(); // ignores spaces
    scanner.addWordCharacters("'"); // does part of the token is the character "'"

    // processes each token
    while (scanner.hasMoreTokens()){
        string token = scanner.nextToken();
        counterSentences += checkSentences(token);
        if(checkWords(token)){
            counterWords ++;
            counterSyllable += colSyllable(token);
        }
    }
    // If the file does not contain any words or sentences, assume that their one
    if(counterWords == 0 || counterSentences == 0) counterSentences = counterWords = 1;

    grade = getGrade(counterSentences, counterWords, counterSyllable);

    cout << "Words : " << counterWords << endl;
    cout << "Syllable : " << counterSyllable << endl;
    cout << "Sentences : " << counterSentences << endl;
    cout << "Grade : " << grade << endl;
}

/**
 * The method takes the token, checks it, and concludes
 * hether this was the end of the sentence.
 * If yes, it returns 1, if not then returns 0.
 */
int checkSentences(string token){
    int res = 0;
    if(token == "." || token == "?" || token == "!" || token == "...") res = 1;

    return res;
}

/**
 * The method takes the tokenscans it and
 * makes a conclusion whether it is a word or not.
 * The result returns a Boolean value.
 */
bool checkWords(string token){
    bool res = false;
    if (isalpha(token[0])) res = true;

    return res;
}

/**
 * Accepts the word.
 * Returns the number of syllables in a word.
 */
int colSyllable(string word){
    int vovelSum = 0;
    word = toLowerCase(word);
    int len = word.length();
    for (int i = 0; i < len; i++) {    // Get on stage every letter of the word
        char letter = word[i];
        bool res = checkVowel(letter, i, len, word); // Checks each letter of the word in a vowel
        if (res) vovelSum++;
    }

    // If the number of vowels equal zero, then the result of doing 1
    if (vovelSum == 0) vovelSum = 1;

    return vovelSum;
}

/**
 * Checks whether the letter is a vowel, and if so,
 * does a conclusion as to whether it syllable.
 * Returns a boolean value.
 */
bool checkVowel(char letter, int i, int len, string word) {
    string vovels = "aeiouy";
    bool res = false;

    // Compare the letter with an array of vowels
    for (int j = 0; j < vovels.length(); j++) {
        if (vovels[j] == letter) res = true;
    }

    // Ignore sequence of vowels in succession
    for (int j = 0; j < vovels.length(); j++) {
        if (i != 0 && vovels[j] == word[i - 1]) res = false;
    }

    // If the last letter "e", it ignores
    if (i == len - 1 && letter == 'e') res = false;

    return res;
}

/**
 * Accepts number of sentences, words and syllables.
 * Gets a value that corresponds to the complexity of the text.
 */
double getGrade(int sentences, int words, int syllable){
    const double c0 = -15.59;
    const double c1 = 0.39;
    const double c2 = 11.8;

    double grade = c0 + (c1 * (double(words) / sentences)) + double(c2 * (double(syllable) / words));
    return grade;
}


