def lru_page_replacement(pages, capacity):
    frame = [-1] * capacity
    page_faults = 0
    recent_count = 0
    recent = [0] * capacity

    print("Incoming\tFrame")

    for page in pages:
        page_found = False

        # Check if the page is already present in the frame
        for j in range(capacity):
            if frame[j] == page:
                page_found = True
                recent[j] = recent_count
                recent_count += 1
                break

        if not page_found:
            # Page is not present, find the least recently used page in the frame
            lru_index = 0
            for j in range(1, capacity):
                if recent[j] < recent[lru_index]:
                    lru_index = j

            # Replace the least recently used page with the new page
            frame[lru_index] = page
            recent[lru_index] = recent_count
            recent_count += 1
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

    # Input the sequence of page requests
    pages = []
    print("Enter the sequence of page requests:")
    for _ in range(n):
        pages.append(int(input()))

    capacity = int(input("Enter the number of frames: "))

    lru_page_replacement(pages, capacity)


