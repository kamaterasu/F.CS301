import unittest


def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        left_half = arr[:mid]
        right_half = arr[mid:]

        merge_sort(left_half)
        merge_sort(right_half)

        i = j = k = 0

        while i < len(left_half) and j < len(right_half):
            if left_half[i] < right_half[j]:
                arr[k] = left_half[i]
                i += 1
            else:
                arr[k] = right_half[j]
                j += 1
            k += 1

        while i < len(left_half):
            arr[k] = left_half[i]
            i += 1
            k += 1

        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1


def load_array(filename):
    with open(filename, "r") as file:
        return list(map(int, file.readline().split()))


class MergeSort(unittest.TestCase):
    def test1(self):
        arr = load_array("../merge1.txt")
        merge_sort(arr)
        self.assertEqual(arr, [1, 2, 3, 4, 5])

    def test2(self):
        arr = load_array("../merge2.txt")
        merge_sort(arr)
        self.assertEqual(arr, [5, 6, 11, 12, 13])

    def test3(self):
        arr = load_array("../merge3.txt")
        merge_sort(arr)
        self.assertEqual(arr, [-5, -2, -1, 0, 3, 8])


if __name__ == "__main__":
    unittest.main()
