#include <array>
#include <iostream>
#include <random>
#include <sstream>

using namespace std;

/*
 * This program is the solution to Exercise 8 of Chapter 6 of PROGRAMMING.
 * Principles and Practice Using C++. 2nd edition.
 *
 * The program implements the game "Bulls and Cows". The computer guesses 4
 * symbols, the user is asked to guess these symbols. Suppose the computer
 * guesses the symbols "abcd" and the user enters the symbols "afdx"; the
 * program must answer "1 bull and 1 cow" because the user guessed one correct
 * symbol (a) at the correct position (bull) and one correct symbol (d) at the
 * incorrect position (cow). The guessing continues until the user gets four
 * bulls, i.e. guesses four correct symbols on four correct positions.
 *
 * The program prompts you to enter characters one at a time, checking if the
 * input is correct.
 */

/*
 * This function randomly generates secret symbol sequence of length 4.
 *
 * STL class array is described in Chapter 20.9.
 */
array<char, 4> generateSecret() {
  array<char, 4> result;

  // Use random library to generate random numbers. See
  // https://en.cppreference.com/w/cpp/header/random
  std::random_device randomDevice;
  std::mt19937 generator(randomDevice());
  std::uniform_int_distribution<std::mt19937::result_type> distribution(
      static_cast<int>('a'), static_cast<int>('{'));
  for (int i = 0; i < 4; i++)
    result.at(i) = static_cast<char>(distribution(generator));
  return result;
}

/*
 * This function handles user input. 
 */
array<char, 4> getUserInput() {
  array<char, 4> result;
  int i = 0;

  while (i < 4) {
    cout << "Input letter:" << endl;
    string input;
    getline(cin, input);
    if (input.size() > 1) {
      cout << "Incorrect input. Please input one letter." << endl;
      continue;
    }

    // isalpha checks if the char is in range ['a', 'z'] or ['A', 'Z'].
    if (!isalpha(input[0])) {
      cout << "Incorrect input. Please input a letter." << endl;
      continue;
    }

    // tolower converts chat to lower case.
    result.at(i++) = tolower(input[0]);
  }
  return result;
}

int countBulls(const array<char, 4>& secret, const array<char, 4> userInput) {
  int result = 0;
  for (int i = 0; i < 4; i++)
    if (secret[i] == userInput[i]) result++;
  return result;
}

int countCows(const array<char, 4>& secret, const array<char, 4> userInput) {
  int result = 0;
  for (int s = 0; s < 4; s++)
    for (int u = 0; u < 4; u++)
      if (secret[s] == userInput[u] && s != u) result++;
  return result;
}

/*
 * This function returns true if all 4 bulls are found.
 * answer is an output parameter.
 */
bool checkUserAnswer(const array<char, 4>& secret,
                     const array<char, 4>& userInput, string& answer) {
  bool result = false;
  int bulls = countBulls(secret, userInput);
  int cows = countCows(secret, userInput);

  // Using stringstream to construct output string.
  // See Chapter 11.4.
  stringstream answerStream;
  answerStream << bulls << " bulls and " << cows << " cows.";
  answer = answerStream.str();
  return bulls == 4;
}

int main() {
  bool stop = false;
  while (!stop) {
    string answer;
    stop = checkUserAnswer(generateSecret(), getUserInput(), answer);
    cout << answer << endl;
  }
  cout << "Winner!" << endl;
  return 0;
}