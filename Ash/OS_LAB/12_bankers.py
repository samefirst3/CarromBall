def is_safe(processes, available, max_demand, alloc, need, n, m):
    work = available[:]
    finish = [0] * n
    safe_seq = []

    count = 0
    while count < n:
        found = False
        for i in range(n):
            if not finish[i]:
                if all(need[i][j] <= work[j] for j in range(m)):
                    for j in range(m):
                        work[j] += alloc[i][j]
                    finish[i] = 1
                    safe_seq.append(processes[i])
                    count += 1
                    found = True
        if not found:
            return False, []
    return True, safe_seq

def main():
    n = int(input("Enter the number of processes: "))
    m = int(input("Enter the number of resources: "))

    processes = list(map(int, input("Enter the process IDs: ").split()))
    available = list(map(int, input("Enter the available resources: ").split()))

    max_demand = []
    print("Enter the maximum demand matrix:")
    for _ in range(n):
        max_demand.append(list(map(int, input().split())))

    alloc = []
    print("Enter the allocation matrix:")
    for _ in range(n):
        alloc.append(list(map(int, input().split())))

    need = [[max_demand[i][j] - alloc[i][j] for j in range(m)] for i in range(n)]

    is_safe_state, safe_seq = is_safe(processes, available, max_demand, alloc, need, n, m)

    if is_safe_state:
        print("System is in a safe state.\nSafe sequence: ", " -> ".join(map(str, safe_seq)))
    else:
        print("System is not in a safe state.")

if __name__ == "__main__":
    main()


