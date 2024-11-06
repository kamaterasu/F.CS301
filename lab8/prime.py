import unittest

def count_primes(n):
    if n < 2:
        return 0
    
    dp = [True] * (n + 1)
    dp[0], dp[1] = False, False
    
    for i in range(2, n+1):
        if dp[i]:
            for j in range(2 * i, n + 1, i):
                dp[j] = False
    
    return sum(dp)

def read_test_cases(filename):
    test_cases = []
    with open(filename, 'r') as file:
        for line in file:
            if line.strip(): 
                n, expected = map(int, line.split())
                test_cases.append((n, expected))
    return test_cases

class Test(unittest.TestCase):
    pass

def add_test_case(n, expected):
    def test_case(self):
        self.assertEqual(count_primes(n), expected)
    return test_case

def load_test_cases():
    test_cases = read_test_cases('prime.txt')
    for i, (n, expected) in enumerate(test_cases):
        test_name = f'test_case_{i}_{n}'
        test_case = add_test_case(n, expected)
        setattr(Test, test_name, test_case)

load_test_cases()

if __name__ == '__main__':
    unittest.main()

