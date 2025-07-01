def solve_partridge(N, initial_placements):
    side = N * (N + 1) // 2
    board = [[0] * side for _ in range(side)]
    inventory = {k: k for k in range(1, N + 1)}
    placements = []

    for (r, c, k) in initial_placements:
        for i in range(r, r + k):
            for j in range(c, c + k):
                board[i][j] = k
        inventory[k] -= 1
        placements.append((r, c, k))

    def find_first_empty():
        for rr in range(side):
            for cc in range(side):
                if board[rr][cc] == 0:
                    return (rr, cc)
        return None

    def backtrack():
        pos = find_first_empty()
        if pos is None:
            return True

        r0, c0 = pos
        for size in range(N, 0, -1):
            if inventory[size] == 0:
                continue
            if r0 + size > side or c0 + size > side:
                continue

            can_place = True
            for rr in range(r0, r0 + size):
                for cc in range(c0, c0 + size):
                    if board[rr][cc] != 0:
                        can_place = False
                        break
                if not can_place:
                    break
            if not can_place:
                continue

            for rr in range(r0, r0 + size):
                for cc in range(c0, c0 + size):
                    board[rr][cc] = size
            inventory[size] -= 1
            placements.append((r0, c0, size))

            if backtrack():
                return True

            placements.pop()
            inventory[size] += 1
            for rr in range(r0, r0 + size):
                for cc in range(c0, c0 + size):
                    board[rr][cc] = 0

        return False

    if backtrack():
        return placements
    else:
        return None


if __name__ == "__main__":
    N = 9
    initial = [
        (9, 0, 9),
        (18, 0, 9),
        (27, 0, 9),
        (36, 0, 9),
        (0, 15, 9),
        (0, 24, 9),
        (13, 29, 9),
        (29, 9, 8),
        (37, 9, 8),
        (30, 29, 8),
        (30, 37, 8),
        (22, 37, 8),
        (0, 37, 8),
        (8, 38, 7),
        (15, 38, 7),
        (38, 31, 7),
        (38, 38, 7),
        (13, 9, 6),
        (19, 9, 5),
        (24, 9, 5),
        (8, 33, 5),
        (0, 11, 4),
        (0, 33, 4),
        (4, 33, 4),
        (4, 12, 3)
    ]

    solution = solve_partridge(N, initial)
    if solution is None:
        print("No solution found for N =", N)
    else:
        print("Solution for N =", N, "(board is 45×45):")
        for (r, c, k) in sorted(solution, key=lambda x: (x[0], x[1], -x[2])):
            print(f"  size={k:2d} at (row={r:2d}, col={c:2d})")
