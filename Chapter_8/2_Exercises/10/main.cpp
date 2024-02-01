#include <iostream>
#include <vector>

using namespace std;

/*
 * This program is a solution of the Exercise 10 0f the Chapter 8.
 * "Write a function that, over two objects, price and weight, of class
 * vector<double>, computes a value ("index") equal to the sum of all products
 * of price[i]*weight[i]".
 */

double index(const vector<double>& price, const vector<double>& weight) {
  double result{0.0};
  for (int i = 0; i < weight.size(); ++i) result += price[i] * weight[i];
  return result;
}

int main() {
  const vector<double> price{21.3, 12.4, 11.1, 40.0, 0.25};
  const vector<double> weight{20.5, 31.0, 42.2, 3.7, 70.08};

  cout << "weights: ";
  for (int i = 0; i < weight.size(); ++i) cout << weight[i] << " ";
  cout << endl << "prices: ";
  for (int i = 0; i < price.size(); ++i) cout << price[i] << " ";
  cout << endl << "index: " << index(price, weight);
}
