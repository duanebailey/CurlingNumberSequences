TARGETS=rotworker3
all:	$(TARGETS)

utils.c:	../utils.c
	cp ../utils.c .

utils.h:	../utils.h
	cp ../utils.h .

rotworker3.c:	../rotworker3.c
	cp ../rotworker3.c .

rotworker3:	rotworker3.c utils.o
	gcc -g -Wall  -o rotworker3 rotworker3.c utils.o

utils.o:	utils.c utils.h
	gcc -O2 -c utils.c

tarball:	rotworker3 realclean
	@echo Build the tarball from this directory.

clean:
	@rm -f *.o *~ *.aux
	@rm -rf *.dSYM
	@echo Clean.

realclean:	clean
	@rm -f $(TARGETS)
	@echo Real clean.