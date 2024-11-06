import unittest


def find_max(arr, low, high):
    if low == high:
        return arr[low]

    mid = (low + high) // 2

    max_left = find_max(arr, low, mid)
    max_right = find_max(arr, mid + 1, high)

    return max(max_left, max_right)


def read_data(filename):
    with open(filename, "r") as file:
        line = file.readline().strip()
        array_part, expected_part = line.split("),(")
        arr = list(map(int, array_part.strip("()").split(",")))
        expected = int(expected_part.strip("()"))
    return arr, expected


class Test(unittest.TestCase):

    def test1(self):
        arr, expected = read_data("../max1.txt")
        result = find_max(arr, 0, len(arr) - 1)
        self.assertEqual(result, expected)

    def test2(self):
        arr, expected = read_data("../max2.txt")
        result = find_max(arr, 0, len(arr) - 1)
        self.assertEqual(result, expected)


if __name__ == "__main__":
    unittest.main()
