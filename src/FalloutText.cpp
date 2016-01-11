#include "../include/FalloutText.h"

// constructor
FalloutText::FalloutText(int row_start, int left_col_start, int right_col_start, 
        int line_width, int num_rows)
{
    row_start_ = row_start;
    row_end_ = row_start + num_rows;
    
    left_col_start_ = left_col_start;
    right_col_start_ = right_col_start;
    
    line_width_ = line_width;
    num_rows_ = num_rows;
    
    // left text column bounds (screen coords)
    left_lower_ = left_col_start;
    left_upper_ = left_lower_ + line_width - 1;
    
    // right column bounds (screen coords)
    right_lower_ = right_col_start;
    right_upper_ = right_lower_ + line_width - 1;
    
    // pick a random starting memory address
    start_address_ = set_start_address();
    
    // generate a list of addresses starting from start address
    gen_address_list();
    
    // all of this should be moved from the constructor to a "new_text" func
    gen_junk_strings();
}

void FalloutText::report_values(void)
{
    std::cout << row_start_ << std::endl;
    std::cout << left_col_start_ << std::endl;
    std::cout << right_col_start_ << std::endl;
    std::cout << line_width_ << std::endl;
    std::cout << num_rows_ << std::endl;
    std::cout << top_text["logo"] << std::endl;
    std::cout << left_text_ << std::endl;
    std::cout << right_text_ << std::endl;
}

int FalloutText::set_start_address(void)
{
    // maximum memory address
    int start_address_max = 65535 - (line_width_ * num_rows_ * 2);
        
    // select random address between 0x0000 and max
    return rand() % start_address_max;
}

void FalloutText::gen_address_list(void)
{
    int start = start_address_;
    
    while (address_list_.size() < (num_rows_ * 2))
    {
        address_list_.push_back(int_address_to_hex_string(start));
        
        start += line_width_;
    }
}

std::string FalloutText::int_address_to_hex_string(int address)
{
    std::stringstream stream;
    
    stream << std::hex << address;
    
    std::string out = stream.str();
    
    // convert to uppercase
    for (auto & c: out) 
    {
        c = toupper(c);
    }
    
    out = "0x" + out;
    
    return out;
}

void FalloutText::gen_junk_strings(void)
{
    std::vector < char > junk_chars = {
            '$','.','\'',':','_','!','\\','"','+','-','%','/','|','*','@','#',
            '`','=','^',';','?',',','(','[','<','{',')',']','>','}'};
            
    int str_len = line_width_ * num_rows_;
    
    while (left_text_.length() < str_len)
    {
        left_text_ = left_text_ + junk_chars[rand() % junk_chars.size()];
        right_text_ = right_text_ + junk_chars[rand() % junk_chars.size()];
    }
}

const std::string & FalloutText::get_top_text(std::string key)
{
    return top_text[key];
}

const std::string & FalloutText::get_left_right_text(std::string side)
{
    if (side == "left")
    {
        return left_text_;
    }
    else
    {
        return right_text_;
    }
}

const std::vector < std::string > & FalloutText::get_address_list(void)
{
    return address_list_;
}

int FalloutText::screen_coords_to_string_index(
        std::string side, int screen_y, int screen_x)
{
    int x_offset;
    
    if (side == "left")
    {
        x_offset = left_lower_;
    }
    else
    {
        x_offset = right_lower_;
    }
    
    return (screen_y - row_start_) * line_width_ + screen_x - x_offset;
}

std::tuple < int, int > FalloutText::string_index_to_screen_coords(
        std::string side, int index)
{
    int x_offset;
    
    if (side == "left")
    {
        x_offset = left_lower_;
    }
    else
    {
        x_offset = right_lower_;
    }
    
    int out_y = (index / line_width_) + row_start_;
    int out_x = (index % line_width_) + x_offset;
    
    return std::make_tuple(out_y, out_x);
}

void FalloutText::reset_text_list(void)
{
    right_text_list_.clear();
}
