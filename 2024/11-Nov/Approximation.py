import random

print("Estimating Jane Street November 2024 Puzzle")

count = 0
n = 10

for j in range (10) :
    

    for i in range(n):
        x = random.random()
        y = random.random()
        if not (y < x and 0 < x < .5 or y < 1 - x and .5 < x < 1):
            continue

        a = random.random()
        b = random.random()

        xintercept = (a**2 + b**2 - x**2 - y**2)/(2*(a-x))

        if xintercept < 0 or xintercept > 1:
            continue

        count += 1

    print(str(j) + ": n = " + str(n) + " guess = " + str(4 * count/n))

    n *= 10
    count = 0

