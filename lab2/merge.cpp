#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include <stdexcept>
#include <vector>
using namespace std;
void merge(int arr[], int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int leftArr[n1], rightArr[n2];

  for (int i = 0; i < n1; i++)
    leftArr[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    rightArr[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    if (leftArr[i] <= rightArr[j]) {
      arr[k] = leftArr[i];
      i++;
    } else {
      arr[k] = rightArr[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = leftArr[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = rightArr[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
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

TEST_CASE("Merge Sort", "[mergeSort]") {
  SECTION("test1") {
    vector<int> arr = readFromFile("../merge1.txt");
    int n = arr.size();
    mergeSort(arr.data(), 0, n - 1);

    vector<int> expected = {1, 2, 3, 4, 5};
    REQUIRE(arr == expected);
  }

  SECTION("test2") {
    vector<int> arr = readFromFile("../merge2.txt");
    int n = arr.size();
    mergeSort(arr.data(), 0, n - 1);

    vector<int> expected = {5, 6, 11, 12, 13};
    REQUIRE(arr == expected);
  }

  SECTION("test3") {
    vector<int> arr = readFromFile("../merge3.txt");
    int n = arr.size();
    mergeSort(arr.data(), 0, n - 1);

    vector<int> expected = {-5, -2, -1, 0, 3, 8};
    REQUIRE(arr == expected);
  }
}
