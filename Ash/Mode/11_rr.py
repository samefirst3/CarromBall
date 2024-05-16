import random

class Process:
    def __init__(self, pid, bt, at):
        self.pid = pid
        self.bt = bt
        self.at = at
        self.rt = bt  # remaining time
        self.ft = 0
        self.tat = 0
        self.wt = 0

def sort_processes(processes):
    processes.sort(key=lambda x: (x.at, x.bt))

def count_iterations(processes, tq):
    total_iterations = 0
    for p in processes:
        if p.bt % tq != 0:
            total_iterations += (p.bt // tq) + 1
        else:
            total_iterations += (p.bt // tq)
    return total_iterations

def print_chart(processes):
    print("\n\t+", end="")
    for p in processes:
        print("---" * p.bt + "+", end="")
    print("\n\t|", end="")
    for p in processes:
        print(f" P{p.pid}", end="")
        for _ in range(1, p.bt):
            print("   ", end="")
        print("|", end="")
    print("\n\t+", end="")
    for p in processes:
        print("---" * p.bt + "+", end="")
    
    check = 0
    print(f"\n\t{processes[0].at}", end="")
    if processes[0].at > 9:
        check = 1
    for p in processes:
        for _ in range(1, p.bt + 1):
            if check == 1:
                print("  ", end="")
                check = 0
            else:
                print("   ", end="")
        print(f"{p.ft}", end="")
        if p.ft > 9:
            check = 1

def execute_processes(processes, exec, tq):
    t = 0
    j = 0
    for i in range(len(exec)):
        if i == 0:
            t = processes[i].at
        if processes[j].rt > 0:
            exec[i] = Process(processes[j].pid, processes[j].bt, processes[j].at)
            if processes[j].rt < tq:
                t += processes[j].rt
                exec[i].bt = processes[j].rt
                processes[j].rt = 0
                processes[j].ft = t
            else:
                t += tq
                processes[j].rt -= tq
                if processes[j].rt == 0:
                    processes[j].ft = t
                exec[i].bt = tq
            exec[i].ft = t
            exec[i].rt = processes[j].rt
        else:
            i -= 1
        j += 1
        if j == len(processes):
            j = 0
    return t

def print_table(processes):
    avgw = 0
    avgt = 0
    print("\n\n\tpid\tAt\tBt\tFt\tTAt\tWt\n")
    for p in processes:
        p.tat = p.ft - p.at
        p.wt = p.tat - p.bt
        avgw += p.wt
        avgt += p.tat
        if p.pid != -1:
            print(f"\n\t{p.pid}\t{p.at}\t{p.bt}\t{p.ft}\t {p.tat}\t{p.wt}\n")
    avgw /= len(processes)
    avgt /= len(processes)
    print(f"\n\n\tAverage waiting time: {avgw:.2f} units\n\tAverage turn-around time: {avgt:.2f} units")

def main():
    print("\n\t\t\t\tRound Robin\n\n\t Enter the total number of processes: ", end="")
    n = int(input())
    processes = []

    print("\n\t Enter the time quantum: ", end="")
    tq = int(input())

    print("\n\t Enter the following data for each process: ")
    for i in range(n):
        print(f"\n\t Process {i + 1}:\n\tArrival time: ", end="")
        at = int(input())
        print("\tBurst time: ", end="")
        bt = int(input())
        processes.append(Process(i + 1, bt, at))

    sort_processes(processes)

    u = count_iterations(processes, tq)
    exec = [None] * u

    t = execute_processes(processes, exec, tq)
    print_table(processes)
    print("\n\n\t Gnatt chart\n")
    print_chart(exec)

    upbt = 4
    lowbt = 1

    s = t + 2
    print("\n\n\n\t\t\tRandom CPU Burst\n\n\t Enter the total number of processes: ", end="")
    m = int(input())
    random_processes = []
    for i in range(m):
        rand_at = s
        s += 1
        rand_bt = random.randint(lowbt, upbt)
        random_processes.append(Process(i + 1, rand_bt, rand_at))

    sort_processes(random_processes)

    v = count_iterations(random_processes, tq)
    exek = [None] * v

    t = execute_processes(random_processes, exek, tq)
    print_table(random_processes)
    print("\n\n\t Gnatt chart\n")
    print_chart(exek)

    print("\n\n\n\t Combined Gnatt chart\n")
    print_chart(exec)
    print("\n\n\t\t--IO of 2 units--\n")
    print_chart(exek)

if __name__ == "__main__":
    main()


