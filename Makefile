# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c headcannon-dwm.c util.c
OBJ = ${SRC:.c=.o}

all: options headcannon-dwm

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

headcannon-dwm: ${OBJ} centeredmaster.c gaplessgrid.c trigapless.c
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f headcannon-dwm ${OBJ} headcannon-dwm-${VERSION}.tar.gz

dist: clean
	mkdir -p headcannon-dwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		headcannon-dwm.1 drw.h util.h ${SRC} dwm.png transient.c\
        gaplessgrid.c trigapless.c centeredmaster.c hcdwm.png\
        headcannon-dwm-${VERSION}
	tar -cf headcannon-dwm-${VERSION}.tar headcannon-dwm-${VERSION}
	gzip headcannon-dwm-${VERSION}.tar
	rm -rf headcannon-dwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f headcannon-dwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/headcannon-dwm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < headcannon-dwm.1 > ${DESTDIR}${MANPREFIX}/man1/headcannon-dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/headcannon-dwm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/headcannon-dwm\
		${DESTDIR}${MANPREFIX}/man1/headcannon-dwm.1

.PHONY: all options clean dist install uninstall
