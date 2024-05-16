import threading

BUFFER_SIZE = 5
buffer = [0] * BUFFER_SIZE
in_index = 0
out_index = 0

mutex_empty = threading.Semaphore(BUFFER_SIZE)
mutex_filled = threading.Semaphore(0)
buffer_lock = threading.Lock()

def producer():
    global in_index
    item = 1
    while True:
        mutex_empty.acquire()
        with buffer_lock:
            buffer[in_index] = item
            print(f"Producer produced: {item}")
            in_index = (in_index + 1) % BUFFER_SIZE
        mutex_filled.release()
        item += 1

def consumer():
    global out_index
    while True:
        mutex_filled.acquire()
        with buffer_lock:
            item = buffer[out_index]
            print(f"Consumer consumed: {item}")
            out_index = (out_index + 1) % BUFFER_SIZE
        mutex_empty.release()

def reader(reader_id):
    global readerCount
    with x_mutex:
        readerCount += 1
        if readerCount == 1:
            db_mutex.acquire()
    print(f"Reader {reader_id} entered db")
    print(f"Reader {reader_id} is reading...")
    with x_mutex:
        readerCount -= 1
        if readerCount == 0:
            db_mutex.release()

def writer(writer_id):
    db_mutex.acquire()
    print(f"Writer {writer_id} entered db")
    print(f"Writer {writer_id} is writing...")
    print(f"Writer {writer_id} exited from db")
    db_mutex.release()

if __name__ == "__main__":
    db_mutex = threading.Lock()
    x_mutex = threading.Lock()
    readerCount = 0

    readers = []
    writers = []

    for i in range(5):
        reader_thread = threading.Thread(target=reader, args=(i,))
        writer_thread = threading.Thread(target=writer, args=(i,))
        readers.append(reader_thread)
        writers.append(writer_thread)
        reader_thread.start()
        writer_thread.start()

    for reader_thread in readers:
        reader_thread.join()
    for writer_thread in writers:
        writer_thread.join()


