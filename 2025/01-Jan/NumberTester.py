def test12345679():
    n = 12345679
    x = 1

    completed = ["061728395", 395061728, 728395061, 950617283, 283950617, 617283950, 839506172, 506172839]

    while (n * x < 99999999): x += 1
    while (n * x < 1000000000):
        product = n * x
        if str(product)[6] != '4':
            if len(set(str(product))) == len(str(product)) and '4' not in str(product):
                valid = True
                for c in completed:
                    for i in range(9):  
                        if str(product)[i] == str(c)[i]:
                            valid = False
                            break
                    if not valid: break
                if valid: print(product)
                        
        x += 1

def test333667():
    n = 333667
    x = 1
 
    while (n * x < 9999999): x += 1
    while (n * x < 1000000000):
        product = n * x
        if str(product)[::-1][0] == '5' and str(product)[::-1][4] == '2':
            if len(set(str(product))) == len(str(product)):
                print(product)
        x += 1  

test12345679()

# ANS IS 283950617
# Last Solver is Alain Verberkmoes of third row and Andre Fioravanti of second row and vsh of first row