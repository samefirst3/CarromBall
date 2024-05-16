import threading
import time

db = threading.Semaphore(1)
x = threading.Semaphore(1)
readerCount = 0

def reader(arg):
    global readerCount

    x.acquire()
    readerCount += 1
    print(f"Reader {arg} entered db")
    if readerCount == 1:
        db.acquire()
    print(f"Reader {arg} is reading...")
    x.release()

    time.sleep(1)  # Simulate reading time

    x.acquire()
    readerCount -= 1
    print(f"Reader {arg} exited from db")
    if readerCount == 0:
        db.release()
    x.release()

def writer(arg):
    db.acquire()
    print(f"Writer {arg} entered db")
    print(f"Writer {arg} is writing...")
    time.sleep(1)  # Simulate writing time
    db.release()
    print(f"Writer {arg} exited from db")

if __name__ == "__main__":
    readers = []
    writers = []

    for i in range(5):
        r = threading.Thread(target=reader, args=(i,))
        w = threading.Thread(target=writer, args=(i,))
        readers.append(r)
        writers.append(w)
        r.start()
        w.start()

    for r in readers:
        r.join()
    for w in writers:
        w.join()


