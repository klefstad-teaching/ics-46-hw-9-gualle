#include "ladder.h"
using namespace std;
void error(string word1, string word2, string msg){
	cerr<<"error:"<<msg<<',' << word1 << " -> " << word2<<endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
	int len1 = str1.size(), len2 = str2.size();
    if (abs(len1 - len2) > d) return false;
    int diff_count = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++diff_count > d) return false;
            if (len1 > len2) ++i; 
            if (len1 < len2) ++j; 
            if (len1 == len2){ ++i; ++j; }
        } else {
            ++i; ++j;
        }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2){
	 return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
	queue<vector<string>> ladder_queue;
	ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        auto ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const auto& word : word_list) {
            if (is_adjacent(last_word, word)) {
				if (visited.find(word) == visited.end()) { 
					visited.insert(word);
	                vector<string> new_ladder = ladder;
	                new_ladder.push_back(word);
	
	                if (word == end_word) return new_ladder;
	                ladder_queue.push(new_ladder);
				}
            }
        }
    }
    return {}; 
}

void load_words(set<string> & word_list, const string& file_name){
	ifstream file(file_name);
    if (!file) {
        error("", "", "Cannot open file: " + file_name);
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder){
	if (ladder.empty()) {
        cout << "No word ladder found!" << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size()-1; ++i) {
        cout << ladder[i]; 
		cout << " -> ";
    }
	cout<<ladder.back();
    cout << endl;
}

void verify_word_ladder(){
	set<string> word_list;
    load_words(word_list, "words.txt");

    vector<string> ladder1 = generate_word_ladder("cat", "dog", word_list);
    print_word_ladder(ladder1);

    vector<string> ladder2 = generate_word_ladder("marty", "curls", word_list);
    print_word_ladder(ladder2);
}