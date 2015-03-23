TARGETS=quick rotworker props curlseq ccurlseq choose gen span spandist cgen drop rotten
all:	$(TARGETS)

quick:	quick.c utils.h utils.c
	gcc -g -Wall -o quick quick.c utils.c

rotworker:	rotworker.c utils.c utils.h
	gcc -Wall -O2 -o rotworker rotworker.c utils.c

rotworker2:	rotworker2.c utils.c utils.h
	gcc -Wall -O2 -o rotworker2 rotworker2.c utils.c

utils.o:	utils.c utils.h
	gcc -c utils.c

props:	props.c utils.o
	gcc -o props props.c utils.o

curlseq:	curlseq.c utils.o
	gcc -o curlseq curlseq.c utils.o

ccurlseq:	ccurlseq.c utils.o
	gcc -o ccurlseq ccurlseq.c utils.o

choose:	choose.c
	gcc -o choose choose.c

drop:	drop.c utils.o
	gcc -o drop drop.c utils.o

rotten:	rotten.c utils.o
	gcc -o rotten rotten.c utils.o

gen:	gen.c utils.o
	gcc -o gen gen.c utils.o

span:	span.c utils.o
	gcc -o span span.c utils.o

spandist:	spandist.c utils.o
	gcc -o spandist spandist.c utils.o

cgen:	cgen.c utils.o
	gcc -o cgen cgen.c utils.o

clean:
	@rm -f *.o *~ *.aux
	@echo Clean.

realclean:	clean
	@rm -f $(TARGETS)
	@echo Real clean.