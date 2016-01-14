#include "../include/FalloutText.h"

// constructor
Character::Character(char character, int screen_y, int screen_x)
{
    character_ = character;
    screen_y_ = screen_y;
    screen_x_ = screen_x;
}
char Character::get_char(void)
{
    return character_;
}

int Character::get_y(void)
{
    return screen_y_;
}

int Character::get_x(void)
{
    return screen_x_;
}

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
            
    unsigned int str_len = line_width_ * num_rows_;
    
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

int FalloutText::screen_coords_to_index(
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

std::tuple < int, int > FalloutText::index_to_screen_coords(
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

char FalloutText::get_left_bracket(char right_bracket)
{
    int pos = std::find(
            right_brackets_.begin(), right_brackets_.end(), right_bracket) - 
            right_brackets_.begin();
    
    return left_brackets_[pos];
}

char FalloutText::get_right_bracket(char left_bracket)
{
    int pos = std::find(
            left_brackets_.begin(), left_brackets_.end(), left_bracket) - 
            left_brackets_.begin();
    
    return right_brackets_[pos];
}

/**
Return reference to list of Character objects containing selected characters and
their screen coordinates
**/
const std::vector < Character > & FalloutText::get_highlighted(
        std::string side, int cursor_y, int cursor_x)
{
    std::string text;
    
    if (side == "left")
    {
        text = left_text_;
    }
    else
    {
        text = right_text_;
    }
    
    // clear highlight list
    hl_list_.clear();
    
    // convert screen coords to string index
    int index = screen_coords_to_index(side, cursor_y, cursor_x);
    
    // get character at that string index
    char char_at_cursor = text[index];
    
    // add that character to highlight list
    hl_list_.push_back(Character(char_at_cursor, cursor_y, cursor_x));
    
    // check character type (alpha, bracket, junk)
    if (is_alpha(char_at_cursor))
    {
        // check characters to the left and right
        //hl_list = self.check_alpha_left(side, index) + hl_list
        //hl_list += self.check_alpha_right(side, index)
    }
    else if (is_left_bracket(char_at_cursor))
    {
        // check characters to the right of current position
        char matching_char = get_right_bracket(char_at_cursor);
        check_bracket_right(side, index, matching_char);
    }
    else if (is_right_bracket(char_at_cursor))
    {
        // check characters to the left of current position
        char matching_char = get_left_bracket(char_at_cursor);
        check_bracket_left(side, index, matching_char);
    }
    
    // junk characters: hl_list already contains just that char, so return
    
    return hl_list_;
}

void FalloutText::check_bracket_left(
        std::string side, int index, char matching_char)
{
    std::string text;
    
    if (side == "left")
    {
        text = left_text_;
    }
    else
    {
        text = right_text_;
    }
    
    // matching bracket flag
    bool found = false;
    
    // temporary results list
    std::vector < Character > hl_chars = {};
    
    while (true)
    {
        index -= 1; // move one character left
        
        if (index < 0)
        {
            break;
        }
        else
        {
            char check = text[index];
            
            // break if word encountered
            if (is_alpha(check))
            {
                break;
            }
            
            // get screen coords of current char
            auto coords = index_to_screen_coords(side, index);
            int screen_y = std::get<0>(coords);
            int screen_x = std::get<1>(coords);
            
            // add char to list
            hl_chars.push_back(Character(check, screen_y, screen_x));
            
            // check if maximum bracket set length exceeded
            if (hl_chars.size() > (max_bracket_len_ - 1))
            {
                break;
            }
            
            if (check == matching_char)
            {
                // matching bracket found
                found = true;
                break;
            }
        }
    }
    
    // append to highlight list if match found
    if (found)
    {
        for (auto hl : hl_chars)
        {
            hl_list_.push_back(hl);
        }
        
        // reverse highlight list to get correct character order
        std::reverse(hl_list_.begin(), hl_list_.end());
    }
}

void FalloutText::check_bracket_right(
        std::string side, unsigned int index, char matching_char)
{
    std::string text;
    
    if (side == "left")
    {
        text = left_text_;
    }
    else
    {
        text = right_text_;
    }
    
    // matching bracket flag
    bool found = false;
    
    // temporary results list
    std::vector < Character > hl_chars = {};
    
    while (true)
    {
        index += 1; // move one character right
        
        if (index > (text.length() - 1))
        {
            break;
        }
        else
        {
            char check = text[index];
            
            // break if word encountered
            if (is_alpha(check))
            {
                break;
            }
            
            // get screen coords of current char
            auto coords = index_to_screen_coords(side, index);
            int screen_y = std::get<0>(coords);
            int screen_x = std::get<1>(coords);
            
            // add char to list
            hl_chars.push_back(Character(check, screen_y, screen_x));
            
            // check if maximum bracket set length exceeded
            if (hl_chars.size() > (max_bracket_len_ - 1))
            {
                break;
            }
            
            if (check == matching_char)
            {
                // matching bracket found
                found = true;
                break;
            }
        }
    }
    
    // append to highlight list if match found
    if (found)
    {
        for (auto hl : hl_chars)
        {
            hl_list_.push_back(hl);
        }
    }
}

/**
Return true if given character is alphabetical ('A', 'B', 'c', 'd', etc.)
**/
bool FalloutText::is_alpha(char character)
{
    return isalpha(character);
}

/**
Return true if given character is a left bracket ('<', '(', '[', '{')
**/
bool FalloutText::is_left_bracket(char character)
{
    bool found = false;
    
    if (std::find(
            left_brackets_.begin(), left_brackets_.end(), character) != 
            left_brackets_.end())
    {
        found = true;
    }

    return found;
}

/**
Return true if given character is a right bracket ('>', ')', ']', '}')
**/
bool FalloutText::is_right_bracket(char character)
{
    bool found = false;
    
    if (std::find(
            right_brackets_.begin(), right_brackets_.end(), character) != 
            right_brackets_.end())
    {
        found = true;
    }
    
    return found;
}

/**
Return word formed from all selected characters concatenated
**/
std::string FalloutText::get_selected_word(void)
{
    std::string out = "";
    
    for (auto hl : hl_list_)
    {
        out += hl.get_char();
    }
    
    return out;
}
