CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
BINDIR = bin

SRCS = fork_example.c fork_wait_example.c fork_exec_example.c pipe_example.c zombie_example.c orphan_example.c
PROGS = $(SRCS:.c=)
TARGETS = $(addprefix $(BINDIR)/, $(PROGS))

.PHONY: all clean run-all run-%

all: $(BINDIR) $(TARGETS)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/%: %.c
	$(CC) $(CFLAGS) -o $@ $<

run-%: all
	@echo "Running $*:" \
	@$(BINDIR)/$*

run-all: all
	@echo "Running all examples..."
	@for p in $(PROGS); do \
		echo "==> $$p"; \
		$(BINDIR)/$$p || exit $$?; \
	done

clean:
	rm -rf $(BINDIR) *.o