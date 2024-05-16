def sort(at, bt, n):
    for i in range(n - 1):
        for j in range(i + 1, n):
            if at[i] > at[j]:
                at[i], at[j] = at[j], at[i]
                bt[i], bt[j] = bt[j], bt[i]

def fcfs():
    n = int(input("Enter the number of processes: "))

    pid = list(range(1, n + 1))
    at = []
    bt = []
    ct = [0] * n
    ta = [0] * n
    wt = [0] * n
    f = [0] * n
    k = [0] * n

    for i in range(n):
        at.append(int(input(f"Enter arrival time for process {i + 1}: ")))
        bt.append(int(input(f"Enter burst time for process {i + 1}: ")))
        k[i] = bt[i]

    sort(at, bt, n)

    st = 0
    tot = 0

    while True:
        c = -1  # Initialize 'c' to an invalid index
        if tot == n:
            break

        for i in range(n):
            if at[i] <= st and f[i] == 0:
                c = i  # Store the index of the process with the shortest burst time
                break

        if c == -1:
            st += 1
        else:
            st += bt[c]
            ct[c] = st
            f[c] = 1
            tot += 1

    for i in range(n):
        ta[i] = ct[i] - at[i]
        wt[i] = ta[i] - bt[i]

    print("\nPid|Arrival| Burst |Complete | Turn|Waiting")
    for i in range(n):
        print(f"{pid[i]}\t{at[i]}\t{bt[i]}\t{ct[i]}\t{ta[i]}\t{wt[i]}")

if __name__ == "__main__":
    fcfs()


