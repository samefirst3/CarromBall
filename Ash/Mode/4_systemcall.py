import os
import sys
import stat

# Function prototypes
def process_system_calls():
    child_pid = os.fork()

    if child_pid < 0:
        print("fork error")
        return
    elif child_pid == 0:
        # Child process
        print(f"Child process: PID = {os.getpid()}")
        os._exit(0)
    else:
        # Parent process
        print(f"Parent process: PID = {os.getpid()}, Child PID = {child_pid}")
        os.wait()

def file_system_calls():
    try:
        # Create and open a new file
        fd = os.open("hello.txt", os.O_CREAT | os.O_RDWR, 0o600)

        # Write data to the file
        bytes_written = os.write(fd, b"Hello, this is a sample file!")

        # Read data from the file
        os.lseek(fd, 0, os.SEEK_SET)  # Move the file offset to the beginning
        buffer = os.read(fd, 100)

        print(f"Read from file: {buffer.decode()}")

        # Close the file
        os.close(fd)

        # Remove the file
        os.unlink("hello.txt")
    except OSError as e:
        print(f"Error: {e}")

def communication_system_calls():
    try:
        # Create a pipe
        fd = os.pipe()

        child_pid = os.fork()

        if child_pid < 0:
            print("fork error")
            return
        elif child_pid == 0:
            # Child process - write to the pipe
            os.close(fd[0])  # Close the read end of the pipe
            message = b"Hello from the child process!"
            os.write(fd[1], message)
            os.close(fd[1])  # Close the write end of the pipe
        else:
            # Parent process - read from the pipe
            os.close(fd[1])  # Close the write end of the pipe
            buffer = os.read(fd[0], 100)
            os.close(fd[0])  # Close the read end of the pipe

            print(f"Message received from child process: {buffer.decode()}")

            os.wait()
    except OSError as e:
        print(f"Error: {e}")

def information_system_calls():
    try:
        file_stat = os.stat("hello.txt")

        print("Information about 'hello.txt':")
        print(f"File Size: {file_stat.st_size} bytes")
        print(f"Number of Links: {file_stat.st_nlink}")
        print(f"File inode: {file_stat.st_ino}")
        print(f"File Permissions: {oct(file_stat.st_mode)}")
        print(f"File UID: {file_stat.st_uid}")
        print(f"File GID: {file_stat.st_gid}")
    except OSError as e:
        print(f"Error: {e}")

def main():
    while True:
        print("\nMenu:")
        print("1. Process related system calls")
        print("2. File related system calls")
        print("3. Communication system calls")
        print("4. Information related system calls")
        print("5. Exit")
        choice = int(input("Enter your choice: "))

        if choice == 1:
            process_system_calls()
        elif choice == 2:
            file_system_calls()
        elif choice == 3:
            communication_system_calls()
        elif choice == 4:
            information_system_calls()
        elif choice == 5:
            print("Exiting...")
            sys.exit(0)
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()


