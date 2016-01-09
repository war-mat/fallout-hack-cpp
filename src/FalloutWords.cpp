#include "../include/FalloutWords.h"

// constructor
FalloutWords::FalloutWords(std::string file_name)
{
    // seed random
    srand(time(NULL));
    
    this->file_name = file_name;
    
    // populate words list
    open_words_file();
    
    //new_match_distribution(15, 4);
    
    //gen_candidate_words(15);
}

void FalloutWords::open_words_file(void)
{
    std::ifstream file("/usr/share/dict/words");

    std::string word;
    
    while (file >> word)
    {
        if ((word.find("'") == std::string::npos) and 
                (isupper(word.at(0)) == 0) and is_ascii(word))
        {
            all_words_.push_back(word);
        }
    }
}

void FalloutWords::report_values(void)
{
    std::cout << all_words_[0] << std::endl;
    std::cout << all_words_[10] << std::endl;
    std::cout << all_words_[100] << std::endl;
    std::cout << all_words_[1000] << std::endl;
    std::cout << all_words_[10000] << std::endl;
    std::cout << all_words_[50000] << std::endl;
    std::cout << all_words_.size() << std::endl;
    std::cout << word_list_[0] << std::endl;
    std::cout << word_list_[1] << std::endl;
    std::cout << word_list_[2] << std::endl;
    std::cout << word_list_.size() << std::endl;
    std::cout << word_list_[word_list_.size() - 1] << std::endl;
    std::cout << word_list_[word_list_.size() - 2] << std::endl;
    std::cout << word_list_[word_list_.size() - 3] << std::endl;
    std::cout << "password: " << password_ << std::endl;
}

void FalloutWords::gen_word_list(int word_length)
{
    for(std::string word : all_words_)
	{
		if (word.length() == word_length)
        {
            word_list_.push_back(word);
        }
	}
}

void FalloutWords::new_password(void)
{
    int index = rand() % word_list_.size();
    
    password_ = word_list_[index];
}

bool FalloutWords::is_ascii(std::string word)
{
    for(char ch : word)
	{
		if (not (ch >= 0) and (ch < 128))
        {
            return false;
        }
	}
    
    return true;
}

void FalloutWords::new_match_distribution(int num_words, int max_match)
{
    // number of choices and size of x axis
    double x = max_match + 1.0;
    
    // y at x = 0 to form a triangle of area 1.0
    double y = 2.0 / x;
    
    // slope of the line from (0, y) to (x, 0) (rise over run)
    double m = -y / x;
    
    // offset size to place each x value at the middle of the line segments
    // created by dividing the x axis into 'x' number of discrete choices
    double step = 1.0 / (x * 2);
    
    // using the formula for a line, find the y value (probability) for each
    // choice, given its position on the x axis
    std::vector < double > probs;
    
    for (int i = 0; i < (max_match + 1); i++)
    {
        double prob = (((i / x) + step) * x * m) + y;

        probs.push_back(prob);
    }
    
    // probabilities should sum to 1.0, give or take floating point errors
    //double sum = 0; for (int i = 0; i < probs.size(); i++) sum += probs[i];
    //std::cout << "sum of probabilities: " << sum << std::endl;
    
    int matches = 0;
    
    while (match_distribution_.size() < num_words)
    {
        double roll = static_cast < double > (rand()) /
                static_cast < double > (RAND_MAX);
                
        double cumulative_prob = 0.0;
        
        for (int i = 0; i < probs.size(); i++)
        {
            cumulative_prob += probs[i];
            
            if (roll < cumulative_prob)
            {
                match_distribution_.push_back(i);
                break;
            }
        }
    }
}

/**
Return number of same characters, in the same location in two strings.
Basically the inverse of Hamming distance.
**/
int FalloutWords::hamming_closeness(std::string word1, std::string word2)
{
    try
    {
        if (word1.length() != word2.length())
        {
            throw "Undefined for sequences of unequal length";
        }
        else
        {
            int count = 0;
            
            for (int i = 0; i < word1.length(); i++)
            {
                count += (word1[i] == word2[i]);
            }
            
            return count;
        }
    }
    catch(const char* msg)
    {
        std::cerr << msg << std::endl;
    }
}

void FalloutWords::gen_candidate_words(int num_words)
{
    try
    {
        for (int i = 0; i < num_words; i++)
        {
            int match = match_distribution_[i];
            
            while (true)
            {
                // list of all words with that number of matches
                std::vector < std::string > match_list;
                
                for (std::string word : word_list_)
                {
                    if (hamming_closeness(word, password_) == match)
                    {
                        match_list.push_back(word);
                    }
                }
                
                // if no matches found, decrease match number and retry
                if (match_list.size() == 0)
                {
                    if (match > 0)
                    {
                        match -= 1;
                    }
                }
                else
                {
                    // select a word from match list at random
                    int rand_index = rand() % match_list.size();
                    
                    std::string rand_word = match_list[rand_index];
                    
                    // check if selected word != pw and hasn't been selected yet
                    if ((rand_word != password_) and 
                            (std::find(candidate_list_.begin(), 
                            candidate_list_.end(), rand_word) == 
                            candidate_list_.end()))
                    {
                        candidate_list_.push_back(rand_word);
                        break;
                    }
                }
            }
        }
        
        // throw exception if candidate list did not generate properly
        if (candidate_list_.size() != num_words)
        {
            throw "candidate word list failed to generate";
        }
    }
    catch(const char* msg)
    {
        std::cerr << msg << std::endl;
    }
}

void FalloutWords::new_game(int word_length, int num_words, int max_match)
{
    // generate word list for current word length
    gen_word_list(word_length);
    
    // select a password
    new_password();
    
    new_match_distribution(num_words, max_match);
}
