#include <iostream>
#include <random>
#include <vector>
#include <sstream>

using namespace std;

vector<int> generateSecret() {
  vector<int> result;
  std::random_device randomDevice;
  std::mt19937 generator(randomDevice());
  std::uniform_int_distribution<std::mt19937::result_type> distribution(0, 9);
  for (int i = 0; i < 4; i++) result.push_back(distribution(generator));
  return result;
}

vector<int> getUserInput() {
  vector<int> result;
  for (int i = 0; i < 4; i++) {
    int inp;
    cin >> inp;
    result.push_back(inp);
  }
  return result;
}

int countBulls(const vector<int>& secret, const vector<int> userInput) {
  int result = 0;
  for (int i = 0; i < 4; i++)
    if (secret[i] == userInput[i]) result++;
  return result;
}

int countCows(const vector<int>& secret, const vector<int> userInput) {
  int result = 0;
  for (int s = 0; s < 4; s++)
    for (int u = 0; u < 4; u++)
      if (secret[s] == userInput[u] && s != u) result++;
  return result;
}

bool checkUserAnswer(const vector<int>& secret, const vector<int> userInput, string& answer) {
  bool result = false;
  int bulls = countBulls(secret, userInput);
  int cows = countCows(secret, userInput);
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

  return 0;
}