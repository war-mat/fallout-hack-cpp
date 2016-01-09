#include "../include/FalloutText.h"

// constructor
FalloutText::FalloutText(int row_start, int left_col_start, int right_col_start, 
        int line_width, int num_rows)
{
    this->row_start = row_start;
    this->left_col_start = left_col_start;
    this->right_col_start = right_col_start;
    this->line_width = line_width;
    this->num_rows = num_rows;
}

void FalloutText::report_values(void)
{
    std::cout << this->row_start << std::endl;
    std::cout << this->left_col_start << std::endl;
    std::cout << this->right_col_start << std::endl;
    std::cout << this->line_width << std::endl;
    std::cout << this->num_rows << std::endl;
    std::cout << top_text["logo"] << std::endl;
}
