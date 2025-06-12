#include "VentanaTransaccion.h"
#include <QFormLayout>

VentanaTransaccion::VentanaTransaccion(QWidget *parent) : VentanaBase(parent) {
    configurarUI();
    conectarSlots();
}

VentanaTransaccion::~VentanaTransaccion() {}

void VentanaTransaccion::configurarUI() {
    this->resize(700, 400);

    QLabel* titulo = new QLabel("Gestión de Transacciones");
    titulo->setStyleSheet("color: white; font-size: 20px;");
    titulo->setAlignment(Qt::AlignCenter);

    campoProducto = new QLineEdit();
    campoProducto->setPlaceholderText("Nombre del Producto");

    campoProveedor = new QLineEdit();
    campoProveedor->setPlaceholderText("Proveedor");

    campoFecha = new QLineEdit();
    campoFecha->setPlaceholderText("Fecha");

    campoCantidad = new QSpinBox();
    campoCantidad->setRange(1, 10000);

    QFormLayout* formulario = new QFormLayout();
    formulario->addRow("Producto:", campoProducto);
    formulario->addRow("Proveedor:", campoProveedor);
    formulario->addRow("Fecha:", campoFecha);
    formulario->addRow("Cantidad:", campoCantidad);

    botonComprar = new QPushButton("Registrar Compra");
    botonVender  = new QPushButton("Registrar Venta");

    QHBoxLayout* botones = new QHBoxLayout();
    botones->addWidget(botonComprar);
    botones->addWidget(botonVender);

    tablaTransacciones = new QTableView();
    modeloTransacciones = new QStandardItemModel(this);
    modeloTransacciones->setHorizontalHeaderLabels({"ID", "Producto", "Proveedor", "Fecha", "Cantidad", "Tipo"});
    tablaTransacciones->setModel(modeloTransacciones);
    tablaTransacciones->setStyleSheet("color: white; background-color: #1E1E1E; border: 1px solid #FFBF18;");

    layoutPrincipal->addWidget(titulo);
    layoutPrincipal->addLayout(formulario);
    layoutPrincipal->addLayout(botones);
    layoutPrincipal->addWidget(tablaTransacciones);
    layoutPrincipal->addStretch();
}

void VentanaTransaccion::conectarSlots() {
    connect(botonComprar, &QPushButton::clicked, this, [=]() { registrarCompra(); });
    connect(botonVender,  &QPushButton::clicked, this, [=]() { registrarVenta();  });
}

void VentanaTransaccion::limpiarFormulario() {
    campoProducto->clear();
    campoProveedor->clear();
    campoFecha->clear();
    campoCantidad->setValue(1);
}

void VentanaTransaccion::registrarCompra() {
    QString prod  = campoProducto->text();
    QString prov  = campoProveedor->text();
    QString fecha = campoFecha->text();

    if (prod.isEmpty() || prov.isEmpty() || fecha.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos deben estar completos.");
        return;
    }

    int cant = campoCantidad->value();
    static int idCounter = 1;

    Producto* producto   = new Producto(idCounter, prod.toStdString(), 0.0f, 0);
    Proveedor* proveedor = new Proveedor(idCounter, prov.toStdString());
    Oferta oferta(producto->getId(), prod.toStdString(), 0.0f, 0,
                  idCounter, prov.toStdString(), 0.0f, "Compra");
    oferta.mostrarOferta();

    Transaccion t(idCounter, fecha.toStdString(), producto, cant);
    t.comprar();
    listaTransacciones.push_back(t);

    QList<QStandardItem*> fila;
    fila << new QStandardItem(QString::number(idCounter))
         << new QStandardItem(prod)
         << new QStandardItem(prov)
         << new QStandardItem(fecha)
         << new QStandardItem(QString::number(cant))
         << new QStandardItem("Compra");
    modeloTransacciones->appendRow(fila);

    ++idCounter;
    limpiarFormulario();
}

void VentanaTransaccion::registrarVenta() {
    QString prod  = campoProducto->text();
    QString fecha = campoFecha->text();

    if (prod.isEmpty() || fecha.isEmpty()) {
        QMessageBox::warning(this, "Error", "Producto y fecha son requeridos.");
        return;
    }

    int cant = campoCantidad->value();
    static int idCounter = 1000;

    Producto* producto = new Producto(idCounter, prod.toStdString(), 0.0f, 0);
    Transaccion t(idCounter, fecha.toStdString(), producto, cant);
    t.vender();
    listaTransacciones.push_back(t);

    QList<QStandardItem*> fila;
    fila << new QStandardItem(QString::number(idCounter))
         << new QStandardItem(prod)
         << new QStandardItem("-")
         << new QStandardItem(fecha)
         << new QStandardItem(QString::number(cant))
         << new QStandardItem("Venta");
    modeloTransacciones->appendRow(fila);

    ++idCounter;
    limpiarFormulario();
}

