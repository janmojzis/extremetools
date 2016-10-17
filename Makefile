CC?=gcc
CFLAGS+=-O2 -Wall

all:  extremeenvuidgid extremesetuidgid

die.o: die.c writeall.h die.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c die.c

dropuidgid.o: dropuidgid.c e.h dropuidgid.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c dropuidgid.c

e.o: e.c e.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c e.c

extremeenvuidgid.o: extremeenvuidgid.c numtostr.h strtonum.h writeall.h \
 e.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c extremeenvuidgid.c

extremesetuidgid.o: extremesetuidgid.c numtostr.h strtonum.h dropuidgid.h \
 e.h die.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c extremesetuidgid.c

numtostr.o: numtostr.c numtostr.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c numtostr.c

strtonum.o: strtonum.c e.h strtonum.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c strtonum.c

writeall.o: writeall.c e.h writeall.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c writeall.c

extremeenvuidgid: extremeenvuidgid.o  die.o dropuidgid.o e.o numtostr.o strtonum.o writeall.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o extremeenvuidgid extremeenvuidgid.o  die.o dropuidgid.o e.o numtostr.o strtonum.o writeall.o

extremesetuidgid: extremesetuidgid.o  die.o dropuidgid.o e.o numtostr.o strtonum.o writeall.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o extremesetuidgid extremesetuidgid.o  die.o dropuidgid.o e.o numtostr.o strtonum.o writeall.o

clean:
	rm -f *.o  extremeenvuidgid extremesetuidgid

