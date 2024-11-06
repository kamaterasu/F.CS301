#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include <vector>
using namespace std;
void insertionSort(int arr[], int n) {
  for (int i = 1; i < n; ++i) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

vector<int> readFromFile(const string &fileName) {
  ifstream file(fileName);
  vector<int> arr;
  int num;

  if (file.is_open()) {
    while (file >> num) {
      arr.push_back(num);
    }
    file.close();
  } else {
    throw runtime_error("Unable to open file");
  }

  return arr;
}

TEST_CASE("Test", "[insertionSort]") {
  SECTION("test 1") {
    vector<int> arr = readFromFile("../insert1.txt");
    int n = arr.size();
    insertionSort(arr.data(), n);

    vector<int> expected = {1, 2, 3, 4, 5};
    REQUIRE(arr == expected);
  }

  SECTION("test 2") {
    vector<int> arr = readFromFile("../insert2.txt");
    int n = arr.size();
    insertionSort(arr.data(), n);

    vector<int> expected = {5, 6, 11, 12, 13};
    REQUIRE(arr == expected);
  }

  SECTION("test 3") {
    vector<int> arr = readFromFile("../insert3.txt");
    int n = arr.size();
    insertionSort(arr.data(), n);

    vector<int> expected = {-5, -2, -1, 0, 3, 8};
    REQUIRE(arr == expected);
  }
}
