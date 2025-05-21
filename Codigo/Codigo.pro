TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Funciones.cpp \
        alojamiento.cpp \
        anfitrion.cpp \
        fecha.cpp \
        huesped.cpp \
        main.cpp \
        reserva.cpp

HEADERS += \
    alojamiento.h \
    anfitrion.h \
    fecha.h \
    huesped.h \
    reserva.h

DISTFILES += \
    Alojamientos.txt \
    Comentarios.txt \
    Reserva.txt \
    Usuarios.txt
