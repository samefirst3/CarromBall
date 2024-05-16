import threading

BUFFER_SIZE = 5
buffer = [0] * BUFFER_SIZE
in_index = 0
out_index = 0

mutex_empty = threading.Semaphore(BUFFER_SIZE)
mutex_filled = threading.Semaphore(0)

def producer():
    global in_index
    item = 1
    while True:
        mutex_empty.acquire()

        buffer[in_index] = item
        print(f"Producer produced: {item}")
        in_index = (in_index + 1) % BUFFER_SIZE

        mutex_filled.release()
        item += 1

def consumer():
    global out_index
    while True:
        mutex_filled.acquire()

        item = buffer[out_index]
        print(f"Consumer consumed: {item}")
        out_index = (out_index + 1) % BUFFER_SIZE

        mutex_empty.release()

if __name__ == "__main__":
    producer_thread = threading.Thread(target=producer)
    consumer_thread = threading.Thread(target=consumer)

    producer_thread.start()
    consumer_thread.start()

    producer_thread.join()
    consumer_thread.join()


#problem