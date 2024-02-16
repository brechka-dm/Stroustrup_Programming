#include "NamePairs.h"

/*
 * This program is a solution of Exercise 2 from Chapter 9.
 * "Design and implement a Name_pairs class containing a (name, age) pair, where
 * name is a string object and age is a double variable. Represent these class
 * members as objects of the classes vector<string> (named name) and vector<double>
 * (named age). Provide a read_names() input operation, reading a series of names.
 * Provide a read_ages() operation that prompts the user to enter an age for each
 * name. Provide a print() operation that prints (name[i], age[i]) pairs (one per
 * line) in the order specified by the name vector. Provide a sort() operation that
 * sorts the name vector alphabetically and sorts the age vector accordingly.
 * Implement all “operations” as member functions."
 * The implementation of the class is moved to separate files.
 */

int main() {
  NamePairs obj;
  obj.readNames();
  obj.readAges();
  obj.print();
  obj.sort();
  obj.print();
}