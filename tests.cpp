/*tests.c*/

//
// Google test cases for our set class.
//
// Initial template: Prof. Joe Hummel
// Northwestern University
// CS 211
//

// <<< Jay Yegon >>>
// <<< COMPUTER SCIENCE AND ENGINEERING MAJOR >>>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <set>  // for comparing answers

using std::string;
using std::vector;
using std::pair;

#include "set.h"
#include "gtest/gtest.h"


TEST(myset, empty_set)
{
  set<int> S;

  ASSERT_EQ(S.size(), 0);
}

TEST(myset, set_with_one)
{
  set<int> S;

  ASSERT_EQ(S.size(), 0);

  S.insert(123);

  ASSERT_EQ(S.size(), 1);

  ASSERT_TRUE(S.contains(123));
  ASSERT_TRUE(S[123]);

  ASSERT_FALSE(S.contains(100));
  ASSERT_FALSE(S[100]);
  ASSERT_FALSE(S.contains(200));
  ASSERT_FALSE(S[200]);
}

TEST(myset, set_with_four_strings)
{
  set<string> S;

  ASSERT_EQ(S.size(), 0);

  S.insert("banana");
  S.insert("apple");
  S.insert("chocolate");
  S.insert("pear");

  ASSERT_EQ(S.size(), 4);

  ASSERT_TRUE(S.contains("pear"));
  ASSERT_TRUE(S["banana"]);
  ASSERT_TRUE(S.contains("chocolate"));
  ASSERT_TRUE(S["apple"]);

  ASSERT_FALSE(S.contains("Apple"));
  ASSERT_FALSE(S["carmel"]);
  ASSERT_FALSE(S.contains("appl"));
  ASSERT_FALSE(S["chocolatee"]);
}

class Movie
{
public:
  string Title;
  int    ID;
  double Revenue;

  Movie(string title, int id, double revenue)
    : Title(title), ID(id), Revenue(revenue)
  { }

  bool operator<(const Movie& other)
  {
    if (this->Title < other.Title)
      return true;
    else
      return false;
  }
};

TEST(myset, set_with_movies)
{
  set<Movie> S;

  ASSERT_EQ(S.size(), 0);

  Movie Sleepless("Sleepless in Seattle", 123, 123456789.00);
  S.insert(Sleepless);

  Movie Matrix("The Matrix", 456, 400000000.00);
  S.insert(Matrix);

  Movie AnimalHouse("Animal House", 789, 1000000000.00);
  S.insert(AnimalHouse);

  ASSERT_EQ(S.size(), 3);

  vector<Movie> V = S.toVector();

  ASSERT_EQ(V[0].Title, "Animal House");
  ASSERT_EQ(V[1].Title, "Sleepless in Seattle");
  ASSERT_EQ(V[2].Title, "The Matrix");
}

TEST(myset, set_from_class_with_nine)
{
  set<int> S;

  vector<int> V = { 22, 11, 49, 3, 19, 35, 61, 30, 41 };

  for (auto x : V)
    S.insert(x);

  ASSERT_EQ(S.size(), (int) V.size());

  for (auto x : V) {
    ASSERT_TRUE(S.contains(x));
    ASSERT_TRUE(S[x]);
  }

  ASSERT_FALSE(S.contains(0));
  ASSERT_FALSE(S[0]);
  ASSERT_FALSE(S.contains(2));
  ASSERT_FALSE(S[2]);
  ASSERT_FALSE(S.contains(4));
  ASSERT_FALSE(S[4]);
  ASSERT_FALSE(S.contains(29));
  ASSERT_FALSE(S[31]);
  ASSERT_FALSE(S.contains(40));
  ASSERT_FALSE(S[42]);
}

TEST(myset, set_no_duplicates)
{
  set<int> S;

  vector<int> V = { 22, 11, 49, 3, 19, 35, 61, 30, 41 };

  for (auto x : V)
    S.insert(x);

  // try to insert them all again:
  for (auto x : V)
    S.insert(x);

  ASSERT_EQ(S.size(), (int) V.size());

  for (auto x : V) {
    ASSERT_TRUE(S.contains(x));
    ASSERT_TRUE(S[x]);
  }
}

