# 🚀 Basik-Forks: POSIX Process Management Examples

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C Standard](https://img.shields.io/badge/C-C11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20WSL-lightgrey.svg)](https://www.kernel.org/)

A comprehensive collection of **C programming examples** demonstrating fundamental POSIX process management concepts including process creation (`fork`), process synchronization (`waitpid`), process replacement (`exec`), inter-process communication (`pipes`), and process lifecycle states (zombies and orphans).

## 🎯 Learning Objectives

This repository serves as a hands-on tutorial for understanding:

- **Process Creation**: How operating systems create new processes using `fork()`
- **Process Hierarchy**: Parent-child relationships and process IDs (PIDs)
- **Process Synchronization**: Waiting for child processes and handling exit status
- **Process Replacement**: Using `exec` family functions to run new programs
- **Inter-Process Communication (IPC)**: Using pipes to transfer data between processes
- **Process States**: Understanding zombie and orphan processes
- **System Programming**: Working with POSIX APIs and system calls

## 📋 Table of Contents

- [Features](#-features)
- [Prerequisites](#-prerequisites)
- [Quick Start](#-quick-start)
- [Detailed Program Descriptions](#-detailed-program-descriptions)
- [Build System](#-build-system)
- [Running Examples](#-running-examples)
- [Expected Output](#-expected-output)
- [Capturing Outputs for Submission](#-capturing-outputs-for-submission)
- [Troubleshooting](#-troubleshooting)
- [FAQ](#-faq)
- [Contributing](#-contributing)
- [License](#-license)
- [Author](#-author)

## ✨ Features

- **6 Complete Examples**: Each demonstrating a specific POSIX concept
- **Modern Build System**: Makefile with clean separation of binaries
- **Comprehensive Documentation**: Inline code comments and detailed README
- **Cross-Platform**: Works on Linux, macOS, and WSL
- **Educational Focus**: Perfect for systems programming courses
- **MIT Licensed**: Free to use and modify

## 📁 Repository Structure

```
Basik-Forks/
├── fork_example.c          # Basic fork() demonstration
├── fork_wait_example.c     # fork() + waitpid() with exit status
├── fork_exec_example.c     # fork() + exec() process replacement
├── pipe_example.c          # Parent-child IPC using pipes
├── zombie_example.c        # Zombie process demonstration
├── orphan_example.c        # Orphan process and reparenting
├── Makefile                # Modern build system
├── make_targets.mk         # Additional Makefile targets
├── ANSWERS.txt             # Educational answers and explanations
├── LICENSE                 # MIT License
├── README.md               # This file
├── captions/               # Sample program outputs
└── bin/                    # Compiled binaries (generated)
```

## 🔧 Prerequisites

### Operating System
- **Linux**: Any modern distribution (Ubuntu, Debian, Fedora, Arch, etc.)
- **macOS**: Version 10.13 or later
- **Windows**: WSL (Windows Subsystem for Linux) version 1 or 2

### Required Software

#### On Linux (Debian/Ubuntu):
```bash
sudo apt update
sudo apt install build-essential
```

#### On Linux (Fedora/RHEL):
```bash
sudo dnf groupinstall "Development Tools"
```

#### On macOS:
```bash
# Install Xcode Command Line Tools
xcode-select --install
```

#### On Windows (WSL):
```bash
# First install WSL from PowerShell (as Administrator):
# wsl --install

# Then inside WSL:
sudo apt update
sudo apt install build-essential
```

### Verify Installation
```bash
gcc --version    # Should show GCC 7.0 or later
make --version   # Should show GNU Make 4.0 or later
```

## 🚀 Quick Start

Get up and running in less than a minute:

```bash
# Clone the repository
git clone https://github.com/MADARA-AI/Basik-Forks.git
cd Basik-Forks

# Build all examples
make

# Run a specific example
./bin/fork_example

# Or run all examples sequentially
make run-all
```

## 📚 Detailed Program Descriptions

### 1. fork_example.c - Basic Process Creation

**Concepts Demonstrated**: `fork()`, `getpid()`, `getppid()`

This program shows the fundamental behavior of `fork()` system call:
- Creates a child process that is an exact copy of the parent
- Both processes continue execution from the point after `fork()`
- Child receives `0` from `fork()`, parent receives child's PID

**Key Code Snippet**:
```c
pid_t pid = fork();
if (pid == 0) {
    printf("Child: pid=%d, parent=%d\n", getpid(), getppid());
} else {
    printf("Parent: pid=%d, child=%d\n", getpid(), pid);
}
```

**Process Flow**:
```
Parent Process (PID: 1234)
         |
         | fork()
         |
    +---------+
    |         |
Parent     Child
(PID:1234) (PID:1235)
```

---

### 2. fork_wait_example.c - Process Synchronization

**Concepts Demonstrated**: `fork()`, `waitpid()`, `WIFEXITED()`, `WEXITSTATUS()`

Demonstrates how a parent process waits for its child to complete:
- Parent blocks until child terminates
- Exit status is retrieved and examined
- Prevents premature parent termination

**Key Code Snippet**:
```c
int status;
waitpid(pid, &status, 0);
if (WIFEXITED(status)) {
    printf("Child exited with status %d\n", WEXITSTATUS(status));
}
```

**Why This Matters**: Without proper waiting, you risk creating zombie processes or orphans.

---

### 3. fork_exec_example.c - Process Replacement

**Concepts Demonstrated**: `fork()`, `execlp()`, process image replacement

Shows how to launch a new program from within your program:
- Child process replaces its memory with a new program (`ls -l`)
- `exec` family functions do not return on success
- Commonly used pattern for running external commands

**Key Code Snippet**:
```c
if (pid == 0) {
    execlp("ls", "ls", "-l", (char *)NULL);
    perror("execlp");  // Only reached if exec fails
    _exit(1);
}
```

**Process Image Replacement**:
```
Before exec():              After exec():
┌─────────────┐            ┌─────────────┐
│ fork_exec   │            │     ls      │
│   program   │  ────>     │   program   │
│  (child)    │            │             │
└─────────────┘            └─────────────┘
```

---

### 4. pipe_example.c - Inter-Process Communication

**Concepts Demonstrated**: `pipe()`, IPC, file descriptors, `read()`, `write()`

Demonstrates parent-child communication using a unidirectional pipe:
- Pipe creates two file descriptors: read end and write end
- Parent writes data, child reads it
- Proper file descriptor management is crucial

**Key Code Snippet**:
```c
int fd[2];
pipe(fd);  // fd[0] = read end, fd[1] = write end

if (pid == 0) {
    close(fd[1]);  // Child closes write end
    read(fd[0], buffer, sizeof(buffer));
} else {
    close(fd[0]);  // Parent closes read end
    write(fd[1], msg, strlen(msg));
}
```

**Pipe Communication**:
```
Parent Process              Child Process
     |                            |
     |  write(fd[1], data) ────>  | read(fd[0], buffer)
     |                            |
  [PIPE: fd[1] ==========> fd[0]]
```

---

### 5. zombie_example.c - Zombie Processes

**Concepts Demonstrated**: Zombie state, process reaping

A zombie is a process that has terminated but whose exit status hasn't been collected:
- Child exits immediately
- Parent sleeps without calling `wait()`
- Child enters zombie state (defunct)

**Key Code Snippet**:
```c
if (pid == 0) {
    _exit(0);  // Child exits immediately
} else {
    printf("Parent sleeping, child pid=%d\n", pid);
    sleep(10);  // Child becomes zombie during this time
}
```

**How to Observe**:
```bash
# Terminal 1:
./bin/zombie_example
# Note the child PID

# Terminal 2 (quickly):
ps -o pid,ppid,state,cmd -p <child-pid>
# Look for 'Z' state
```

**Why Zombies Matter**: Too many zombies consume process table entries and can eventually prevent new processes from being created.

---

### 6. orphan_example.c - Orphan Processes and Reparenting

**Concepts Demonstrated**: Process reparenting, init/systemd adoption

An orphan is a process whose parent has terminated:
- Parent exits immediately
- Child continues running
- OS reparents child to init (PID 1) or systemd

**Key Code Snippet**:
```c
if (pid == 0) {
    sleep(2);  // Give parent time to exit
    printf("My parent is %d (should be 1)\n", getppid());
} else {
    printf("Parent exiting immediately\n");
    return 0;  // Parent exits
}
```

**Reparenting Visualization**:
```
Initial State:           After Parent Exits:
     init (PID 1)              init (PID 1)
          |                         |
       Parent                    Child
          |                   (reparented)
       Child
```

## 🔨 Build System

The repository includes a modern Makefile that:
- Compiles all programs into a separate `bin/` directory
- Provides individual run targets for each program
- Supports incremental builds
- Includes a clean target

### Build All Programs

```bash
make
```

This compiles all 6 examples and places executables in the `bin/` directory.

### Build a Specific Program

```bash
make bin/fork_example
make bin/pipe_example
# etc.
```

### Manual Compilation

If you prefer to compile manually or don't have `make`:

```bash
# Create bin directory
mkdir -p bin

# Compile individual programs
gcc -Wall -Wextra -std=c11 -g -o bin/fork_example fork_example.c
gcc -Wall -Wextra -std=c11 -g -o bin/fork_wait_example fork_wait_example.c
gcc -Wall -Wextra -std=c11 -g -o bin/fork_exec_example fork_exec_example.c
gcc -Wall -Wextra -std=c11 -g -o bin/pipe_example pipe_example.c
gcc -Wall -Wextra -std=c11 -g -o bin/zombie_example zombie_example.c
gcc -Wall -Wextra -std=c11 -g -o bin/orphan_example orphan_example.c
```

### Compiler Flags Explained

- `-Wall`: Enable all common warnings
- `-Wextra`: Enable extra warnings
- `-std=c11`: Use C11 standard
- `-g`: Include debugging information (useful with gdb)

### Clean Build Artifacts

```bash
make clean
```

This removes the `bin/` directory and all compiled objects.

## ▶️ Running Examples

All programs are built into the `bin/` directory by default.

### Run Individual Programs

#### 1. Basic Fork Example
```bash
./bin/fork_example
```
**What to expect**: Parent and child PIDs displayed, showing both processes executing.

#### 2. Fork with Wait
```bash
./bin/fork_wait_example
```
**What to expect**: Parent waits for child, displays exit status 42.

#### 3. Fork with Exec
```bash
./bin/fork_exec_example
```
**What to expect**: Directory listing from child process running `ls -l`.

#### 4. Pipe Communication
```bash
./bin/pipe_example
```
**What to expect**: Message sent from parent to child through pipe.

#### 5. Zombie Process
```bash
# Terminal 1:
./bin/zombie_example

# Terminal 2 (quickly, before 10 seconds elapse):
ps -o pid,ppid,state,cmd -p <child-pid>
```
**What to expect**: Child process in 'Z' (zombie) state visible in `ps` output.

#### 6. Orphan Process
```bash
./bin/orphan_example
```
**What to expect**: Child reports parent PID as 1 (init) or systemd PID after reparenting.

### Run All Examples Sequentially

```bash
make run-all
```

This builds (if necessary) and runs all examples one after another.

### Run with Makefile Targets

```bash
make run-fork_example
make run-pipe_example
# etc.
```

## 📊 Expected Output

### fork_example
```
Before fork(): pid=12345
Parent: pid=12345, child=12346
Process 12345 exiting
Child: pid=12346, parent=12345
Process 12346 exiting
```

### fork_wait_example
```
Parent (12345): waiting for child 12346
Child (12346): doing some work...
Child (12346): exiting with status 42
Parent: child exited with status 42
```

### fork_exec_example
```
Child (12346): exec ls -l
total 128
-rw-r--r-- 1 user user  1234 Jan 15 10:30 fork_example.c
-rw-r--r-- 1 user user  1456 Jan 15 10:30 fork_wait_example.c
[... directory listing ...]
Parent: child finished
```

### pipe_example
```
Child (12346) read: Hello from parent via pipe
```

### zombie_example
```
Child (12346) exiting immediately
Parent (12345): sleeping for 10 seconds. Child pid=12346
[... 10 seconds pass ...]
Parent: now exiting (child should be reaped automatically by exit)
```

**In another terminal during the 10-second sleep**:
```
$ ps -o pid,ppid,state,cmd -p 12346
  PID  PPID S CMD
12346 12345 Z [zombie_example] <defunct>
```

### orphan_example
```
Parent (12345) exiting immediately, child pid=12346
Child (12346): my parent is 1 (should be 1 or systemd)
```

## 📸 Capturing Outputs for Submission

If you're using this repository for coursework or need to document your runs:

### Create Output Directory
```bash
mkdir -p screenshots
```

### Capture Standard Output
```bash
./bin/fork_example > screenshots/fork_example.txt 2>&1
./bin/fork_wait_example > screenshots/fork_wait_example.txt 2>&1
./bin/fork_exec_example > screenshots/fork_exec_example.txt 2>&1
./bin/pipe_example > screenshots/pipe_example.txt 2>&1
./bin/orphan_example > screenshots/orphan_example.txt 2>&1
```

### Capture Zombie Example (Special Case)
```bash
# Start the program in background
./bin/zombie_example > screenshots/zombie_program.txt 2>&1 &

# Wait a moment for child to exit
sleep 1

# Capture the zombie state (replace <child-pid> with actual PID from output)
ps -o pid,ppid,state,cmd -p <child-pid> > screenshots/zombie_ps.txt
```

### Automated Capture Script

For convenience, you can use the provided script:

```bash
./run_and_save.sh
```

This will automatically run all examples and save outputs to the `captions/` directory.

### Commit Your Outputs
```bash
git add screenshots/*
git commit -m "Add program run outputs"
git push origin main
```

## 🔍 Troubleshooting

### Build Issues

#### Problem: `make: command not found`
**Solution**: Install build tools:
```bash
# Ubuntu/Debian
sudo apt install build-essential

# Fedora/RHEL
sudo dnf groupinstall "Development Tools"

# macOS
xcode-select --install
```

#### Problem: `gcc: command not found`
**Solution**: Install GCC compiler:
```bash
# Ubuntu/Debian
sudo apt install gcc

# macOS (install Xcode Command Line Tools)
xcode-select --install
```

#### Problem: Compilation errors about C11 features
**Solution**: Ensure you're using GCC 7.0 or later:
```bash
gcc --version
# If older, update your compiler
```

### Runtime Issues

#### Problem: Permission denied when running programs
**Solution**: Make sure executables have execute permissions:
```bash
chmod +x bin/*
```

#### Problem: `zombie_example` - Can't see zombie state
**Solution**: The zombie only exists for 10 seconds. You need to be quick:
1. Run `./bin/zombie_example` in terminal 1
2. Note the child PID immediately
3. Quickly run `ps -o pid,ppid,state,cmd -p <child-pid>` in terminal 2 within 10 seconds

**Alternative**: Modify the sleep time in `zombie_example.c` to give yourself more time:
```c
sleep(60);  // Change from 10 to 60 seconds
```

#### Problem: `orphan_example` shows wrong parent PID
**Solution**: The reparenting happens quickly. The child sleeps for 2 seconds to allow parent to exit. If you see the original parent PID, the timing might need adjustment.

#### Problem: `fork_exec_example` shows "execlp: No such file or directory"
**Solution**: The `ls` command is not in your PATH. On some systems, try:
```bash
# Check where ls is located
which ls

# If it's not found, install coreutils
sudo apt install coreutils  # Ubuntu/Debian
```

### Git Issues

#### Problem: Can't push to GitHub - authentication failed
**Solution**: Set up authentication:

**Option 1 - SSH Keys** (Recommended):
```bash
# Generate SSH key
ssh-keygen -t ed25519 -C "your_email@example.com"

# Copy public key
cat ~/.ssh/id_ed25519.pub

# Add to GitHub: Settings > SSH and GPG keys > New SSH key
```

**Option 2 - Personal Access Token**:
1. Go to GitHub Settings > Developer settings > Personal access tokens
2. Generate new token with `repo` scope
3. Use token as password when prompted

#### Problem: `git push` says "everything up-to-date" but changes aren't pushed
**Solution**: Make sure you've committed your changes first:
```bash
git add .
git commit -m "Your commit message"
git push origin main
```

### Platform-Specific Issues

#### macOS: "fork_example.c:11:10: fatal error: 'sys/types.h' file not found"
**Solution**: Install Xcode Command Line Tools:
```bash
xcode-select --install
```

#### WSL: Programs run but output seems delayed
**Solution**: This is normal for WSL1. Consider upgrading to WSL2:
```powershell
# In PowerShell as Administrator
wsl --set-default-version 2
```

#### Linux: "Resource temporarily unavailable" error
**Solution**: You might have hit the process limit. Check and increase:
```bash
ulimit -u      # Check current limit
ulimit -u 4096 # Increase limit
```

## ❓ FAQ (Frequently Asked Questions)

### General Questions

**Q: What is the difference between `fork()` and `exec()`?**

A: `fork()` creates a duplicate of the current process, while `exec()` replaces the current process with a new program. They're often used together: fork to create a child, then exec in the child to run a different program.

**Q: Why use `_exit()` instead of `exit()` in children?**

A: `_exit()` terminates immediately without flushing I/O buffers or calling `atexit()` handlers, which prevents duplicate cleanup when both parent and child would otherwise run the same cleanup code.

**Q: What happens if a parent doesn't wait for its children?**

A: Children become zombies until the parent waits for them or exits. When the parent exits, zombies are adopted by init/systemd which reaps them.

**Q: Can a child process have children of its own?**

A: Yes! Any process can fork. This creates a process tree. Use `pstree` command to visualize the process hierarchy on your system.

### Technical Questions

**Q: What's the return value of `fork()`?**

A:
- `-1`: Fork failed (error)
- `0`: You're in the child process
- `> 0`: You're in the parent, value is child's PID

**Q: Are file descriptors inherited across `fork()`?**

A: Yes! Open file descriptors are inherited by the child. Both parent and child share the same file offset. This is why we close unused pipe ends.

**Q: Are file descriptors inherited across `exec()`?**

A: By default yes, unless marked with `FD_CLOEXEC` flag. This is how shell redirection works when running commands.

**Q: How much memory does `fork()` consume?**

A: Modern systems use copy-on-write (COW), so initially very little extra memory is used. Pages are only copied when modified by parent or child.

**Q: What's the maximum number of processes I can create?**

A: Depends on system limits. Check with `ulimit -u`. Typical limits are 1024-4096 per user on Linux.

### Debugging Questions

**Q: How can I debug these programs?**

A: Use GDB (GNU Debugger):
```bash
gdb bin/fork_example
(gdb) break main
(gdb) run
(gdb) next  # Step through
```

For debugging forked processes:
```bash
gdb bin/fork_example
(gdb) set follow-fork-mode child  # Or 'parent'
(gdb) run
```

**Q: How can I trace system calls?**

A: Use `strace` on Linux or `dtruss` on macOS:
```bash
strace ./bin/fork_example
# You'll see all fork, wait, exit system calls
```

**Q: How do I check for memory leaks?**

A: Use Valgrind:
```bash
valgrind --leak-check=full ./bin/fork_example
```

### Educational Questions

**Q: Which example should I study first?**

A: Recommended order:
1. `fork_example.c` - Understand basic forking
2. `fork_wait_example.c` - Learn synchronization
3. `fork_exec_example.c` - Process replacement
4. `pipe_example.c` - IPC basics
5. `zombie_example.c` - Process states
6. `orphan_example.c` - Process lifecycle

**Q: What real-world programs use these concepts?**

A:
- **Shells** (bash, zsh): Use fork+exec to run commands
- **Web servers** (Apache, nginx): Fork to handle multiple clients
- **Init systems** (systemd, init): Adopt orphaned processes
- **Cron/schedulers**: Fork to run jobs without blocking
- **Compilers**: Fork to run preprocessor, compiler, linker stages

**Q: Are there alternatives to `fork()`?**

A: Yes:
- **`vfork()`**: Legacy, faster but dangerous (child shares parent's memory)
- **`clone()`**: Linux-specific, more control over what's shared
- **`posix_spawn()`**: Higher-level, combines fork+exec
- **Threads**: Use `pthread_create()` for shared-memory concurrency

## 📖 Additional Resources

### Books
- **Advanced Programming in the UNIX Environment** by W. Richard Stevens
- **The Linux Programming Interface** by Michael Kerrisk
- **Operating System Concepts** by Silberschatz, Galvin, Gagne

### Online Resources
- [Linux man pages](https://man7.org/linux/man-pages/)
- [POSIX.1-2017 Standard](https://pubs.opengroup.org/onlinepubs/9699919799/)
- [fork() man page](https://man7.org/linux/man-pages/man2/fork.2.html)
- [exec() man page](https://man7.org/linux/man-pages/man3/exec.3.html)
- [pipe() man page](https://man7.org/linux/man-pages/man2/pipe.2.html)

### Related Topics to Explore
- **Signals**: Process communication via signals (SIGTERM, SIGKILL, etc.)
- **Process Groups and Sessions**: Job control in shells
- **Threads**: POSIX threads (pthreads) for shared-memory concurrency
- **IPC Mechanisms**: Shared memory, message queues, semaphores, sockets
- **Process Scheduling**: Priority, nice values, real-time scheduling

## 🎓 Learning Exercises

Want to deepen your understanding? Try these exercises:

### Beginner Level
1. Modify `fork_example.c` to create 3 child processes instead of 1
2. Change `fork_wait_example.c` to wait for multiple children
3. Modify `fork_exec_example.c` to run `ps -ef` instead of `ls -l`
4. Make `pipe_example.c` bidirectional (parent and child both read and write)

### Intermediate Level
5. Create a program that forks N children and has parent wait for all
6. Implement a simple shell that can run commands (fork+exec pattern)
7. Build a program that creates a process tree 3 levels deep
8. Write a program using two pipes for bidirectional communication

### Advanced Level
9. Implement a simple producer-consumer using pipes
10. Create a mini web server that forks to handle each connection
11. Build a process pool that reuses children for multiple tasks
12. Implement signal handling to gracefully terminate child processes

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

### Reporting Issues
If you find a bug or have a suggestion:
1. Check if the issue already exists in [GitHub Issues](https://github.com/MADARA-AI/Basik-Forks/issues)
2. If not, create a new issue with:
   - Clear description of the problem
   - Steps to reproduce
   - Expected vs actual behavior
   - Your environment (OS, GCC version)

### Submitting Changes

1. **Fork the repository**
   ```bash
   # Click 'Fork' on GitHub, then:
   git clone https://github.com/YOUR_USERNAME/Basik-Forks.git
   ```

2. **Create a feature branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

3. **Make your changes**
   - Follow existing code style (K&R style preferred)
   - Add comments for complex logic
   - Test your changes on multiple platforms if possible

4. **Commit your changes**
   ```bash
   git add .
   git commit -m "Add: Brief description of your changes"
   ```

5. **Push and create Pull Request**
   ```bash
   git push origin feature/your-feature-name
   # Then create PR on GitHub
   ```

### Code Style Guidelines
- Use K&R indentation style
- Limit lines to 80 characters where practical
- Add comments for non-obvious code
- Include error checking for all system calls
- Use meaningful variable names

### Ideas for Contributions
- Add more examples (shared memory, message queues, signals)
- Improve error messages
- Add performance benchmarks
- Create interactive tutorials
- Translate comments/docs to other languages
- Add Windows (Cygwin/MinGW) support
- Create video tutorials

## 📝 Notes and Recommendations

### For Students
- **Read the code first**: Start with `fork_example.c` and understand every line
- **Experiment**: Modify the code and observe what happens
- **Use print statements**: Add `printf` to trace execution flow
- **Draw diagrams**: Visualize process trees and pipe connections
- **Read man pages**: Run `man fork`, `man exec`, etc. for detailed documentation
- **ANSWERS.txt**: Contains additional explanations for coursework

### For Instructors
- These examples are designed for introductory systems programming courses
- Each example is self-contained and can be taught independently
- The progression is designed from simple to complex
- Consider having students modify examples rather than write from scratch
- The Makefile can be studied to teach build systems
- The repository structure follows best practices for C projects

### For Developers
- These patterns are the foundation of UNIX/Linux systems programming
- Real applications need additional error handling and robustness
- Consider using higher-level abstractions (pthreads, event loops) for production
- Study how popular software (shells, servers) uses these primitives
- Performance matters: fork() is expensive, consider alternatives for high-frequency use

## 📄 License

This project is released under the **MIT License** — see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2024-2025 MADARA-AI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
```

### What this means:
- ✅ Free to use for personal and commercial purposes
- ✅ Free to modify and distribute
- ✅ No warranty or liability
- ✅ Must include original license and copyright notice

## 👤 Author

**MADARA-AI**

- GitHub: [@MADARA-AI](https://github.com/MADARA-AI)
- Repository: [Basik-Forks](https://github.com/MADARA-AI/Basik-Forks)

## 🌟 Acknowledgments

- Inspired by classic UNIX systems programming examples
- Built for educational purposes to teach process management concepts
- Thanks to all contributors and users of this repository

## 📮 Support and Contact

- **Issues**: Report bugs or request features via [GitHub Issues](https://github.com/MADARA-AI/Basik-Forks/issues)
- **Discussions**: Ask questions in [GitHub Discussions](https://github.com/MADARA-AI/Basik-Forks/discussions)
- **Pull Requests**: Contributions welcome via pull requests

---

<div align="center">

### ⭐ If you find this repository helpful, please consider giving it a star!

**Happy Learning! 🚀**

*Made with ❤️ for systems programming education*

</div>
