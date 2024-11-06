import unittest


def binarySearch(arr, low, high, x):

    if high >= low:

        mid = low + (high - low) // 2

        if arr[mid] == x:
            return mid

        elif arr[mid] > x:
            return binarySearch(arr, low, mid - 1, x)

        else:
            return binarySearch(arr, mid + 1, high, x)

    else:
        return -1


def read_data(filename):
    with open(filename, "r") as file:
        n = int(file.readline().strip())
        arr = list(map(int, file.readline().strip().split()))
        query = int(file.readline().strip())
    return arr, query


class Test(unittest.TestCase):

    def test1(self):
        arr, query = read_data("../binary.txt")
        result = binarySearch(arr, 0, len(arr) - 1, query)
        self.assertEqual(result, 3)

    def test2(self):
        arr, query = read_data("../binary1.txt")
        result = binarySearch(arr, 0, len(arr) - 1, query)
        self.assertEqual(result, -1)


if __name__ == "__main__":
    unittest.main()
