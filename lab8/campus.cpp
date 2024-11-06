#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

int distance(pair<int, int> d1, pair<int, int> d2) {
    return abs(d1.first - d2.first) + abs(d1.second - d2.second);
}

vector<int> assign_bikes(vector<pair<int, int>>& students, vector<pair<int, int>>& bikes) {
    int n = students.size();
    int m = bikes.size();
    
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int dist = distance(students[i], bikes[j]);
            pq.emplace(dist, i, j);
        }
    }
    
    vector<int> result(n, -1);
    vector<bool> bike_taken(m, false);
    vector<bool> student_assigned(n, false);
    
    while (!pq.empty()) {
        auto [dist, student, bike] = pq.top();
        pq.pop();
        
        if (!student_assigned[student] && !bike_taken[bike]) {
            result[student] = bike;
            student_assigned[student] = true;
            bike_taken[bike] = true;
        }
    }
    
    return result;
}

void read_input(const string& filename, vector<vector<pair<int, int>>>& test_students, vector<vector<pair<int, int>>>& test_bikes) {
    ifstream infile(filename);
    string line;
    int t, n, m;
    
    getline(infile, line);
    stringstream ss(line);
    ss >> t;
    
    for (int i = 0; i < t; ++i) {
        vector<pair<int, int>> students;
        vector<pair<int, int>> bikes;
        
        getline(infile, line);
        stringstream ss(line);
        ss >> n >> m;
        
        for (int j = 0; j < n; ++j) {
            int x, y;
            getline(infile, line);
            stringstream ss(line);
            ss >> x >> y;
            students.emplace_back(x, y);
        }
        
        for (int j = 0; j < m; ++j) {
            int x, y;
            getline(infile, line);
            stringstream ss(line);
            ss >> x >> y;
            bikes.emplace_back(x, y);
        }
        
        test_students.push_back(students);
        test_bikes.push_back(bikes);
    }
}

TEST_CASE("test", "[test]") {
    vector<vector<pair<int, int>>> test_students;
    vector<vector<pair<int, int>>> test_bikes;
    read_input("input.txt", test_students, test_bikes);
    
    REQUIRE(test_students.size() == test_bikes.size());
    
    for (size_t i = 0; i < test_students.size(); ++i) {
        vector<int> result = assign_bikes(test_students[i], test_bikes[i]);
        REQUIRE(result == expected_results[i]);
    }
}

