#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error with " << word1 << " and " << word2 << ": " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();
    if (abs(len1 - len2) > d) 
        return false;

    vector<vector<int>> distance(len1 + 1, vector<int>(len2 + 1));

    for (int i = 0; i <= len1; ++i) {
        for (int j = 0; j <= len2; ++j) {
            if (i == 0) {
                distance[i][j] = j;
            } else if (j == 0) {
                distance[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                distance[i][j] = distance[i - 1][j - 1];
            } else {
                distance[i][j] = 1 + min({distance[i - 1][j], distance[i][j - 1], distance[i - 1][j - 1]});
            }
        }
    }
    return distance[len1][len2] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    unordered_set<string> word_set(word_list.begin(), word_list.end());
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    unordered_set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size();
        unordered_set<string> current_level_visited;

        for (int i = 0; i < level_size; ++i) {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.back();

            for (size_t j = 0; j < last_word.length(); ++j) {
                string new_word = last_word;
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == last_word[j]) continue;
                    new_word[j] = c;

                    if (new_word == end_word) {
                        ladder.push_back(new_word);
                        return ladder;
                    }

                    if (word_set.count(new_word) && !visited.count(new_word)) {
                        current_level_visited.insert(new_word);
                        vector<string> new_ladder = ladder;
                        new_ladder.push_back(new_word);
                        ladder_queue.push(new_ladder);
                    }
                }
            }

            for (size_t j = 0; j <= last_word.length(); ++j) {
                for (char c = 'a'; c <= 'z'; ++c) {
                    string new_word = last_word.substr(0, j) + c + last_word.substr(j);
                    
                    if (new_word == end_word) {
                        ladder.push_back(new_word);
                        return ladder;
                    }

                    if (word_set.count(new_word) && !visited.count(new_word)) {
                        current_level_visited.insert(new_word);
                        vector<string> new_ladder = ladder;
                        new_ladder.push_back(new_word);
                        ladder_queue.push(new_ladder);
                    }
                }
            }

            for (size_t j = 0; j < last_word.length(); ++j) {
                string new_word = last_word.substr(0, j) + last_word.substr(j + 1);
                
                if (new_word == end_word) {
                    ladder.push_back(new_word);
                    return ladder;
                }

                if (word_set.count(new_word) && !visited.count(new_word)) {
                    current_level_visited.insert(new_word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(new_word);
                    ladder_queue.push(new_ladder);
                }
            }
        }
        for (const auto& w : current_level_visited) {
            visited.insert(w);
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

    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
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