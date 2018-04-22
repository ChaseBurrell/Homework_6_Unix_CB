# Name: Chase Burrell
# NetID: cab160330
# Email: cab160330@utdallas.edu

#
# Implicit rules
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

PROJECTNAME = Homework_6

#
# Source files
SRCS = cdkexample.cc

#
# name the executable
EXEC = Hw_6


OBJS = $(SRCS:cc=o)

all: $(EXEC)

clean:
	rm -f $(OBJS) *.d *~ \#* $(EXEC)


#  This is a rule to link the files.  Pretty standard
$(EXEC): $(OBJS)
	$(CXX)  -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)


# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!



