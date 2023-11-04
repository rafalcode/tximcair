# Th	is Makefile is for pangocairo code.
# Though cairo is quite an indepentent project, pango is very much linked to Gnome. In fact it actually belongs to the gobject hierarchy,
# so gobject is very necessary to it.
CC=gcc
CFLAGS=-g -Wall
DBGCFLAGS=-g -Wall -DDBG
SPECLIBS=-lcairo -lm
#pango extremely difficult to compile. header files all in the wrong places.
# got this from "pkg-config --cflags --libs pangocairo"
# UBINCS=-I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz 
# UBINCS=-I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz 
UBINCS=-I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/harfbuzz 
# why the above?
# /usr/include/glib-2.0 for glib-object.h
# /usr/lib/x86_64-linux-gnu/glib-2.0/include for glibconfig.h
# /usr/include/harfbuzz  for hb.h

UBLIBS=-lpangocairo-1.0 -lglib-2.0 -lpango-1.0 -lgobject-2.0 -lcairo
SPECINC=-I/home/nutria/mylocal/include
EXECUTABLES=patxim0 patxim2 seeauf pa pat

# still trying to center text
patxim0: patxim0.c
	# ${CC} ${CFLAGS} ${ARCHPANGINCS} -o $@ $^ ${ARCHPANGLIBS}
	# those above libraries may have worked with Arch ... but not ub/deb
	${CC} ${CFLAGS} ${UBINCS} -o $@ $^ ${UBLIBS}

patxim2: patxim2.c
	${CC} ${CFLAGS} ${UBINCS} -o $@ $^ ${UBLIBS}

pa: pa.c
	${CC} ${CFLAGS} ${UBINCS} -o $@ $^ ${UBLIBS}
pat: pat.c
	${CC} ${CFLAGS} ${UBINCS} -o $@ $^ ${UBLIBS}

seeauf: seeauf.c
	${CC} ${CFLAGS} -o $@ $^

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
