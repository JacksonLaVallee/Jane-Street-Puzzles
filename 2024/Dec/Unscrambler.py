import os

def recurse(nums, current, used, file):
    if len(nums) == len(current):
        file.write(''.join(current) + '\n')
        return

    for i in range(len(nums)):
        if used[i] or (i > 0 and nums[i] == nums[i - 1] and not used[i - 1]):
            continue
        used[i] = True
        current.append(nums[i])
        recurse(nums, current, used, file)
        current.pop()
        used[i] = False

def main():
    s = "GOMIINNESSS"
    nums = sorted(list(s))  # Sort the characters to handle duplicates

    used = [False] * len(nums)
    unique_starting_letters = sorted(set(nums))

    for letter in unique_starting_letters:
        filename = f'permutations_{letter}.txt'
        with open(filename, 'w') as file:
            for i in range(len(nums)):
                if nums[i] == letter and not used[i]:
                    used[i] = True
                    recurse(nums, [nums[i]], used, file)
                    used[i] = False

if __name__ == "__main__":
    main()