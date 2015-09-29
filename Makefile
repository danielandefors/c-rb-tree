
CC       = gcc
CFLAGS   = -std=c99 -Wall -I.
LINKER   = gcc -o
LFLAGS   = -Wall -I. -lm
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
TARGET   = rb_tree

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

.SUFFIXES:
.SUFFIXES: .c .o

$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean :
	@rm -rf $(OBJDIR) $(BINDIR)
