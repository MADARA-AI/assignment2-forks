#!/usr/bin/env bash
# run_and_save.sh - build and run examples, save outputs to screenshots/
set -euo pipefail

mkdir -p screenshots
echo "Building..."
make

echo "Running fork_example..."
./bin/fork_example > screenshots/fork_example.txt 2>&1 || true
echo "Running fork_wait_example..."
./bin/fork_wait_example > screenshots/fork_wait_example.txt 2>&1 || true
echo "Running fork_exec_example..."
./bin/fork_exec_example > screenshots/fork_exec_example.txt 2>&1 || true
echo "Running pipe_example..."
./bin/pipe_example > screenshots/pipe_example.txt 2>&1 || true
echo "Running orphan_example..."
./bin/orphan_example > screenshots/orphan_example.txt 2>&1 || true

# Run zombie_example in background and capture ps for the child
echo "Running zombie_example (background)..."
./bin/zombie_example > screenshots/zombie_program.txt 2>&1 & ZPID=$!
# Give it a moment to start and print PIDs
sleep 1
CHILD=$(awk -F'=' '/Child pid/ {gsub(/ /,"",$2); print $2; exit}' screenshots/zombie_program.txt || true)
if [[ -n "$CHILD" ]]; then
  echo "Captured child PID: $CHILD"
  ps -o pid,ppid,state,cmd -p "$CHILD" > screenshots/zombie_ps.txt 2>&1 || true
  echo "Saved ps output to screenshots/zombie_ps.txt"
else
  echo "Could not find child PID in screenshots/zombie_program.txt. You may need to run zombie_example manually and capture 'ps' while the parent sleeps."
fi

echo "All outputs saved under screenshots/"