#include <iostream>
#include <cstring> // For strcmp, strcpy, tolower
using namespace std;

// Structure for each word node
struct WordNode {
    char* word;
    int count;
    WordNode* next;
    
    WordNode(const char* w) {
        word = new char[strlen(w) + 1];
        strcpy(word, w);
        count = 1;
        next = nullptr;
    }
    
    ~WordNode() {
        delete[] word;
    }
};

// Hash Table Implementation
class WordFrequencyCounter {
private:
    static const int TABLE_SIZE = 100; // Size of hash table
    WordNode* table[TABLE_SIZE]; // Array of WordNode pointers
    
    // Convert word to lowercase for case-insensitive comparison
    void toLower(char* str) {
        for(int i = 0; str[i]; i++) {
            str[i] = tolower(str[i]);
        }
    }
    
    // Simple hash function (sum of ASCII values % TABLE_SIZE)
    int hashFunction(const char* word) {
        int sum = 0;
        for(int i = 0; word[i] != '\0'; i++) {
            sum += word[i];
        }
        return sum % TABLE_SIZE;
    }
    
    // Insert or update a word in the hash table
    void insertWord(const char* word) {
        char lowerWord[100];
        strcpy(lowerWord, word);
        toLower(lowerWord);
        
        int index = hashFunction(lowerWord);
        WordNode* current = table[index];
        
        // Check if word already exists
        while(current != nullptr) {
            if(strcmp(current->word, lowerWord) == 0) {
                current->count++;
                return;
            }
            current = current->next;
        }
        
        // If word doesn't exist, add new node
        WordNode* newNode = new WordNode(lowerWord);
        newNode->next = table[index];
        table[index] = newNode;
    }
    
public:
    WordFrequencyCounter() {
        for(int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }
    
    ~WordFrequencyCounter() {
        for(int i = 0; i < TABLE_SIZE; i++) {
            WordNode* current = table[i];
            while(current != nullptr) {
                WordNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
    
    // Process input text (split into words and insert into hash table)
    void processText(const char* text) {
        const char* delimiters = " \t\n.,;:!?\"()";
        char buffer[1000];
        strcpy(buffer, text);
        
        char* token = strtok(buffer, delimiters);
        while(token != nullptr) {
            insertWord(token);
            token = strtok(nullptr, delimiters);
        }
    }
    
    // Display word frequencies (sorted alphabetically)
    void displayFrequencies() {
        WordNode* words[1000];
        int wordCount = 0;
        
        // Collect all words
        for(int i = 0; i < TABLE_SIZE; i++) {
            WordNode* current = table[i];
            while(current != nullptr) {
                words[wordCount++] = current;
                current = current->next;
            }
        }
        
        // Sort words alphabetically (Bubble Sort for simplicity)
        for(int i = 0; i < wordCount - 1; i++) {
            for(int j = 0; j < wordCount - i - 1; j++) {
                if(strcmp(words[j]->word, words[j+1]->word) > 0) {
                    WordNode* temp = words[j];
                    words[j] = words[j+1];
                    words[j+1] = temp;
                }
            }
        }
        
        // Display results
        cout << "Word Frequency Count:\n";
        cout << "----------------------\n";
        for(int i = 0; i < wordCount; i++) {
            cout << words[i]->word << ": " << words[i]->count << endl;
        }
    }
};

int main() {
    WordFrequencyCounter counter;
    
    cout << "=== Word Frequency Counter ===\n";
    cout << "Enter text (press Enter twice to finish):\n";
    
    string input;
    string fullText;
    
    while(true) {
        getline(cin, input);
        if(input.empty()) break;
        fullText += input + " ";
    }
    
    counter.processText(fullText.c_str());
    counter.displayFrequencies();
    
    return 0;
}