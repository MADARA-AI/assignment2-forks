# Assignment 2 — Basic forks and C-style development

This repository contains the code examples from Lab-5 (forks and simple process examples), explanations, a Makefile to build and run the examples, and an open-source license.

## Contents

- fork_example.c — simple fork() demonstration
- fork_wait_example.c — fork() + waitpid() example
- fork_exec_example.c — fork() + exec (child runs `ls -l`)
- pipe_example.c — parent-child communication using a pipe
- zombie_example.c — demonstrates a zombie child
- orphan_example.c — demonstrates an orphan child becoming reparented to init/systemd
- Makefile — build targets for each example and `run-all`
- ANSWERS.txt — textual answers and explanations (linker, loader, description of each example, how to run, and screenshot instructions)
- LICENSE — MIT License

## Build

Requires a POSIX-compatible system with `gcc`:

```sh
make
```

This will build all example programs.

To build a single target:
```sh
make fork_example
```

## Run

Individual programs:
```sh
./fork_example
./fork_wait_example
./fork_exec_example
./pipe_example
./zombie_example    # recommended to run in separate terminal to inspect `ps`
./orphan_example
```

Run them all (serially) with:
```sh
make run-all
```

Notes:
- `zombie_example` is designed to allow you to observe the zombie state; run it and quickly run `ps -o pid,ppid,state,cmd` to inspect the child's state.
- `orphan_example` shows the child reparented to `init`/`systemd` (parent PID will typically become 1 or systemd PID).

## What to submit

The assignment requires:
- `.c` source files (included)
- `Makefile` (included)
- `README.md` (this file)
- `ANSWERS.txt` (included)
- `LICENSE` (included)
- Screenshots showing compilation and running outputs (you need to capture and upload those)

## How to capture screenshots

1. Build the project:
   - `make`
   - Save a screenshot of the terminal showing `make` output.
2. Run each program and capture the terminal:
   - `./fork_example` — screenshot
   - `./fork_wait_example` — screenshot
   - `./fork_exec_example` — screenshot
   - `./pipe_example` — screenshot
   - `./zombie_example` — open a second terminal and run `ps -o pid,ppid,state,cmd | grep <child-pid>` to capture the 'Z' (zombie) state; screenshot both terminals
   - `./orphan_example` — screenshot showing the child's parent PID change
3. Add screenshots to the repository (e.g., `screenshots/`) and commit.

## License

This project uses the MIT License. See the LICENSE file.

## Author

Your Name (replace with your name)