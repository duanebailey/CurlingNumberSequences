TARGETS=project quick rotworker props curlseq ccurlseq choose gen span spandist cgen drop rotten rotworker2 rotworker3 rotworker4 tailer pop start tile inflate flaws diffs deflate prefix forced
all:	$(TARGETS)

forced:	forced.c
	gcc -Wall -g -o forced forced.c utils.c

prefix:	prefix.c
	gcc -g -o prefix prefix.c utils.c

diffs:	diffs.c
	gcc -o diffs diffs.c

flaws:	flaws.c utils.c
	gcc -g -o flaws flaws.c utils.c

project:	project.c utils.c
	gcc -g -o project project.c utils.c -lm

inflate:	inflate.c utils.c
	gcc -g -o inflate inflate.c utils.c

deflate:	deflate.c utils.c
	gcc -g -o deflate deflate.c utils.c

pop:	pop.c utils.c
	gcc -g -o pop pop.c utils.c

start:	start.c utils.c
	gcc -g -o start start.c utils.c

tile:	tile.c utils.c
	gcc -g -o tile tile.c utils.c

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
	gcc -Wall -g -o rotworker3 rotworker3.c utils.o

rotworker4:	rotworker4.c utils.c utils.h
	gcc -Wall -O3 -o rotworker4 rotworker4.c utils.c

utils.o:	utils.c utils.h
	gcc -O2 -c utils.c

props:	props.c utils.o
	gcc -o props props.c utils.o

curlseq:	curlseq.c utils.o
	gcc -o curlseq curlseq.c utils.o

ccurlseq:	ccurlseq.c utils.o
	gcc -g -o ccurlseq ccurlseq.c utils.o

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
	@rm -rf *.dSYM
	@echo Real clean.