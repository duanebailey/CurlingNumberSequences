TARGETS=quick rotworker props curlseq ccurlseq choose gen span spandist cgen drop rotten rotworker2 rotworker3 tailer
all:	$(TARGETS)

tailer:	tailer.c utils.o
	gcc -g -O2 -o tailer tailer.c utils.o

quick:	quick.c utils.o
	gcc -g -Wall -o quick quick.c utils.o

rotworker:	rotworker.c utils.o
	gcc -Wall -O2 -o rotworker rotworker.c utils.o

rotworker2:	rotworker2.c utils.o
	gcc -Wall -O2 -o rotworker2 rotworker2.c utils.o

rw3:	rotworker3.c utils.o
	gcc -Wall -g -o rw3 rotworker3.c utils.o

rotworker3:	rotworker3.c utils.o
	gcc -Wall -O2 -o rotworker3 rotworker3.c utils.o

utils.o:	utils.c utils.h
	gcc -O2 -c utils.c

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