TEST(myset, toVector)
{
  set<int> S;

  vector<int> V = { 22, 11, 49, 3, 19, 35, 61, 30, 41 };

  for (auto x : V)
    S.insert(x);

  ASSERT_EQ(S.size(), (int) V.size());

  vector<int> V2 = S.toVector();

  ASSERT_EQ(V2.size(), V.size());

  std::sort(V.begin(), V.end());

  //
  // V and V2 should have the same elements in 
  // the same order:
  //
  auto iterV = V.begin();
  auto iterV2 = V2.begin();

  while (iterV != V.end()) {
    ASSERT_EQ(*iterV, *iterV2);

    iterV++;
    iterV2++;
  }
}

TEST(myset, copy_empty)
{
  set<int> S1;

  {
    //
    // create a new scope, which will trigger destructor:
    //
    set<int> S2 = S1;  // this will call copy constructor:

    S1.insert(123);  // this should have no impact on S2:
    S1.insert(100);
    S1.insert(150);

    ASSERT_EQ(S2.size(), 0);

    vector<int> V2 = S2.toVector();

    ASSERT_EQ((int) V2.size(), 0);
  }
}

TEST(myset, copy_constructor)
{
  set<int> S1;

  vector<int> V = { 22, 11, 49, 3, 19, 35, 61, 30, 41 };

  for (auto x : V)
    S1.insert(x);

  ASSERT_EQ(S1.size(), (int) V.size());

  {
    //
    // create a new scope, which will trigger destructor:
    //
    set<int> S2 = S1;  // this will call copy constructor:

    S1.insert(123);  // this should have no impact on S2:
    S1.insert(100);
    S1.insert(150);

    ASSERT_EQ(S2.size(), (int) V.size());

    vector<int> V2 = S2.toVector();

    ASSERT_EQ(V2.size(), V.size());

    std::sort(V.begin(), V.end());

    //
    // V and V2 should have the same elements in 
    // the same order:
    //
    auto iterV = V.begin();
    auto iterV2 = V2.begin();

    while (iterV != V.end()) {
      ASSERT_EQ(*iterV, *iterV2);

      iterV++;
      iterV2++;
    }

    S2.insert(1000);  // this should have no impact on S1:
    S2.insert(2000);
    S2.insert(3000);
    S2.insert(4000);
    S2.insert(5000);

    V.push_back(123);
    V.push_back(100);
    V.push_back(150);
  }

  //
  // the copy was just destroyed, the original set
  // should still be the same as it was earlier:
  //
  ASSERT_EQ(S1.size(), (int) V.size());

  vector<int> V2 = S1.toVector();

  ASSERT_EQ(V2.size(), V.size());

  std::sort(V.begin(), V.end());

  //
  // V and V2 should have the same elements in 
  // the same order:
  //
  auto iterV = V.begin();
  auto iterV2 = V2.begin();

  while (iterV != V.end()) {
    ASSERT_EQ(*iterV, *iterV2);

    iterV++;
    iterV2++;
  }
}

TEST(myset, find_empty)
{
  set<int> S;

  auto iter = S.find(22);
  ASSERT_TRUE(iter == S.end());
}

TEST(myset, find_one)
{
  set<int> S;

  S.insert(1234);

  auto iter = S.find(123);
  ASSERT_TRUE(iter == S.end());

  iter = S.find(1234);
  if (iter == S.end()) {  // this should not happen:
    ASSERT_TRUE(false); // fail:
  }

  ASSERT_EQ(*iter, 1234);

  iter = S.find(1235);
  ASSERT_TRUE(iter == S.end());
}

TEST(myset, find_with_set_from_class)
{
  set<int> S;

  vector<int> V = { 22, 11, 49, 3, 19, 35, 61, 30, 41 };

  for (auto x : V)
    S.insert(x);

  ASSERT_EQ(S.size(), (int) V.size());

  //
  // make sure we can find each of the values we inserted:
  //
  for (auto x : V) {
    auto iter = S.find(x);

    if (iter == S.end()) {  // this should not happen:
      ASSERT_TRUE(false); // fail:
    }

    ASSERT_EQ(*iter, x);
  }

  //
  // these searches should all fail:
  //
  auto iter = S.find(0);
  ASSERT_TRUE(iter == S.end());

  iter = S.find(-1);
  ASSERT_TRUE(iter == S.end());

  iter = S.find(1);
  ASSERT_TRUE(iter == S.end());

  iter = S.find(4);
  ASSERT_TRUE(iter == S.end());

  iter = S.find(34);
  ASSERT_TRUE(iter == S.end());

  iter = S.find(36);
  ASSERT_TRUE(iter == S.end());
}

