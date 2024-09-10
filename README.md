
# System Programming Assignments

This repository contains 13 assignments that explore various system programming concepts. Each assignment demonstrates different techniques and functionalities related to file manipulation, process management, and system calls in a Unix-like environment.

## 1. Hole and File Copying with mmap
- **Objective**: Create a file with a gap (hole) in the middle using `lseek`.
- **Details**: Two programs are provided to copy this file:
  - `mmap_cp`: Copies the entire file, including the hole.
  - `mmap_cp2`: Copies only the data, excluding the hole.

## 2. Flock vs Lockf
- **Objective**: Compare the functionality and performance differences between `flock` and `lockf` for file locking mechanisms.

## 3. Buffered I/O Modes
- **Objective**: Understand the differences between line-buffered, unbuffered, and fully-buffered I/O operations.
- **Details**: Explore how buffering affects input and output performance.

## 4. Reading Files with Setuid
- **Objective**: Use `setuid` to read file types in a target directory.
- **Details**: Demonstrate the security implications of setuid programs.

## 5. Busybox-like Softlink
- **Objective**: Use softlinks to implement a `busybox`-like program.
- **Details**: Create a single program that can perform multiple system operations (`cp`, `ls`, `cat`, `chown`) based on the name of the softlink used to invoke it.

## 6. File Monitoring
- **Objective**: Monitor a file for changes and display its last modification time and content.
- **Details**: Implement a watcher to display real-time updates when the file is modified.

## 7. Nice Value and Performance
- **Objective**: Measure the effect of different `nice` values on program execution efficiency.
- **Details**: Analyze how adjusting process priorities affects CPU scheduling.

## 8. Login Program
- **Objective**: Design a simple login program.
- **Details**: Check if a user exists and verify the correctness of their password.

## 9. Zombie Processes
- **Objective**: Understand zombie processes and how to avoid them.
- **Details**: Explore how to handle process termination to prevent zombies from lingering in the system.

## 10. Signal Handling for Ctrl+C
- **Objective**: Capture and handle the `Ctrl+C` signal (SIGINT).
- **Details**: Implement custom signal handling to gracefully terminate or pause the program.

## 11. Stdin, Stdout, Stderr
- **Objective**: Explore the behavior and redirection of standard input, output, and error streams.
- **Details**: Understand how each stream operates and affects program behavior.

## 12. Pipe and File Counting
- **Objective**: Execute a command pipeline to count the number of characters in a directory's file listing.
- **Details**: Implement a pipe that executes `ls -R /file | wc -l` to count the files under a directory.

## 13. Nice and Process Priority Impact
- **Objective**: Measure the impact of `nice` value changes on process performance and scheduling.
- **Details**: Experiment with different priority settings using `nice` to see how they affect execution times.
