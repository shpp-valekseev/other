#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

/**
 * Program words ladder.It takes two words of equal length,
 * and displays the shortest ladder of valid words that change one letter.
 * The program transforms from the first word entered into the second.
 */
Vector<string> madeLadders(string firstWord, string lastWord, Vector<string> & vec);
Vector<string> checkSimilarWord(Vector<string> & vec, string lastWordLadder);
void showResult(Vector<string> &res);

/**
 * The main method that prompts the user words and forwards them for further processing
 */
int main() {
    while(true){
        string firstWord;
        string lastWord;

        Lexicon english("EnglishWords.txt");
        cout << "Enter the first word: ";
        cin >> firstWord;
        cout << "Enter the last word: ";
        cin >> lastWord;
        if(firstWord.length() != lastWord.length()){
            cout << "Please, enter correct data" << endl;
            continue;
        }

        Vector<string> vec;
        for (string word : english){
            if(word.length() == firstWord.length()) vec.add(word); // sorted only those words that are typed in length
        }

        Vector<string> res = madeLadders(firstWord, lastWord, vec);
        showResult(res);

    }
    return 0;
}

/**
 * It takes the words from which to make a ladder,
 * and a dictionary of words in length coincides with the length of introductory words
 */
Vector<string> madeLadders(string firstWord, string lastWord, Vector<string> & vec){
    Queue<Vector<string>> mainQueue;
    Vector<string> nullV;
    Vector<string> ladders;
    Lexicon usedWord;

    usedWord.add(firstWord);
    ladders.add(firstWord);
    mainQueue.enqueue(ladders);

    while (!mainQueue.isEmpty()){
        ladders = mainQueue.dequeue();
        string lastWordLadder =  ladders.get(ladders.size()-1);
        usedWord.add(lastWordLadder);

        if(lastWordLadder == lastWord) return ladders;

        Vector<string> similarWords = checkSimilarWord(vec, lastWordLadder);;

        for(string evenSimilar : similarWords){
            if(!usedWord.contains(evenSimilar)){
                usedWord.add(evenSimilar);
                Vector<string> lesticaCopy = ladders;
                lesticaCopy.add(evenSimilar);
                mainQueue.enqueue(lesticaCopy);
            }
        }
    }
    return nullV;
}

/**
 * Method takes a dictionary and the last word to the dictionary of the ladders.
 * Returns a vector with a list of words that use different by one letter in the input word.
 */
Vector<string> checkSimilarWord(Vector<string> & vec, string lastWordLadder){
    Vector<string> similarWords;

    for (int j = 0; j < vec.size(); j++){
        string word = vec[j];
        int countEquals = 0;

        for (int i = 0; i < lastWordLadder.length(); i++){
            if (lastWordLadder[i] == word[i]) countEquals++;
        }
        if(countEquals == lastWordLadder.length() - 1) similarWords.add(word);
    }
    return similarWords;
}

/**
 * Accepts vector with words ladder,
 * and displays the result on the screen.
 */
void showResult(Vector<string> &res){
    if (res.size() < 1){
        cout << "Ledder is not found." << endl;
    } else {
        for(int i = 0; i < res.size(); i++){
            string word = res.get(i);
            if(i != res.size()-1){
                cout << word << " -> ";
            } else {
                cout << word << endl;
            }
        }
    }
}
