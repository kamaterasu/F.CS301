#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include <vector>
using namespace std;
int binarySearch(int arr[], int low, int high, int x) {
  if (high >= low) {
    int mid = low + (high - low) / 2;

    if (arr[mid] == x)
      return mid;

    if (arr[mid] > x)
      return binarySearch(arr, low, mid - 1, x);

    return binarySearch(arr, mid + 1, high, x);
  }
  return -1;
}

vector<int> readData(const string &filename, int &query) {
  ifstream infile(filename);
  if (!infile) {
    throw runtime_error("Unable to open file");
  }

  int n;
  infile >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    infile >> arr[i];
  }

  infile >> query;
  infile.close();
  return arr;
}

TEST_CASE("Test", "[binarySearch]") {
  SECTION("test1") {
    int query;
    vector<int> arr = readData("../binary.txt", query);
    REQUIRE(binarySearch(arr.data(), 0, arr.size() - 1, query) == 3);
  }
  SECTION("test2") {
    int query;
    vector<int> arr = readData("../binary1.txt", query);
    REQUIRE(binarySearch(arr.data(), 0, arr.size() - 1, query) == -1);
  }
}
