def find_optimal_page(pages, frame, n, capacity, index):
    res = -1
    farthest = index
    for i in range(capacity):
        j = index
        while j < n:
            if frame[i] == pages[j]:
                if j > farthest:
                    farthest = j
                    res = i
                break
            j += 1

        # If the page is not present in the future pages, return it.
        if j == n:
            return i

    return 0 if res == -1 else res

def optimal_page_replacement(pages, n, capacity):
    frame = [-1] * capacity
    page_faults = 0

    print("Incoming\tFrame")

    for i in range(n):
        page = pages[i]
        page_found = False

        # Check if the page is already present in the frame
        for j in range(capacity):
            if frame[j] == page:
                page_found = True
                break

        if not page_found:
            replace_index = find_optimal_page(pages, frame, n, capacity, i)
            frame[replace_index] = page
            page_faults += 1

        # Print the current page and frame status
        print(f"{page}\t\t", end="")
        for j in range(capacity):
            if frame[j] != -1:
                print(f"{frame[j]}\t\t", end="")
            else:
                print("-\t\t", end="")
        print()

    print(f"\nTotal Page Faults: {page_faults}")

if __name__ == "__main__":
    n = int(input("Enter the number of pages: "))

    pages = []
    print("Enter the sequence of page requests:")
    for _ in range(n):
        pages.append(int(input()))

    capacity = int(input("Enter the number of frames: "))

    optimal_page_replacement(pages, n, capacity)


