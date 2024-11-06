#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

namespace search_cost {
    // Function to calculate minimum search cost
    int minimum_search_cost(const vector<int>& keys, const vector<int>& freqs) {
        // Create a vector of pairs (frequency, key)
        vector<pair<int, int>> paired;
        for (size_t i = 0; i < keys.size(); ++i) {
            paired.emplace_back(freqs[i], keys[i]);
        }

        // Sort pairs by frequency in descending order
        sort(paired.begin(), paired.end(), greater<>());

        // Calculate total minimum search cost
        int cost = 0;
        for (size_t depth = 0; depth < paired.size(); ++depth) {
            cost += paired[depth].first * (depth + 1); // depth + 1 gives the depth level
        }

        return cost;
    }

    // Helper function to read test data from a file
    void read_test_data(const string& filename, vector<int>& keys, vector<int>& freqs, int& expected_cost) {
        ifstream infile(filename);
        if (!infile.is_open()) {
            throw runtime_error("Could not open input file.");
        }

        int n;
        infile >> n;  // Read number of keys

        keys.resize(n);
        freqs.resize(n);

        for (int i = 0; i < n; ++i) {
            infile >> keys[i]; // Read keys
        }

        for (int i = 0; i < n; ++i) {
            infile >> freqs[i]; // Read frequencies
        }

        infile >> expected_cost; // Read expected cost
    }
}

// Catch2 Test Cases
TEST_CASE("Minimum search cost calculation from input file") {
    vector<int> keys;
    vector<int> freqs;
    int expected_cost;

    // Reading test data from file
    search_cost::read_test_data("test_input.txt", keys, freqs, expected_cost);

    // Compute the minimum search cost
    int calculated_cost = search_cost::minimum_search_cost(keys, freqs);

    // Check if the calculated cost matches the expected value
    REQUIRE(calculated_cost == expected_cost);
}