TEST(myset, stress_test)
{
  set<long long> S;
  std::set<long long> C;

  long long N = 1000000;

  //
  // setup random number generator so tree will
  // be relatively balanced given insertion of
  // random numbers:
  //
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<long long> distrib(1, N * 100);  // inclusive

  vector<long long> V;  // collect a few values for searching:
  int count = 0;

  while (S.size() != N) {

    long long x = distrib(gen);

    S.insert(x);
    C.insert(x);

    count++;
    if (count == 1000) { // save every 1,000th value:

      V.push_back(x);
      count = 0;
    }
  }

  ASSERT_EQ(S.size(), N);

  for (auto x : V) {
    ASSERT_TRUE(S.contains(x));
  }

  ASSERT_FALSE(S.contains(0));
  ASSERT_FALSE(S.contains(-1));

  //
  // now let's compare our set to C++ set:
  //
  V.clear();
  V = S.toVector();

  ASSERT_EQ(V.size(), C.size());
  ASSERT_EQ(S.size(), (int) C.size());

  int i = 0;

  for (auto x : C) {
    ASSERT_EQ(V[i], x);
    i++;
  }
}

//
//test empty set
//
TEST(myset, myset_empty_set_Test)
{
  set<int> S; // set of integers
  vector<pair<int, int>> V; // vector of pair integers
  V = S.toPairs(-1); // call toPairs with -1 pair to non-threaded elements

  ASSERT_TRUE(V.size() == 0); //vector size should be 0
}

//
// test a set with one element
//
TEST(myset, myset_containing_one_element_Test)
{
  set<int> S;
  vector<pair<int, int>> V;

  S.insert(10);
  V = S.toPairs(-1);

  ASSERT_TRUE(V.size() == 1);
  ASSERT_TRUE(V[0].first == 10);
  ASSERT_TRUE(V[0].second == -1);
}

//
//test a set with multiple elements
//
TEST(myset, myset_containing_five_elements_Test)
{
  set<int> S; // set of integers
  vector<pair<int, int>> V; // vector to store results of toPair function

  // insert multiple integer elements
  S.insert(30);
  S.insert(15);
  S.insert(50);
  S.insert(8);
  S.insert(25);
  S.insert(70);
  S.insert(20);
  S.insert(28);
  S.insert(60);

  V = S.toPairs(-1); // pass -1 as pair to non-threaded elements

  ASSERT_TRUE(V.size() == 9);

  // check each inoder element with their threaded pair
  ASSERT_TRUE(V[0].first == 8);
  ASSERT_TRUE(V[0].second == 15);
  ASSERT_TRUE(V[1].first == 15);
  ASSERT_TRUE(V[1].second == -1);
  ASSERT_TRUE(V[2].first == 20);
  ASSERT_TRUE(V[2].second == 25);
  ASSERT_TRUE(V[3].first == 25);
  ASSERT_TRUE(V[3].second == -1);
  ASSERT_TRUE(V[4].first == 28);
  ASSERT_TRUE(V[4].second == 30);
  ASSERT_TRUE(V[5].first == 30);
  ASSERT_TRUE(V[5].second == -1);
  ASSERT_TRUE(V[6].first == 50);
  ASSERT_TRUE(V[6].second == -1);
  ASSERT_TRUE(V[7].first == 60);
  ASSERT_TRUE(V[7].second == 70);
  ASSERT_TRUE(V[8].first == 70);
  ASSERT_TRUE(V[8].second == -1);

}

