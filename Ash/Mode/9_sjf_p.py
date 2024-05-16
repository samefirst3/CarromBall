def main():
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
        burst_time = int(input(f"Enter burst time for process {i + 1}: "))
        bt.append(burst_time)
        k[i] = burst_time

    st = 0
    tot = 0

    while True:
        min_bt = float('inf')
        c = n
        if tot == n:
            break

        for i in range(n):
            if at[i] <= st and f[i] == 0 and bt[i] < min_bt:
                min_bt = bt[i]
                c = i

        if c == n:
            st += 1
        else:
            bt[c] -= 1
            st += 1
            if bt[c] == 0:
                ct[c] = st
                f[c] = 1
                tot += 1

    for i in range(n):
        ta[i] = ct[i] - at[i]
        wt[i] = ta[i] - k[i]

    print("\nPid|Arrival| Burst |Complete | Turn|Waiting")
    for i in range(n):
        print(f"{pid[i]}\t{at[i]}\t{k[i]}\t{ct[i]}\t{ta[i]}\t{wt[i]}")

if __name__ == "__main__":
    main()


