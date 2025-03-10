#include "ladder.h"

int main() {
    set<string> word_list;
    load_words(word_list, "test.txt");
    for (const auto& word : word_list) {
        std::cout << word << " ";
    }
}