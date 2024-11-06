#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include <limits.h>
#include <fstream>
#include <sstream>
#include <string>
#include "catch.hpp"

using namespace std;

int solve(const vector<int>& coins, int target, int index, vector<vector<int>>& dp) {
    if (target == 0) {
        return 0;
    }
    if (dp[index][target] != -1) {
        return dp[index][target];
    }

    int include = 1 + solve(coins, target - coins[index], index, dp);
    int exclude = solve(coins, target, index + 1, dp);

    dp[index][target] = min(include, exclude);
    return dp[index][target];

}

vector<tuple<vector<int>, int, int>> readTestCases(const string& filename) {
    ifstream file(filename);
    vector<tuple<vector<int>, int, int>> testCases;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<int> coins;
            istringstream iss(line);
            int coin;
            while (iss >> coin) {
                coins.push_back(coin);
            }
            if (getline(file, line)) {
                int amount = stoi(line);
                if (getline(file, line)) {
                    int expected = stoi(line);
                    testCases.emplace_back(coins, amount, expected);
                }
            }
        }
    }
    return testCases;
}

TEST_CASE("test", "[coin]") {
    auto testCases = readTestCases("coin.txt");
    for (const auto& [coins, amount, expected] : testCases) {
        vector<vector<int>> dp(coins.size() + 1, vector<int>(amount + 1, -1));
        int result = solve(coins, amount, 0, dp);

        REQUIRE(result == expected);
    }
}

