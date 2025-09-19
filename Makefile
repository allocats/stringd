NASM     = nasm
NASMFLAGS= -g -f elf64

CC       = clang
CFLAGS   = -O0 -fno-builtin -g3

BUILDDIR = build
BINDIR   = $(BUILDDIR)/bin

.PHONY: all
all:
	@echo "Usage: make <name>"
	@echo "Example: make strlen"

.PRECIOUS: $(BINDIR)/% $(BUILDDIR)/%.o
%: $(BINDIR)/%
	@echo "Finished building $@"

$(BINDIR)/%: $(BUILDDIR)/%.o tests/test_%.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: src/%.asm | $(BUILDDIR)
	$(NASM) $(NASMFLAGS) -o $@ $<

$(BUILDDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
