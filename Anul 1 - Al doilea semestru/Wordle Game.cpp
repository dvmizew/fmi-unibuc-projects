/*  
    Homework 3 - Backtracking
    This is a C++ program that uses backtracking method to impelement the Wordle game at the word level.
*/

#include <iostream>
#include <string>
#include <unordered_set>

const int MAX_TRIES = 6;

bool check_char_at_pos(const std::string& word, char character, int pos) {
    return word[pos] == character;
}

bool contains_Char(const std::string& word, char character) {
    return word.find(character) != std::string::npos;
}

int number_green(const std::string& guess, const std::string& target) {
    int counter = 0;
    size_t len = guess.length();
    for (size_t i = 0; i < len; i++) {
        if (guess[i] == target[i])
            counter++;
    }
    return counter;
}

int number_yellow(const std::string& guess, const std::string& target) {
    int counter = 0;
    size_t len = guess.length();
    std::unordered_set<char> yellow_chars;
    for (size_t i = 0; i < len; i++) {
        if (guess[i] != target[i] && contains_Char(target, guess[i]) && !check_char_at_pos(guess, guess[i], i)
            && yellow_chars.count(guess[i]) == 0) {
            counter++;
            yellow_chars.insert(guess[i]);
        }
    }
    return counter;
}

bool valid(const std::string& guess, const std::string& target, int num_green, int num_yellow) {
    int greens_counter = number_green(guess, target);
    int yellows_counter = number_yellow(guess, target);
    return (num_green == greens_counter && num_yellow <= yellows_counter);
}

void print_guessed(const std::string& guess, const std::string& target) {
    size_t len = guess.length();
    for (size_t i = 0; i < len; i++) {
        if (guess[i] == target[i])
            std::cout << "\033[1;32m" << guess[i] << "\033[0m";
        else
            std::cout << '-';
    }
    std::cout << '\n';
}

bool wordleBkt(const std::string& target, std::string& guess, int attempt) {
    if (guess == target)
        return true;
    if (attempt >= MAX_TRIES)
        return false;

    std::string word;
    std::cout << "Try " << (attempt + 1) << ": Enter a word: ";
    std::cin >> word;

    if (word.length() != target.length()) {
        std::cout << "The word you entered has a different length than the target word.\n";
        return false;
    }

    int numGreen = number_green(word, target);
    int numYellow = number_yellow(word, target);

    if (valid(word, target, numGreen, numYellow)) {
        for (size_t i = 0; i < target.length(); i++)
            if (word[i] == target[i])
                guess[i] = word[i];
    }
    else
        std::cout << "The word you entered doesn't correspond to the indications.\n";

    std::cout << "Mysterious word: ";
    print_guessed(guess, target);
    return false;
}

int main() {
    std::string target;
    std::cout << "Enter the target word (maximum 5 letters): ";
    std::cin >> target;

    if (target.length() > 5) {
        std::cout << "The target word has more than 5 letters.\n";
        return 0;
    }

    std::string guess(target.length(), '-');
    std::cout << "The game has begun!\n";
    std::cout << "Mysterious word: ";
    print_guessed(guess, target);

    int try_num = 0;
    while (try_num < MAX_TRIES) {
        if (wordleBkt(target, guess, try_num))
            break;
        try_num++;
    }

    std::cout << "Mysterious word: ";
    print_guessed(guess, target);

    if (guess == target)
        std::cout << "Congratulations, you won!\n";
    else
        std::cout << "You lose. The target word was: " << target << '\n';
    return 0;
}
