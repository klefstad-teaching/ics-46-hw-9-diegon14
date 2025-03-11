#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error with " << word1 << " and " << word2 << ": " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();

    if (len1 > len2) {
        return edit_distance_within(str2, str1, d);
    }

    if (abs(len1 - len2) > d) {
        return false;
    }

    if (len1 == 0) return len2 <= d;
    if (len2 == 0) return len1 <= d;

    if (d < 0) return false;

    if (str1[len1 - 1] == str2[len2 - 1]) {
        return edit_distance_within(str1.substr(0, len1 - 1), str2.substr(0, len2 - 1), d);
    } else {
        if (edit_distance_within(str1, str2.substr(0, len2 - 1), d - 1)) {
            return true;
        }

        if (edit_distance_within(str1.substr(0, len1 - 1), str2, d - 1)) {
            return true;
        }
        
        if (edit_distance_within(str1.substr(0, len1 - 1), str2.substr(0, len2 - 1), d - 1)) {
            return true;
        }
        return false;
    }
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    unordered_set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);

                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        return new_ladder;
                    }

                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    string word;

    if (!file.is_open()) {
        error("", "", "Unable to open file");
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string data = buffer.str();
    stringstream ss(data);

    while (ss >> word) {
        for (char& c : word) {
            c = tolower(c);
        }
        word_list.emplace(move(word));
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        cout << "Word ladder found: "; 
        for (const string& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    vector<string> test = generate_word_ladder("work", "play", word_list);
    my_assert(test.size() == 6)
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}
