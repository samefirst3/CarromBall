def fifo_page_replacement(pages, capacity):
    frame = [-1] * capacity
    page_faults = 0
    front = 0  # Pointer to the first page in the frame

    print("Incoming\tFrame")

    for page in pages:
        page_found = False

        # Check if the page is already present in the frame
        if page in frame:
            page_found = True

        if not page_found:
            # Page is not present, replace the oldest page in the frame
            frame[front] = page
            front = (front + 1) % capacity
            page_faults += 1

        # Print the current page and frame status
        print(f"{page}\t\t", end="")
        for f in frame:
            if f != -1:
                print(f"{f}\t\t", end="")
            else:
                print("-\t\t", end="")
        print()

    print(f"\nTotal Page Faults: {page_faults}")

if __name__ == "__main__":
    # Input the number of pages
    n = int(input("Enter the number of pages: "))

    # Input the sequence of page requests
    pages = list(map(int, input("Enter the sequence of page requests: ").split()))

    # Input the number of frames
    capacity = int(input("Enter the number of frames: "))

    fifo_page_replacement(pages, capacity)


