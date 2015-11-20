#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/**
 * This program simulates the game obenglobish.
 * Under the terms of the game, in every word
 * necessary to insert the letters "ob", before
 * every vowel letters.
 */

string obenglobish(string word);

/**
 * The main class that takes a word
 * from the user and displays the result.
 */
int main() {
   while(true){
       string word = toLowerCase(getLine("Enter the word: "));
       if( word == ""){
           cout << "You have not entered words :(" << endl;
           continue;
       }
       string translation = obenglobish(word);
       cout << word << " -> " << translation << endl;
   }
   return 0;
}

/**
 * The method takes the word.
 * Returns the word by inserting the letter "ob"
 * before a vowel letters according to the rules of the game.
 */
string obenglobish(string word){
 string vovels = "aeiou";
 string res;

 for( int i = 0; i < word.length(); i++){
     char oneChar = word.at(i);
     string ob;

     // Checks each letter of the word, in a vowel.
     for( int j = 0; j < vovels.length(); j++){
         if(oneChar == vovels.at(j)) ob = "ob" ;
     }

     // Checks had a previous letter of vowel or not.
     for( int j = 0; j < vovels.length(); j++){
         if(i != 0 && word.at(i-1) == vovels.at(j)) ob = "" ;
     }

     // Checks that the last letter "e" or not
     if (i == word.length() - 1 && oneChar == 'e') ob =  "";

     res += ob + oneChar;
 }

 // Converts the first letter of a word to uppercase.
 res[0] = toupper(res[0]);
 return res;
}
