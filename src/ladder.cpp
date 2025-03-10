#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error with " << word1 << " and " << word2 << ": " << msg << endl;
}

//bool edit_distance_within(const std::string& str1, const std::string& str2, int d);
//bool is_adjacent(const string& word1, const string& word2);
//vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    string word;

    if (!file.is_open()) {
        error("", "", "Unable to open file");
    }

    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found" << endl;
    } else {
        for (const string& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    }
}