//
//test a set with non-numeric values
//
TEST(myset, myset_containing_non_numeric_elements_Test)
{
  set<string> S; // set of strings
  vector<pair<string, string>> V; // vector to store results of toPair function

  //insert multiple string elements
  S.insert("Jay");
  S.insert("Brian");
  S.insert("Val");
  S.insert("Mercy");
  S.insert("Vincent");

  V = S.toPairs("None"); // pass in "None" as pair to non-threaded elements 
  
  // size of vector should equal number of elements inserted
  ASSERT_TRUE(V.size() == 5);

  // check each inoder element with their threaded pair
  ASSERT_TRUE(V[0].first == "Brian");
  ASSERT_TRUE(V[0].second == "Jay");
  ASSERT_TRUE(V[1].first == "Jay");
  ASSERT_TRUE(V[1].second == "None");
  ASSERT_TRUE(V[2].first == "Mercy");
  ASSERT_TRUE(V[2].second == "Val");
  ASSERT_TRUE(V[3].first == "Val");
  ASSERT_TRUE(V[3].second == "None");
  ASSERT_TRUE(V[4].first == "Vincent");
  ASSERT_TRUE(V[4].second == "None");
}

//
// test foreach with no element in set
//
TEST(myset, myset_foreach_emptyset)
{
  set<int> S;

  auto iter = S.find(5); // find iter for a non-existent element
  ASSERT_TRUE(iter == S.end()); // iter should be null
}

//
// test foreach with one element in set
//
TEST(myset, myset_foreach_containing_one_element)
{
  set<int> S; // set of integers

  S.insert(5); // insert one element

  auto iter = S.begin(); // find iterator for start of Set

  std::vector<int> V; // vector of integers

  while (iter != S.end())
  {
    V.push_back(iter.operator*()); //access element and push in vector
    iter.operator++(); // advance to next element
  }

  ASSERT_TRUE(V[0] == 5); // vector should now have 1 element at index 0
  ASSERT_TRUE(V.size() == 1); // vector size is now equal to 1
}

//
// test foreach with multiple elements
//
TEST(myset, myset_foreach_multipleelements)
{
  set<int> S; // set of integers
  vector<int> V; // vector of integer pairs
  

  // insert multiple elements
  S.insert(30);
  S.insert(15);
  S.insert(50);
  S.insert(8);
  S.insert(25);
  S.insert(70);
  S.insert(20);
  S.insert(28);
  S.insert(60);

  auto iter = S.begin(); // find iterator for start of Set


  // vector of ordered elements
  vector<int> orderedElements = S.toVector();

  // Iterate through the set and push each set element into the vector
  while (iter != S.end()) 
  {
    V.push_back(iter.operator*()); //access element and push in vector
    iter.operator++(); // advance to next element
  }
  
  ASSERT_TRUE(V == orderedElements); // vector V should now equal vector orderedElements
  ASSERT_TRUE(V.size() == 9); // vector V should have 9 elements
}

//
// test foreach with string elements
//
TEST(myset, myset_foreach_containing_string_elements)
{
  set<string> S; // set of strings
  vector<string> V;

  // insert couple of strings
  S.insert("banana");
  S.insert("apple");
  S.insert("orange");

  // vector to store elements in order
  vector<string> orderedFruits;

  // populate vector with elements from set S
  for (const auto& fruit : S) {
    orderedFruits.push_back(fruit);
  }

  auto iter = S.begin(); // find iterator for start of Set

  while (iter != S.end()) 
  {
    V.push_back(iter.operator*()); //access element and push in vector
    iter.operator++(); // advance to next element
  }

  ASSERT_TRUE(V.size() == 3); // should be 3
  ASSERT_TRUE(V == orderedFruits); // Both vectors should be equal right now
  ASSERT_TRUE(S.size() == 3); //size of vector and set should be 3
  ASSERT_TRUE(S.find("apple").operator!=(S.find("banana"))); //iterator for apple and banana should be different
  ASSERT_TRUE(S.find("orange").operator==(S.find("orange"))); //iterator for apple and apple should be similar
}

