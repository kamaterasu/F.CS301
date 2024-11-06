#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Item {
    double weight, value;

    Item(double w, double v) : weight(w), value(v) {}
};

bool compare(Item a, Item b) {
    double r1 = a.value / a.weight;
    double r2 = b.value / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int W, vector<Item> &items) {
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;
    int currentWeight = 0;

    for (Item item : items) {
        if (currentWeight + item.weight <= W) {
            currentWeight += item.weight;
            totalValue += item.value;
        } else {
            int remainingCapacity = W - currentWeight;
            totalValue += (item.value / item.weight) * remainingCapacity;
            break;
        }
    }

    return totalValue;
}

vector<tuple<int, double, vector<Item>, double>> loadTestCases(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return {};
    }

    vector<tuple<int, double, vector<Item>, double>> testCases;

    int n;
    double W, expected;
    while (file >> n >> W) {
        vector<Item> items;
        for (int i = 0; i < n; ++i) {
            double value, weight;
            file >> value >> weight;
            items.push_back(Item(weight, value));
        }
        file >> expected;
        testCases.push_back(make_tuple(n, W, items, expected));
    }

    file.close();
    return testCases;
}

TEST_CASE("Test case", "[knapsack]") {
    vector<tuple<int, double, vector<Item>, double>> testCases = loadTestCases("test.txt");

    for (size_t i = 0; i < testCases.size(); ++i) {
        int n = get<0>(testCases[i]);
        double W = get<1>(testCases[i]);
        vector<Item> items = get<2>(testCases[i]);
        double expected = get<3>(testCases[i]);

        SECTION("Test case " + to_string(i + 1)) {
            double result = fractionalKnapsack(W, items);
            REQUIRE(result == Approx(expected).margin(0.01));
        }
    }
}
