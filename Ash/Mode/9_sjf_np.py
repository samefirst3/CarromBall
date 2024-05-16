def main():
    n = int(input("Enter the number of processes: "))

    pid = list(range(1, n + 1))
    at = []
    bt = []
    ct = [0] * n
    ta = [0] * n
    wt = [0] * n
    f = [0] * n
    st = 0
    tot = 0

    for i in range(n):
        at.append(int(input(f"Enter arrival time for process {i + 1}: ")))
        bt.append(int(input(f"Enter burst time for process {i + 1}: ")))

    while True:
        c = n
        min_bt = 999
        if tot == n:
            break

        for i in range(n):
            if at[i] <= st and f[i] == 0 and bt[i] < min_bt:
                min_bt = bt[i]
                c = i

        if c == n:
            st += 1
        else:
            ct[c] = st + bt[c]
            st += bt[c]
            ta[c] = ct[c] - at[c]
            wt[c] = ta[c] - bt[c]
            f[c] = 1
            tot += 1

    print("\nPid|Arrival| Burst |Complete | Turn|Waiting")
    for i in range(n):
        print(f"{pid[i]}\t{at[i]}\t{bt[i]}\t{ct[i]}\t{ta[i]}\t{wt[i]}")

if __name__ == "__main__":
    main()


