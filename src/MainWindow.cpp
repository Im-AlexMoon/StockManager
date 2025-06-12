#include "MainWindow.h"
#include "VentanaProducto.h"
#include "VentanaProveedor.h"
#include "VentanaTransaccion.h"
// #include "VentanaReporte.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    configurarUI();
    conectarSlots();
}

MainWindow::~MainWindow() {}

void MainWindow::configurarUI() {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    this->setWindowTitle("StockManager - Menú Principal");
    this->resize(400, 500);
    this->setStyleSheet("background-color: #141414; font-family: Arial;");

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignCenter);

    QLabel* titulo = new QLabel("STOCKMANAGER");
    titulo->setStyleSheet("color: white; font-size: 24px; font-weight: bold;");
    titulo->setAlignment(Qt::AlignCenter);
    layout->addWidget(titulo);

    // Botones
    botonProductos = new QPushButton("Productos");
    botonProveedores = new QPushButton("Proveedores");
    botonTransacciones = new QPushButton("Transacciones");
    botonReportes = new QPushButton("Reportes");

    QList<QPushButton*> botones = {botonProductos, botonProveedores, botonTransacciones, botonReportes};
    for (QPushButton* boton : botones) {
        boton->setFixedHeight(40);
        boton->setStyleSheet("background-color: #4F48EC; color: white; font-size: 16px;");
        layout->addWidget(boton);
    }

    central->setLayout(layout);
}

void MainWindow::conectarSlots() {
    connect(botonProductos, &QPushButton::clicked, this, [=]() {
        auto* ventana = new VentanaProducto(this);
        ventana->show();  // o ventana->exec() si es QDialog
    });

    connect(botonProveedores, &QPushButton::clicked, this, [=]() {
        auto* ventana = new VentanaProveedor(this);
        ventana->show();
    });

    connect(botonTransacciones, &QPushButton::clicked, this, [=]() {
        auto* ventana = new VentanaTransaccion(this);
        ventana->show();
    });

    // Puedes agregar conexiones similares para Reportes
}
