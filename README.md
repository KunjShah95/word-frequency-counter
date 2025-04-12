# Word Frequency Counter

A C++ program that counts and displays the frequency of words in a given text using a hash table implementation.

## Features

- Case-insensitive word counting
- Efficient hash table implementation
- Handles various text delimiters (spaces, tabs, punctuation)
- Alphabetically sorted output

## How to Use

1. Compile the program:
   ```bash
   g++ main.cpp -o word_counter
   ```

2. Run the program:
   ```bash
   ./word_counter
   ```

3. Enter your text. Press Enter twice to finish input.

## Implementation Details

- Uses a hash table with chaining for collision resolution
- Custom hash function based on ASCII values
- Dynamic memory management for word storage
- Bubble sort for alphabetical output sorting

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.