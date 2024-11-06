try:
    with open("../test.txt", "r") as file:
        content = file.read()
    print(content)
except Exception as e:
    print(e)