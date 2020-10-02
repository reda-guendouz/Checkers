CC=gcc
CFLAGS=-O2 -Wall `sdl-config --cflags`
LIBS=`sdl-config --libs` -lm -lSDL_ttf
DIR=IN200

all: controleur 

controleur: controleur.c vue.o modele.o graphics.o 
	$(CC) $(CFLAGS) graphics.o vue.o modele.o controleur.c -o resultat $(LIBS)
	./resultat

vue.o: vue.c vue.h
	if [ ! -f vue.o  ]; then $(CC) $(CFLAGS) -c vue.c; elif [ vue.o -ot vue.c ]; then $(CC) $(CFLAGS) -c vue.c; fi

modele.o: modele.c modele.h
	if [ ! -f modele.o  ]; then $(CC) $(CFLAGS) -c modele.c; elif [ modele.o -ot modele.c ]; then $(CC) $(CFLAGS) -c modele.c; fi

#Cible generique pour Linux
%: graphics.o %.c
	rm -f $@
	$(CC) $(CFLAGS) graphics.o $@.c -o $@ $(LIBS)

#Cible generique pour free BSD
.c .o: graphics.o
	rm -f $@
	$(CC) $(CFLAGS) graphics.o $@.c -o $@ $(LIBS)

graphics.o: graphics.c graphics.h
	rm -f police.h
	touch police.h
	if test -e /usr/include/SDL_ttf.h;           then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/include/SDL/SDL_ttf.h;       then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/local/include/SDL_ttf.h;     then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/local/include/SDL/SDL_ttf.h; then echo "#define SDL_TTF_OK" > police.h; fi
	$(CC) $(CFLAGS) -c graphics.c


sans_ttf:
	rm -f police.h
	touch police.h
	$(CC) $(CFLAGS) -c graphics.c
	$(CC) $(CFLAGS) graphics.o exemple.c -o exemple $(LIBS)
	./exemple


tar: clean
	rm -rf $(DIR)
	mkdir $(DIR)
	cp exemple.c $(DIR)
	cp graphics.c $(DIR)
	cp graphics.h $(DIR)
	cp couleur.h $(DIR)
	cp exo1.1.c $(DIR)
	cp Makefile $(DIR)
	cp *.ttf $(DIR)
	tar cvf $(DIR).tar $(DIR)
	rm -rf $(DIR)

clean:
	rm -f *core
	rm -f police.h
	rm -f resultat
	rm -f *.tar
	rm -rf $(DIR)
