import random

def generate_large_numbers_and_verify():
    with open("test.in", "w") as infile, open("test.out", "w") as outfile:
        for _ in range(1000):
            num1 = random.randint(10**50, 10**100 - 1)
            num2 = random.randint(10**50, 10**100 - 1)
            result = num1 * num2

            infile.write(f"{num1} {num2}\n")
            outfile.write(f"{result}\n")

if __name__ == "__main__":
    generate_large_numbers_and_verify()

