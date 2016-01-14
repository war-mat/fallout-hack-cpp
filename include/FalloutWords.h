#ifndef FALLOUT_WORDS_H
#define FALLOUT_WORDS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include <time.h>
#include <cstdlib>
#include <algorithm>

class FalloutWords
{
private:
    
    std::string file_name;
    
    // "<>(){}[]$.':_!\"+-%\/|*@#`=^;?,"
    std::vector < char > junk_list_ = {'<', '>', '(', ')', '{', '}', '[', ']', 
            '$', '.', '\'', ':', '_', '!', '\"', '+', '-', '%', '\\', '/', '|',
            '*', '@', '#', '`', '=', '^', ';', '?', ','};
    
    // filtered words loaded from /usr/share/dict/words
    std::vector < std::string > all_words_;
    
    // current word list (all words of a given length)
    std::vector < std::string > word_list_;
    
    // current password
    std::string password_;
    
    // current distribution of number of matching letters
    std::vector < int > match_distribution_;
    
    // current list of password candidates (excluding actual password)
    std::vector < std::string > candidate_list_;
    
    //FalloutWords() { } // private default constructor
    
public:
    FalloutWords(std::string file_name);
    void open_words_file(void);
    void report_values(void);
    void gen_word_list(unsigned int word_length);
    void new_password(void);
    bool is_ascii(std::string word);
    void new_match_distribution(unsigned int num_words, int max_match);
    int hamming_closeness(std::string word1, std::string word2);
    void gen_candidate_words(unsigned int num_words);
    void new_game(int word_length, int num_words, int max_match);
};

#endif