//
// test foreach with double elements
//
TEST(myset, myset_foreach_containing_double_elements)
{
  set<double> S; // set of doubles
  vector<double> V; // vector of doubles
  vector<double> insertV = {30.5, 15.5, 50.5, 8.5, 25.5, 70.5, 20.5, 28.5, 60.5}; // vector of doubles to insert into the set

  // insert doubles into set
  for (double d :  insertV)
  {
    S.insert(d);
  }

  auto iter = S.begin(); // find iterator for start of Set

  while(iter != S.end()) // move iterator through the set
  {
    V.push_back(iter.operator*()); // populates vector with set elements
    iter.operator++(); // advance iterator
  }

  std::sort(insertV.begin(), insertV.end()); // sort vector
  ASSERT_TRUE(V.size() == 9); // should be 9
  ASSERT_TRUE(V == insertV); // Both vectors should be equal right now
  ASSERT_TRUE(S.begin().operator*() == V[0]); // first element in set should be equal to first element in vector
  ASSERT_TRUE(S.size() == 9); // size of vector and set should be 9
  ASSERT_TRUE(S.find(20.5).operator!=(S.find(25.5))); //iterator for 20.5 and 25.5 should be different
}

//
// Stress test for the set class with a large number of random elements
//
TEST(myset, myset_for_each_stressTest)
{
  // create new set to store long long values
  set<long long> S;

  // number of elements to insert into set S
  long long N = 1000000;

  // random number generator to ensure a relatively balanced tree
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<long long> distrib(1, N * 100);  // inclusive

  // insert random values into set S until the desired size is reached
  while (S.size() != N)
  {
    long long x = distrib(gen);
    S.insert(x);
  }

  // vector to store elements in order
  vector<long long> orderedElements;

  //initialize iter for set
  auto iter = S.begin();

  // populate vector with elements from set
  while (iter != S.end())
  {
    orderedElements.push_back(iter.operator*()); //insert ptr value of iterator
    iter.operator++(); // advance iterator
  }

  // compare the two using a foreach loop
  for (const auto &element : orderedElements)
  {
    auto iter = S.find(element);
    ASSERT_TRUE(iter.operator!=(S.end()));
    ASSERT_EQ(iter.operator*(), element);
  }

  // check for match in size between set and vector
  ASSERT_EQ(S.size(), orderedElements.size());
}

//
//advancing iterator beyond the size of Set
//
TEST(myset, test_advancing_iterator_beyond_size_of_Set)
{
  //empty set
  set<int> S;
  auto iterEmpty = S.begin();
  iterEmpty.operator++();// should have no effect
  ASSERT_TRUE(iterEmpty == S.end()); // Iterator should still be at the end

  //set with one element
  set<int> S1;
  S1.insert(5);
  auto iterEnd = S1.begin();
  iterEnd.operator++();// advance iterator past first element
  ASSERT_TRUE(iterEnd == S1.end()); // reaches at the end

  // set with multiple elements
  set<int> S2;

  // insert multiple elements
  S2.insert(30);
  S2.insert(15);
  S2.insert(50);
  S2.insert(8);
  S2.insert(25);
  S2.insert(70);
  S2.insert(20);
  S2.insert(28);
  S2.insert(60);
  
  auto iterMid = S2.begin(); // starting iter

  iterMid.operator++(); // advance iterator past first element
  ASSERT_TRUE(*iterMid == 15); // second element
  iterMid.operator++(); // advance iterator past second element
  ASSERT_TRUE(*iterMid == 20); // third element
  iterMid.operator++(); // advance iterator past third element
  ASSERT_TRUE(*iterMid == 25); // fourth element
  iterMid.operator++(); // advance iterator past fourth element
  ASSERT_TRUE(*iterMid == 28); // fifth element
  iterMid.operator++(); // advance iterator past fifth element
  ASSERT_TRUE(*iterMid == 30); // sixth element
  iterMid.operator++(); // advance iterator past sixth element
  ASSERT_TRUE(*iterMid == 50); // seventh element
  iterMid.operator++(); // advance iterator past seventh element
  ASSERT_TRUE(*iterMid == 60); // eighth element
  iterMid.operator++(); // advance iterator past eighth element
  ASSERT_TRUE(*iterMid == 70); // ninth element
  iterMid.operator++(); // advance iterator past ninth element
  ASSERT_TRUE(iterMid == S2.end()); //hits end
}