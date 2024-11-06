import unittest


def minimum_search_cost(k, f):
    combined = list(zip(k, f))
    combined.sort(key=lambda x: x[1], reverse=True)
    total_cost = 0
    for i, (key, freq) in enumerate(combined):
        total_cost += (i + 1) * freq
    return total_cost


class TestMinimumSearchCost(unittest.TestCase):
    def test_from_file(self):
        with open('test_data.txt', 'r') as file:
            keys = file.readline().strip().split()
            frequencies = list(map(int, file.readline().strip().split()))
            expected_cost = int(file.readline().strip())
        result = minimum_search_cost(keys, frequencies)
        self.assertEqual(result, expected_cost)


if __name__ == '__main__':
    unittest.main()
