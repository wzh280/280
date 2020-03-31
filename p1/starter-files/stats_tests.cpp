/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

void test_count_small_data_set();
void test_sum_small_data_set();
void test_mean_small_data_set();
void test_median_small_data_set();
void test_min_small_data_set();
void test_max_small_data_set();
void test_percentile_small_data_set();
void test_stdev_small_data_set();
void test_summarize_small_data_set();
void test_mode_small_data_set();
void test_mode_small_data_set();


// Add prototypes for you test functions here.

int main()
{
  test_mode_small_data_set();
  // Call your test functions here

  return 0;
}

void test_sum_small_data_set()
{
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}


// Add the test function implementations here.
void test_count_small_data_set()
{
  cout << "test_count_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(count(data) == 3);

  cout << "PASS!" << endl;
}


void test_mean_small_data_set()
{
  cout << "test_mean_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(mean(data) == 2);

  cout << "PASS!" << endl;
}

void test_max_small_data_set()
{
  cout << "test_max_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(4);

  assert(max(data) == 4);

  cout << "PASS!" << endl;
}

void test_min_small_data_set()
{
  cout << "test_min_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(4);

  assert(min(data) == 1);

  cout << "PASS!" << endl;
}


void test_median_small_data_set()
{
  cout << "test_median_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(4);

  assert(median(data) == 2);

  cout << "PASS!" << endl;
  
}


void test_percentile_small_data_set()
{
  cout << "test_percentile_small_data_set" << endl;

  vector<double> data;
  data.push_back(6);
  data.push_back(7);
  data.push_back(8);
  data.push_back(9);
  data.push_back(10);

  assert(percentile(data,0) == 6);
  assert(percentile(data,25) == 7);
  assert(percentile(data,50) == 8);
  assert(percentile(data,75) == 9);
  assert(percentile(data,100) == 10);

  cout << "PASS!" << endl;
  
}

void test_stdev_small_data_set()
{
  cout << "test_stdev_small_data_set" << endl;

  vector<double> data;
  data.push_back(6);
  data.push_back(7);
  data.push_back(8);
  data.push_back(9);
  data.push_back(10);
  const double epsilon = 0.00001;
  cout << "function out = " << stdev(data) <<endl;
  if (abs(stdev(data) - 1.58114) < epsilon) {
    assert(true);
  } else {
    cout << "not equal" << endl;

  assert(false);
  }
  

  cout << "PASS!" << endl;
  
}

void test_summarize_small_data_set()
{
  cout << "test_summarize_small_data_set" << endl;

  vector<double> data;
  data.push_back(9);
  data.push_back(10);
  data.push_back(7);
  data.push_back(8);
  
  data.push_back(8);
  vector<vector<double>> result,golden;
 
  result = summarize(data); 
  golden = {{7, 1},{8, 2},{9, 1},{10, 1}};
  for (size_t i = 0; i < result.size(); i += 1) {
    for (size_t j = 0; j < result[i].size(); j += 1) {
      if(result[i][j]!=golden[i][j]){
        assert(false);
      }
    }

  }
 
 cout << "PASS!" << endl;
  
}

void test_mode_small_data_set()
{
  cout << "test_mode_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(4);
  data.push_back(3);
  data.push_back(3);
  data.push_back(3);
  data.push_back(4);
  data.push_back(2);
  data.push_back(4);

  assert(mode(data) == 3);

  cout << "PASS!" << endl;
}
