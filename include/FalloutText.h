#ifndef FALLOUT_TEXT_H
#define FALLOUT_TEXT_H

#include <map>
#include <iostream>

class FalloutText
{
private:
    
    std::map <std::string, std::string> top_text = {
            {"logo", "ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL"},
            {"command", "ENTER PASSWORD NOW"}
            };
            
    int row_start;
    int left_col_start;
    int right_col_start;
    int line_width;
    int num_rows;
    
    FalloutText() { } // private default constructor
    
public:
    FalloutText(int row_start, int left_col_start, int right_col_start, 
            int line_width, int num_rows);
    void report_values(void);
};

#endif

