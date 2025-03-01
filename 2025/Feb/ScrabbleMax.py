# Define Scrabble letter values
scrabble_scores = {
    'A': 1, 'E': 1, 'I': 1, 'O': 1, 'U': 1, 'L': 1, 'N': 1, 'S': 1, 'T': 1, 'R': 1,
    'D': 2, 'G': 2,
    'B': 3, 'C': 3, 'M': 3, 'P': 3,
    'F': 4, 'H': 4, 'V': 4, 'W': 4, 'Y': 4,
    'K': 5,
    'J': 8, 'X': 8,
    'Q': 10, 'Z': 10
}

def highest_scrabble_letters(input_string):
    best_score = 0
    best_letters = []  # To store letters (keeping their original case if needed)
    
    for char in input_string:
        upper_char = char.upper()
        if upper_char in scrabble_scores:
            score = scrabble_scores[upper_char]
            if score > best_score:
                best_score = score
                best_letters = [char]
            elif score == best_score:
                # Avoid duplicate entries if needed (optional)
                if char not in best_letters:
                    best_letters.append(char)
    return best_letters, best_score

def main():
    while True:
        user_input = input("Enter a string (or type 'quit' to exit): ")
        if user_input.lower() == "quit":
            print("Exiting the program. Goodbye!")
            break
        
        letters, score = highest_scrabble_letters(user_input)
        if letters:
            if len(letters) == 1:
                print(f"The highest value scrabble letter is '{letters[0]}' with a score of {score}.")
            else:
                letters_formatted = ", ".join(f"'{letter}'" for letter in letters)
                print(f"The highest value scrabble letters are {letters_formatted} with a score of {score}.")
        else:
            print("No valid scrabble letters found in the input.")

if __name__ == "__main__":
    main()
