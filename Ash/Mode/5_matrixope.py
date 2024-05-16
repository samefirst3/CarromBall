import threading

matA = [[2, 2, 2],
        [2, 2, 2],
        [2, 2, 2]]

matB = [[3, 2, 2],
        [3, 3, 2],
        [2, 2, 2]]

matC = [[0, 0, 0],
        [0, 0, 0],
        [0, 0, 0]]

ROW = 3
COLUMN = 3
MAX_THREADS = 3
k = 0
k_lock = threading.Lock()

def display(mat):
    for row in mat:
        print(" ".join(map(str, row)))
    print()

def mat_mul():
    global k
    with k_lock:
        row = k
        k += 1
    for i in range(ROW):
        for j in range(COLUMN):
            matC[row][i] += (matA[row][j] * matB[j][i])

def mat_add():
    global k
    with k_lock:
        row = k
        k += 1
    for i in range(ROW):
        matC[row][i] = (matA[row][i] + matB[row][i])

def mat_sub():
    global k
    with k_lock:
        row = k
        k += 1
    for i in range(ROW):
        matC[row][i] = (matA[row][i] - matB[row][i])

def main():
    global k
    ch = int(input("\nEnter operation- \n1. Mul\n2. Add\n3. Sub\n"))

    if ch == 1:
        k = 0
        print("matrix A-")
        display(matA)

        print("matrix B-")
        display(matB)

        threads = []
        for i in range(MAX_THREADS):
            thread = threading.Thread(target=mat_mul)
            threads.append(thread)
            thread.start()
            print(f"\nThread{i} created successfully")

        for thread in threads:
            thread.join()

        print("\nmatrix C-")
        display(matC)

    elif ch == 2:
        k = 0
        print("matrix A-")
        display(matA)

        print("matrix B-")
        display(matB)

        threads = []
        for i in range(MAX_THREADS):
            thread = threading.Thread(target=mat_add)
            threads.append(thread)
            thread.start()
            print(f"\nThread{i} created successfully")

        for thread in threads:
            thread.join()

        print("\nmatrix C-")
        display(matC)

    elif ch == 3:
        k = 0
        print("matrix A-")
        display(matA)

        print("matrix B-")
        display(matB)

        threads = []
        for i in range(MAX_THREADS):
            thread = threading.Thread(target=mat_sub)
            threads.append(thread)
            thread.start()
            print(f"\nThread{i} created successfully")

        for thread in threads:
            thread.join()

        print("\nmatrix C-")
        display(matC)

if __name__ == "__main__":
    main()


