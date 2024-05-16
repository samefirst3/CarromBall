import threading
import time
from threading import Semaphore

bs = 8

es = Semaphore(bs)
fs = Semaphore(0)
buffer = [0] * bs
in_index = 0
out_index = 0

def producer():
    global in_index
    item = 1

    while True:
        print(f"Produced item: {item}")

        es.acquire()

        buffer[in_index] = item
        in_index = (in_index + 1) % bs

        fs.release()

        item += 1
        time.sleep(1)  # Added sleep to simulate time taken to produce an item

def consumer():
    global out_index

    while True:
        fs.acquire()

        consumed = buffer[out_index]
        print(f"Consumed item: {consumed}")

        out_index = (out_index + 1) % bs

        es.release()
        time.sleep(1)  # Added sleep to simulate time taken to consume an item

if __name__ == "__main__":
    producer_thread = threading.Thread(target=producer)
    consumer_thread = threading.Thread(target=consumer)

    producer_thread.start()
    consumer_thread.start()

    producer_thread.join()
    consumer_thread.join()


