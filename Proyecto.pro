##########################################################
# Nombre del ejecutable y configuración de Qt
##########################################################
TEMPLATE = app
TARGET = main

QT += core gui widgets
CONFIG += c++17 console

##########################################################
# Indicamos la ruta de include/ (para MainWindow.h, etc.)
##########################################################
INCLUDEPATH += $$PWD/include

##########################################################
# Listado de fuentes y cabeceras de nuestro proyecto
##########################################################
SOURCES += \
    src/main.cpp \
    src/VentanaBase.cpp \
    src/VentanaProducto.cpp\
    src/VentanaProveedor.cpp \
    src/VentanaTransaccion.cpp \
    src/MainWindow.cpp \
    src/Producto.cpp \  
    src/ProductoElectronico.cpp \  
    src/ProductoPerecedero.cpp \  
    src/Transaccion.cpp \  
    src/Proveedor.cpp \
    src/Oferta.cpp
    
HEADERS += \
    include/VentanaBase.h \ 
    include/VentanaProducto.h \ 
    include/VentanaProveedor.h \
    include/VentanaTransaccion.h \
    include/MainWindow.h \
    include/MainWindow.h \
    include/Producto.h \  
    include/ProductoElectronico.h \  
    include/ProductoPerecedero.h \  
    include/Transaccion.h \  
    include/Proveedor.h \
    include/Oferta.h
