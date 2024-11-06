#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int find_max(const vector<int> &arr, int low, int high) {
  if (low == high) {
    return arr[low];
  }

  int mid = (low + high) / 2;
  int max_left = find_max(arr, low, mid);
  int max_right = find_max(arr, mid + 1, high);

  return max(max_left, max_right);
}

vector<int> read_data(const string &filename) {
  ifstream file(filename);
  int n;
  file >> n;

  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    file >> arr[i];
  }
  return arr;
}

TEST_CASE("test", "[find_max]") {
  SECTION("Test1") {
    vector<int> arr = read_data("../max1.txt");
    int result = find_max(arr, 0, arr.size() - 1);
    REQUIRE(result == 5);
  }

  SECTION("Test2") {
    vector<int> arr = read_data("../max2.txt");
    int result = find_max(arr, 0, arr.size() - 1);
    REQUIRE(result == -1);
  }
}
