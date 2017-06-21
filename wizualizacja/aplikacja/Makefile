APLIKACJA=wizualizacja
URUCHOM_APLIKACJE=./wizualizacja
ZRODLA=`/bin/pwd`/src/*.cpp `/bin/pwd`/inc/*.h* `/bin/pwd`/res/*.qrc
KATALOG_MOC=./moc
KATALOG_OBJ=./obj
KATALOG_RCC=./rcc
ZMIENNE_PROJ= OBJECTS_DIR=${KATALOG_OBJ} MOC_DIR=${KATALOG_MOC} QT+=widgets QT+=network QT+=printsupport QT+=opengl QT+=xml\
	LIBS+=-L/usr/opt/lib LIBS+=-lQGLViewer QMAKE_RESOURCE_FLAGS=-no-compress RCC_DIR=${KATALOG_RCC}

start : ${APLIKACJA} clean
	rm -f core*; ${URUCHOM_APLIKACJE}

${APLIKACJA}: Makefile.app __sprawdz__

__sprawdz__ :
	make -f Makefile.app

Makefile.app: pro/${APLIKACJA}.pro
	qmake -o Makefile.app pro/${APLIKACJA}.pro

pro/${APLIKACJA}.pro:
	qmake -project -o pro/${APLIKACJA}.pro ${ZMIENNE_PROJ} ${ZRODLA}

clean:
	rm -rf ${KATALOG_OBJ} ${KATALOG_MOC} ${KATALOG_RCC} pro Makefile.app
