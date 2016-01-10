#ifndef FALLOUT_TEXT_H
#define FALLOUT_TEXT_H

#include <map>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <unordered_set>

class FalloutText
{
private:
    
    std::map <std::string, std::string> top_text = {
            {"logo", "ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL"},
            {"command", "ENTER PASSWORD NOW"}
            };
    
    // text up-down bounds (screen coords)        
    int row_start_;
    int row_end_;
    
    int left_col_start_;
    int right_col_start_;
    int line_width_;
    int num_rows_;
    
    // left text column bounds (screen coords)
    int left_lower_;
    int left_upper_;
    
    // right column bounds (screen coords)
    int right_lower_;
    int right_upper_;
    
    // random starting memory address
    int start_address_;
    
    // list of hex memory addresses
    std::vector < std::string > address_list_;
    
    // original text strings for searching through
    std::string left_text_;
    std::string right_text_;
    
    // array for storing right side text strings
    std::vector < std::string > right_text_list_;
    int right_max_lines_ = 20;
    int max_bracket_len_ = 20;
    
    std::unordered_set < char > alphabet_ = {
            'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
            'R','S','T','U','V','W','X','Y','Z'};
    std::unordered_set < char > junk_ = {
            '$','.','\'',':','_','!','\\','"','+','-','%','/','|','*','@','#',
            '`','=','^',';','?',','};
    std::vector < char > left_brackets_ = {'(', '[', '<', '{'};
    std::vector < char > right_brackets_ = {')', ']', '>', '}'};
    
    FalloutText() { } // private default constructor
    
public:
    FalloutText(int row_start, int left_col_start, int right_col_start, 
            int line_width, int num_rows);
    void report_values(void);
    int set_start_address(void);
    void gen_address_list(void);
    std::string int_address_to_hex_string(int address);
    void gen_junk_strings(void);
    const std::string & get_top_text(std::string key);
    const std::string & get_left_right_text(std::string side);
    const std::vector < std::string > & get_address_list(void);
};

#endif
