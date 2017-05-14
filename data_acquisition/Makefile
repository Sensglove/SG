NAZWA_APLIKACJI=d_a
URUCHOMIENIE_APLIKACJI=./${NAZWA_APLIKACJI}
ZRODLA_PROJEKTU=`/bin/pwd`/src/*.cpp `/bin/pwd`/inc/*.cpp
PODSTAWIENIA=OBJECTS_DIR=${KATALOG_OBJ}\
             INCLUDEPATH=inc\
             MOC_DIR=${KATALOG_MOC}\
             RCC_DIR=./rcc\
             QT+=widgets\
             QMAKE_CXXFLAGS+=-std=c++11

KATALOG_OBJ=./obj
KATALOG_MOC=./moc

CPPFLAGS=-Wall -pedantic -Iinc -Iinc/rs232
LFLAGS=-Wall

__start__: __sprawdz_Qt__ ${NAZWA_APLIKACJI}
	#rm -f core*; ${URUCHOMIENIE_APLIKACJI}
	@echo
	@echo " Utworzono aplikacje:  odbiornik-qt (nasluchuje na porcie /dev/ttyUSB1)"
	@echo "                       nadawanie    (transmituje do portu /dev/ttyUSB0)"
	@echo

__sprawdz_Qt__: __sprawdz_qmake__
	@if qmake -v | grep 'ver.*4\.[0-9]*\.[0-9]*' > /dev/null;\
         then exit 0;\
         else echo; echo " Brak biblioteki Qt w wersji 5.x.x";\
              echo;  exit 1;\
        fi

__sprawdz_qmake__:
	@if which qmake > /dev/null; then exit 0;\
        else\
          echo; echo " Brak programu qmake."\
               " Prawdopodobnie biblioteka Qt nie zostala zainstalowana.";\
          echo; exit 1;\
        fi


${NAZWA_APLIKACJI}: Makefile.app  __sprawdz__ 

__sprawdz__:
	make -f Makefile.app

Makefile.app: pro/${NAZWA_APLIKACJI}.pro
	qmake -o Makefile.app pro/${NAZWA_APLIKACJI}.pro

pro/${NAZWA_APLIKACJI}.pro: Makefile
	rm -fr pro/
	qmake -project -nopwd -o pro/${NAZWA_APLIKACJI}.pro\
               ${PODSTAWIENIA} ${ZRODLA_PROJEKTU} 

project: __usun_pro__ pro/${NAZWA_APLIKACJI}.pro

__usun_pro__:
	rm -f pro/${NAZWA_APLIKACJI}.pro

clean:
	rm -f nadawanie
	make -f Makefile.app clean


cleanall: clean
	rm -f ${NAZWA_APLIKACJI}

__clean_auxiliary_files__:
	find . -name \*~ -exec rm {} \;
	find . -name \*.tex -exec rm {} \;

cleantotally: __clean_auxiliary_files__ cleanall
	rm -f  Makefile.app
	rm -fr ${KATALOG_MOC} ${KATALOG_OBJ}
	rm -rf pro/

help:
	@echo "Podcele:"
	@echo 
	@echo " project  - wymusza utworzenie nowego projektu"
	@echo " clean    - usuwa wszystkie produkty kompilacji i konsolidacji"
	@echo " cleanall - usuwa produkty kompilacji wraz z aplikacja"
	@echo " cleantotally - usuwa wszystko oprocz zrodel i pliku Makefile"
	@echo " help     - wyswietla niniejszy pomoc"
	@echo
