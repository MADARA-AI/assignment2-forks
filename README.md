# Assignment 2 — Basic forks and C-style development

This repository contains small C examples used to demonstrate process creation and IPC on POSIX systems (fork, waitpid, exec, pipes, zombies, and orphaned processes). The README below includes up-to-date build and run instructions, notes on capturing outputs for submission, and troubleshooting tips.

## Contents

- fork_example.c — simple fork() demonstration
- fork_wait_example.c — fork() + waitpid() example (child exits with status 42)
- fork_exec_example.c — fork() + exec (child runs `ls -l`)
- pipe_example.c — parent-child communication using a pipe
- zombie_example.c — demonstrates a zombie child
- orphan_example.c — demonstrates an orphan child becoming reparented to init/systemd
- Makefile — builds all examples into `bin/` and provides run targets
- Makefile.txt — original Makefile (kept for backward compatibility)
- ANSWERS.txt — textual answers and explanations for submission
- LICENSE — MIT License

## Prerequisites

- POSIX-compatible OS (Linux, WSL, macOS)
- gcc and make (install via your distro package manager, e.g., `sudo apt install build-essential`)

## Build

The repository includes a modern Makefile that builds programs into the `bin/` directory.

Build all programs:

    make

Build a single program (example):

    make bin/fork_example

If you do not have `make`, compile manually with:

    gcc -Wall -Wextra -std=c11 -g -o bin/fork_example fork_example.c

## Run

Programs are built into `bin/` by default.

- fork_example

    ./bin/fork_example

  Shows parent and child PIDs and demonstrates that both processes continue executing after fork().

- fork_wait_example

    ./bin/fork_wait_example

  Parent waits for child; the child exits with status 42 so you can observe the exit status handling.

- fork_exec_example

    ./bin/fork_exec_example

  Child replaces its image with `ls -l` (you will see a directory listing printed by the child).

- pipe_example

    ./bin/pipe_example

  Parent writes to a pipe and the child reads and prints the message.

- zombie_example (observe a zombie)

  In one terminal run:

    ./bin/zombie_example

  It prints the parent and child PIDs and then the parent sleeps for 10 seconds. While the parent sleeps, in another terminal run (replace <child-pid> with the child PID printed by the program):

    ps -o pid,ppid,state,cmd -p <child-pid>

  Look for the state column showing 'Z' (zombie). After the parent exits (after sleeping), the child will be reaped.

- orphan_example (observe reparenting)

    ./bin/orphan_example

  The parent exits immediately; the child sleeps and then prints its parent PID, which is typically 1 or the `systemd` PID showing reparenting.

## Run all examples (serially)

The Makefile provides a `run-all` target which builds and runs each example in sequence:

    make run-all

## Capturing outputs for submission

Instead of screenshots you can capture program outputs to text files and commit them. Example:

    mkdir -p screenshots
    ./bin/fork_example > screenshots/fork_example.txt 2>&1
    ./bin/fork_wait_example > screenshots/fork_wait_example.txt 2>&1
    ./bin/fork_exec_example > screenshots/fork_exec_example.txt 2>&1
    ./bin/pipe_example > screenshots/pipe_example.txt 2>&1
    ./bin/orphan_example > screenshots/orphan_example.txt 2>&1

For the zombie example capture the program output and the `ps` entry while the parent is sleeping:

    ./bin/zombie_example > screenshots/zombie_program.txt 2>&1 &
    sleep 1
    ps -o pid,ppid,state,cmd -p <child-pid> > screenshots/zombie_ps.txt

Then commit the screenshots folder:

    git add screenshots/*
    git commit -m "Add run outputs for submission"
    git push origin main

## Notes and recommendations

- The original `Makefile.txt` is kept for compatibility; the new `Makefile` builds into `bin/` and provides run targets.
- `ANSWERS.txt` contains the required written answers for your submission. Ensure it is present before final submission.
- If you want a helper script to automatically run each example and save outputs to `screenshots/`, it can be added in a follow-up commit.

## Troubleshooting

- If `make` is not found: install build-essential or your platform's equivalent.
- If `gcc` is not found: install the compiler package.
- If `git` prompts for username/password when pushing: set up SSH keys (recommended) or create a Personal Access Token (PAT) and configure a credential helper. A script can be provided to generate an ed25519 key and instructions for adding it to GitHub.

## License

This project is released under the MIT License — see the LICENSE file.

## Author

MADARA-AI
