import unittest


def insertion_sort(arr):
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1

        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key


def load_array(filename):
    with open(filename, "r") as file:
        return list(map(int, file.readline().split()))


class InsertionSort(unittest.TestCase):
    def test1(self):
        arr = load_array("../insert1.txt")
        insertion_sort(arr)
        self.assertEqual(arr, [1, 2, 3, 4, 5])

    def test2(self):
        arr = load_array("../insert2.txt")
        insertion_sort(arr)
        self.assertEqual(arr, [5, 6, 11, 12, 13])

    def test3(self):
        arr = load_array("../insert3.txt")
        insertion_sort(arr)
        self.assertEqual(arr, [-5, -2, -1, 0, 3, 8])


if __name__ == "__main__":
    unittest.main()
