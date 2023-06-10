/*  
    Homework 3 - Backtracking
    This is a C++ program that uses backtracking method to impelement the Wordle game at the word level.
*/

#include <iostream>
#include <string>
#include <unordered_set>

const int MAX_TRIES = 6;

int get_green_number(const std::string& guess, const std::string& target) {
    int contor = 0;
    size_t len = guess.length();
    for (size_t i = 0; i < len; i++) {
        if (guess[i] == target[i])
            contor++;
    }
    return contor;
}

int get_yellow_number(const std::string& guess, const std::string& target) {
    int contor = 0;
    size_t len = guess.length();
    std::unordered_set<char> yellow_characters;
    for (size_t i = 0; i < len; i++) {
        if ((guess[i] != target[i]) && (target.find(guess[i]) != std::string::npos) && (!yellow_characters.count(guess[i]))) {
            contor++;
            yellow_characters.insert(guess[i]);
        }
    }
    return contor;
}

bool valid(const std::string& guess, const std::string& target, int nr_green, int nr_yellow) {
    int contor_green = get_green_number(guess, target);
    int contor_yellow = get_yellow_number(guess, target);
    return (nr_green == contor_green && nr_yellow <= contor_yellow);
}

void print_guess(const std::string& guess, const std::string& target) {
    for (size_t i = 0; i < target.length(); i++) {
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

    std::string cuvant;
    std::cout << "Try number " << (attempt + 1) << ": Enter a word: ";
    std::cin >> cuvant;

    if (cuvant.length() != target.length()) {
        std::cout << "The word you entered is not the same length as the target word.\n";
        attempt++;
        return wordleBkt(target, guess, attempt);
    }

    int numGreen = get_green_number(cuvant, target);
    int numYellow = get_yellow_number(cuvant, target);

    if (valid(cuvant, target, numGreen, numYellow)) {
        for (size_t i = 0; i < target.length(); i++)
            if (cuvant[i] == target[i])
                guess[i] = cuvant[i];
    }
    else
        std::cout << "The word you entered doesn't correspond to the indications.\n";

    std::cout << "Mistery word: ";
    print_guess(guess, target);

    attempt++;
    return wordleBkt(target, guess, attempt);
}

int main() {
    std::string target;
    std::cout << "Enter target word: ";
    std::cin >> target;

    std::string guess(target.length(), '-');
    std::cout << "Let the game begin!\n";
    std::cout << "Mistery word: ";
    print_guess(guess, target);

    if (wordleBkt(target, guess, 0))
        std::cout << "Congratulations, you won!\n";
    else
        std::cout << "You lose, the word you was looking for was: " << target << '\n';
    return 0;
}
