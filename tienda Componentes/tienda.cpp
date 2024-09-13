/**
 * @file tienda.cpp
 * @brief Implementación de un sistema de control de ventas de productos de cómputo, basado en el uso de 
 * Estructuras de Datos. Se establece la aplicación de listas enlazadas para el manejo de los productos, 
 * vendedores, clientes y ventas.
 * Para mejorar la organización de la información, se establece la creación de arboles binarios para el
 * manejo de los productos y vendedores.
 * Para el manejo de las ventas, se establece la creación de una cola de prioridad para el manejo de las ventas.
 * Para el manejo de los clientes, se establece la creación de una pila para el manejo de los clientes.
 * Para el manejo de los proveedores, se establece la creación de una cola para el manejo de los proveedores.
 * Para el manejo de los pagos, se establece la creación de una lista doblemente enlazada para el manejo de los pagos.
 * Para almacenar la información de los productos, vendedores, clientes, proveedores y pagos, se establece el uso de archivos.
 * @version 1.0
 * @date 2024-09-07
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

// Definición de las estructuras de datos:
// Vendedor: Estructura que almacena la información de un vendedor.
struct Vendedor {
    int id;
    string nombre;
    string apellido;
    string telefono;
    string correo;
    string direccion;
    float salario;
    double ventas_realizadas;
};

// Cliente: Estructura que almacena la información de un cliente.
struct Cliente {
    int id;
    string nombre;
    string apellido;
    string telefono;
    string correo;
    string direccion;
    string nit;
};

// Proveedor: Estructura que almacena la información de un proveedor.
struct Proveedor {
    int id;
    string nombre;
    string telefono;
    string correo;
    string tipo;
};

// Producto: Estructura que almacena la información de un producto.
struct Producto {
    string codigo;
    string nombre;
    float precio;
    int cantidad;
    string descripcion;
    string categoria;
    // Enlazar con el proveedor
    Proveedor proveedor;
    bool estado;
};

// Venta: Estructura que almacena la información de una venta.
struct Venta {
    int nro_venta;
    string fecha;
    // Enlazar con el cliente
    Cliente cliente;
    float total;
    // Enlazar con el vendedor
    Vendedor vendedor;
};

// DetalleVenta: Estructura que almacena la información de un detalle de venta.
struct DetalleVenta {
    int nro_detalle;
    // Enlazar con la venta
    Venta venta;
    // Enlazar con el producto
    Producto producto;
    int cantidad;
    float subtotal;
};

// Variables globales:
list<Producto> productos;
map<string, Producto> productos_codigo;
map<string, list<Producto>> productos_categoria;
queue<Proveedor> proveedores;
list<Vendedor> vendedores;
queue<Vendedor> vendedores_nuevos;
list<Cliente> clientes;
queue<Cliente> clientes_nuevos;
stack<Cliente> clientes_pila;
list<Venta> ventas;
list<DetalleVenta> detalles_ventas;



// Definición de funciones:
// Funciones para el manejo de productos:
void agregarProducto(list<Producto> &productos, map<string, Producto> &productos_codigo, map<string, list<Producto>> &productos_categoria, queue<Proveedor> &proveedores);
void modificarProducto(list<Producto> &productos, map<string, Producto> &productos_codigo, map<string, list<Producto>> &productos_categoria);
void eliminarProducto(list<Producto> &productos, map<string, Producto> &productos_codigo, map<string, list<Producto>> &productos_categoria);
void mostrarProductos(list<Producto> &productos);

// Funciones para el manejo de clientes:
void agregarCliente(list<Cliente> &clientes);
void mostrarClientes(list<Cliente> &clientes);
void verificarClienteNuevo(queue<Cliente> &clientes_nuevos);
void mostrarClienteNuevo(queue<Cliente> &clientes_nuevos);

// Funciones para el manejo de ventas:
void agregarVenta(list<Venta> &ventas, list<DetalleVenta> &detalles_ventas, list<Producto> &productos, list<Cliente> &clientes, list<Vendedor> &vendedores);
void mostrarVentas(list<Venta> &ventas, list<DetalleVenta> &detalles_ventas);
void mostrarDetalleVenta(list<DetalleVenta> &detalles_ventas);
void actualizarMontoTotal(list<Cliente> &clientes, list<Venta> &ventas);

// Funciones para el manejo de vendedores:
void agregarVendedor(list<Vendedor> &vendedores);
void mostrarVendedores(list<Vendedor> &vendedores);
void verificarVendedorNuevo(queue<Vendedor> &vendedores_nuevos);
void mostrarVendedorNuevo(queue<Vendedor> &vendedores_nuevos);

// Función para cargar la información de los archivos:
void cargarInformacion(list<Producto> &productos, map<string, Producto> &productos_codigo, map<string, list<Producto>> &productos_categoria, list<Cliente> &clientes, list<Venta> &ventas, list<Vendedor> &vendedores, queue<Proveedor> &proveedores);

// Función para guardar la información en archivos:
void guardarInformacion(list<Producto> &productos, map<string, Producto> &productos_codigo, map<string, list<Producto>> &productos_categoria, list<Cliente> &clientes, list<Venta> &ventas, list<Vendedor> &vendedores, queue<Proveedor> &proveedores);

// Función para mostrar el menú principal de opciones:
void mostrarMenuPrincipal();

// Función para mostrar el menú de opciones de productos:
void mostrarMenuProductos();

// Función para mostrar el menú de opciones de clientes:
void mostrarMenuClientes();

// Función para mostrar el menú de opciones de ventas:
void mostrarMenuVentas();

// Función para mostrar el menú de opciones de vendedores:
void mostrarMenuVendedores();


// Función principal:
int main()
{
    int opcion, opcion2;
    system("cls");

    // Cargar la información de los archivos:
    cargarInformacion(productos, productos_codigo, productos_categoria, clientes, ventas, vendedores, proveedores);

    do {
        mostrarMenuPrincipal();
        cin >> opcion;
        system("cls");
        switch (opcion){
            case 1:
                mostrarMenuVendedores();
                cin >> opcion2;
                system("cls");
                switch (opcion2){
                    case 1:
                        agregarVendedor(vendedores);
                        break;
                    case 2:
                        mostrarVendedores(vendedores);
                        break;
                    case 3:
                        verificarVendedorNuevo(vendedores_nuevos);
                        break;
                    case 4:
                        mostrarVendedorNuevo(vendedores_nuevos);
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Opción no válida." << endl;
                        break;
                }
                break;
            case 2:
                mostrarMenuProductos();
                cin >> opcion2;
                system("cls");
                switch (opcion2){
                    case 1:
                        agregarProducto(productos, productos_codigo, productos_categoria, proveedores);
                        break;
                    case 2:
                        modificarProducto(productos, productos_codigo, productos_categoria);
                        break;
                    case 3:
                        eliminarProducto(productos, productos_codigo, productos_categoria);
                        break;
                    case 4:
                        mostrarProductos(productos);
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Opción no válida." << endl;
                        break;
                }
                break;
            case 3:
                mostrarMenuVentas();
                cin >> opcion2;
                system("cls");
                switch (opcion2){
                    case 1:
                        agregarVenta(ventas, detalles_ventas, productos, clientes, vendedores);
                        break;
                    case 2:
                        mostrarVentas(ventas, detalles_ventas);
                        break;
                    case 3:
                        mostrarDetalleVenta(detalles_ventas);
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Opción no válida." << endl;
                        break;
                }
                break;
            case 4:
                mostrarMenuClientes();
                cin >> opcion2;
                system("cls");
                switch (opcion2){
                    case 1:
                        agregarCliente(clientes);
                        break;
                    case 2:
                        mostrarClientes(clientes);
                        break;
                    case 3:
                        verificarClienteNuevo(clientes_nuevos);
                        break;
                    case 4:
                        mostrarClienteNuevo(clientes_nuevos);
                        break;
                    case 5:
                        actualizarMontoTotal(clientes, ventas);
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Opción no válida." << endl;
                        break;
                }
                break;
            case 5:
                mostrarVentas(ventas, detalles_ventas);
                break;
            case 0:
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
    } while (opcion != 0);

    // Guardar la información en los archivos:
    guardarInformacion(productos, productos_codigo, productos_categoria, clientes, ventas, vendedores, proveedores);

    
    return 0;
}

// Implementación de funciones:
void agregarProducto(list<Producto> &productos, map<string, Producto> &productos_codigo, map<string, list<Producto>> &productos_categoria, queue<Proveedor> &proveedores){
    Producto producto;

    // Ingresar la información del producto y corregir el error de ingreso de datos:
    cout << "Ingrese el código del producto: ";
    // Leer y validar el código del producto, si el código ya existe, solicitar un nuevo código:
    map<string, Producto>::iterator it;
    do{
        cin >> producto.codigo;
        it = productos_codigo.find(producto.codigo);
        if (it != productos_codigo.end()){
            cout << "El código del producto ya existe. Ingrese un nuevo código: ";
        }
    } while (it != productos_codigo.end());
    // Ingresar el resto de la información del producto:
    // Ingresar el nombre del producto permitiendo espacios:
    cin.ignore();
    cout << "Ingrese el nombre del producto: ";
    getline(cin, producto.nombre);
    //cin >> producto.nombre;
    cout << "Ingrese el precio del producto: ";
    cin >> producto.precio;
    cout << "Ingrese la cantidad del producto: ";
    cin >> producto.cantidad;
    //cin.ignore();
    cout << "Ingrese la descripción del producto: ";
    getline(cin, producto.descripcion);
    //cin >> producto.descripcion;
    //cin.ignore();
    cout << "Ingrese la categoría del producto: ";
    getline(cin, producto.categoria);
    //cin >> producto.categoria;
    cout << "Ingrese el estado del producto: ";
    cin >> producto.estado;

    cout << "Ingrese el id del proveedor: ";

    int id_proveedor;
    cin >> id_proveedor;
    queue<Proveedor> proveedores_aux;
    Proveedor proveedor;
    while (!proveedores.empty()){
        proveedor = proveedores.front();
        proveedores.pop();
        if (proveedor.id == id_proveedor){
            producto.proveedor = proveedor;
        }
        proveedores_aux.push(proveedor);
    }
    proveedores = proveedores_aux;
    productos.push_back(producto);
    productos_codigo[producto.codigo] = producto;
    productos_categoria[producto.categoria].push_back(producto);
}

void modificarProducto(list<Producto> &productos, map<string, Producto> &productos_codigo, map<string, list<Producto>> &productos_categoria){
    string codigo;
    cout << "Ingrese el código del producto a modificar: ";
    cin >> codigo;
    map<string, Producto>::iterator it = productos_codigo.find(codigo);
    if (it != productos_codigo.end()){
        Producto producto = it->second;
        cout << "Ingrese el nuevo nombre del producto: ";
        cin >> producto.nombre;
        cout << "Ingrese el nuevo precio del producto: ";
        cin >> producto.precio;
        cout << "Ingrese la nueva cantidad del producto: ";
        cin >> producto.cantidad;
        cout << "Ingrese la nueva descripción del producto: ";
        cin >> producto.descripcion;
        cout << "Ingrese la nueva categoría del producto: ";
        cin >> producto.categoria;
        cout << "Ingrese el nuevo estado del producto: ";
        cin >> producto.estado;
        productos_codigo[codigo] = producto;
        list<Producto> productos_aux;
        for (list<Producto>::iterator it = productos.begin(); it != productos.end(); it++){
            if (it->codigo == codigo){
                productos_aux.push_back(producto);
            } else {
                productos_aux.push_back(*it);
            }
        }
        productos = productos_aux;
        list<Producto> productos_categoria_aux;
        for (map<string, list<Producto>>::iterator it = productos_categoria.begin(); it != productos_categoria.end(); it++){
            if (it->first == producto.categoria){
                for (list<Producto>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
                    if (it2->codigo == codigo){
                        productos_categoria_aux.push_back(producto);
                    } else {
                        productos_categoria_aux.push_back(*it2);
                    }
                }
            } else {
                productos_categoria_aux = it->second;
            }
        }
        productos_categoria[producto.categoria] = productos_categoria_aux;
    } else {
        cout << "El producto no existe." << endl;
    }
}

void eliminarProducto(list<Producto> &productos, map<string, Producto> &productos_codigo, map<string, list<Producto>> &productos_categoria){
    string codigo;
    cout << "Ingrese el código del producto a eliminar: ";
    cin >> codigo;
    map<string, Producto>::iterator it = productos_codigo.find(codigo);
    if (it != productos_codigo.end()){
        Producto producto = it->second;
        productos_codigo.erase(codigo);
        list<Producto> productos_aux;
        for (list<Producto>::iterator it = productos.begin(); it != productos.end(); it++){
            if (it->codigo != codigo){
                productos_aux.push_back(*it);
            }
        }
        productos = productos_aux;
        list<Producto> productos_categoria_aux;
        for (map<string, list<Producto>>::iterator it = productos_categoria.begin(); it != productos_categoria.end(); it++){
            if (it->first == producto.categoria){
                for (list<Producto>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
                    if (it2->codigo != codigo){
                        productos_categoria_aux.push_back(*it2);
                    }
                }
            } else {
                productos_categoria_aux = it->second;
            }
        }
        productos_categoria[producto.categoria] = productos_categoria_aux;
    } else {
        cout << "El producto no existe." << endl;
    }
}

void mostrarProductos(list<Producto> &productos){
    for (list<Producto>::iterator it = productos.begin(); it != productos.end(); it++){
        cout << "------------------------------------------" << endl;
        cout << "Código: " << it->codigo << endl;
        cout << "Nombre: " << it->nombre << endl;
        cout << "Precio: " << it->precio << endl;
        cout << "Cantidad: " << it->cantidad << endl;
        cout << "Descripción: " << it->descripcion << endl;
        cout << "Categoría: " << it->categoria << endl;
        cout << "Proveedor: " << it->proveedor.nombre << endl;
        cout << "Estado: " << it->estado << endl;
        cout << "-----------------------------------------" << endl;
        cout << endl;
    }
}

void agregarCliente(list<Cliente> &clientes){
    Cliente cliente;
    cout << "Ingrese el nombre del cliente: ";
    cin >> cliente.nombre;
    cout << "Ingrese el apellido del cliente: ";
    cin >> cliente.apellido;
    cout << "Ingrese el teléfono del cliente: ";
    cin >> cliente.telefono;
    cout << "Ingrese el correo del cliente: ";
    cin >> cliente.correo;
    cout << "Ingrese la dirección del cliente: ";
    cin >> cliente.direccion;
    cout << "Ingrese el NIT del cliente: ";
    cin >> cliente.nit;
    clientes.push_back(cliente);
}

void mostrarClientes(list<Cliente> &clientes){
    for (list<Cliente>::iterator it = clientes.begin(); it != clientes.end(); it++){
        cout << "Nombre: " << it->nombre << endl;
        cout << "Apellido: " << it->apellido << endl;
        cout << "Teléfono: " << it->telefono << endl;
        cout << "Correo: " << it->correo << endl;
        cout << "Dirección: " << it->direccion << endl;
        cout << "NIT: " << it->nit << endl;
    }
}

void verificarClienteNuevo(queue<Cliente> &clientes_nuevos){
    if (!clientes_nuevos.empty()){
        Cliente cliente = clientes_nuevos.front();
        cout << "Cliente nuevo: " << cliente.nombre << " " << cliente.apellido << endl;
    } else {
        cout << "No hay clientes nuevos." << endl;
    }
}

void mostrarClienteNuevo(queue<Cliente> &clientes_nuevos){
    if (!clientes_nuevos.empty()){
        Cliente cliente = clientes_nuevos.front();
        cout << "Nombre: " << cliente.nombre << endl;
        cout << "Apellido: " << cliente.apellido << endl;
        cout << "Teléfono: " << cliente.telefono << endl;
        cout << "Correo: " << cliente.correo << endl;
        cout << "Dirección: " << cliente.direccion << endl;
        cout << "NIT: " << cliente.nit << endl;
    } else {
        cout << "No hay clientes nuevos." << endl;
    }
}

void actualizarMontoTotal(list<Cliente> &clientes, list<Venta> &ventas){
    for (list<Cliente>::iterator it = clientes.begin(); it != clientes.end(); it++){
        float total = 0;
        for (list<Venta>::iterator it2 = ventas.begin(); it2 != ventas.end(); it2++){
            if (it->id == it2->cliente.id){
                total += it2->total;
            }
        }
        cout << "Cliente: " << it->nombre << " " << it->apellido << endl;
        cout << "Monto total: " << total << endl;
    }
}

void agregarVenta(list<Venta> &ventas, list<DetalleVenta> &detalles_ventas, list<Producto> &productos, list<Cliente> &clientes, list<Vendedor> &vendedores){
    Venta venta;
    cout << "Ingrese el número de venta: ";
    cin >> venta.nro_venta;
    cout << "Ingrese la fecha de la venta: ";
    cin >> venta.fecha;
    cout << "Ingrese el nombre del cliente: ";
    string nombre_cliente;
    cin >> nombre_cliente;
    list<Cliente>::iterator it = find_if(clientes.begin(), clientes.end(), [nombre_cliente](Cliente cliente){
        return cliente.nombre == nombre_cliente;
    });
    if (it != clientes.end()){
        venta.cliente = *it;
    } else {
        cout << "El cliente no existe." << endl;
        return;
    }
    cout << "Ingrese el total de la venta: ";
    cin >> venta.total;
    cout << "Ingrese el nombre del vendedor: ";
    string nombre_vendedor;
    cin >> nombre_vendedor;
    list<Vendedor>::iterator it2 = find_if(vendedores.begin(), vendedores.end(), [nombre_vendedor](Vendedor vendedor){
        return vendedor.nombre == nombre_vendedor;
    });
    if (it2 != vendedores.end()){
        venta.vendedor = *it2;
    } else {
        cout << "El vendedor no existe." << endl;
        return;
    }
    ventas.push_back(venta);
    int nro_detalle = 1;
    int opcion;
    do{
        DetalleVenta detalle_venta;
        detalle_venta.nro_detalle = nro_detalle;
        detalle_venta.venta = venta;
        cout << "Ingrese el código del producto: ";
        string codigo;
        cin >> codigo;
        list<Producto>::iterator it3 = find_if(productos.begin(), productos.end(), [codigo](Producto producto){
            return producto.codigo == codigo;
        });
        if (it3 != productos.end()){
            detalle_venta.producto = *it3;
        } else {
            cout << "El producto no existe." << endl;
            return;
        }
        cout << "Ingrese la cantidad del producto: ";
        cin >> detalle_venta.cantidad;
        detalle_venta.subtotal = detalle_venta.cantidad * detalle_venta.producto.precio;
        detalles_ventas.push_back(detalle_venta);
        nro_detalle = nro_detalle + 1;
        cout << "Desea agregar otro producto a la venta? (1. Sí, 0. No): ";
        cin >> opcion;
    } while (opcion != 0);
}

void mostrarVentas(list<Venta> &ventas, list<DetalleVenta> &detalles_ventas){
    for (list<Venta>::iterator it = ventas.begin(); it != ventas.end(); it++){
        cout << "Número de venta: " << it->nro_venta << endl;
        cout << "Fecha: " << it->fecha << endl;
        cout << "Cliente: " << it->cliente.nombre << " " << it->cliente.apellido << endl;
        cout << "Total: " << it->total << endl;
        cout << "Vendedor: " << it->vendedor.nombre << " " << it->vendedor.apellido << endl;
        for (list<DetalleVenta>::iterator it2 = detalles_ventas.begin(); it2 != detalles_ventas.end(); it2++){
            if (it->nro_venta == it2->venta.nro_venta){
                cout << "Número de detalle: " << it2->nro_detalle << endl;
                cout << "Producto: " << it2->producto.nombre << endl;
                cout << "Cantidad: " << it2->cantidad << endl;
                cout << "Subtotal: " << it2->subtotal << endl;
            }
        }
    }
}

void mostrarDetalleVenta(list<DetalleVenta> &detalles_ventas){
    for (list<DetalleVenta>::iterator it = detalles_ventas.begin(); it != detalles_ventas.end(); it++){
        cout << "Número de detalle: " << it->nro_detalle << endl;
        cout << "Venta: " << it->venta.nro_venta << endl;
        cout << "Producto: " << it->producto.nombre << endl;
        cout << "Cantidad: " << it->cantidad << endl;
        cout << "Subtotal: " << it->subtotal << endl;
    }
}

void agregarVendedor(list<Vendedor> &vendedores){
    Vendedor vendedor;
    cout << "Ingrese el nombre del vendedor: ";
    cin >> vendedor.nombre;
    cout << "Ingrese el apellido del vendedor: ";
    cin >> vendedor.apellido;
    cout << "Ingrese el teléfono del vendedor: ";
    cin >> vendedor.telefono;
    cout << "Ingrese el correo del vendedor: ";
    cin >> vendedor.correo;
    cout << "Ingrese la dirección del vendedor: ";
    cin >> vendedor.direccion;
    cout << "Ingrese el salario del vendedor: ";
    cin >> vendedor.salario;
    cout << "Ingrese las ventas realizadas del vendedor: ";
    cin >> vendedor.ventas_realizadas;
    vendedores.push_back(vendedor);
}

void mostrarVendedores(list<Vendedor> &vendedores){
    for (list<Vendedor>::iterator it = vendedores.begin(); it != vendedores.end(); it++){
        cout << "Nombre: " << it->nombre << endl;
        cout << "Apellido: " << it->apellido << endl;
        cout << "Teléfono: " << it->telefono << endl;
        cout << "Correo: " << it->correo << endl;
        cout << "Dirección: " << it->direccion << endl;
        cout << "Salario: " << it->salario << endl;
        cout << "Ventas realizadas: " << it->ventas_realizadas << endl;
    }
}

void verificarVendedorNuevo(queue<Vendedor> &vendedores_nuevos){
    if (!vendedores_nuevos.empty()){
        Vendedor vendedor = vendedores_nuevos.front();
        cout << "Vendedor nuevo: " << vendedor.nombre << " " << vendedor.apellido << endl;
    } else {
        cout << "No hay vendedores nuevos." << endl;
    }
}

void mostrarVendedorNuevo(queue<Vendedor> &vendedores_nuevos){
    if (!vendedores_nuevos.empty()){
        Vendedor vendedor = vendedores_nuevos.front();
        cout << "Nombre: " << vendedor.nombre << endl;
        cout << "Apellido: " << vendedor.apellido << endl;
        cout << "Teléfono: " << vendedor.telefono << endl;
        cout << "Correo: " << vendedor.correo << endl;
        cout << "Dirección: " << vendedor.direccion << endl;
        cout << "Salario: " << vendedor.salario << endl;
        cout << "Ventas realizadas: " << vendedor.ventas_realizadas << endl;
    } else {
        cout << "No hay vendedores nuevos." << endl;
    }
}

// Función para cargar la información de los archivos:
void cargarInformacion(list<Producto> &productos, map<string, Producto> &productos_codigo, map<string, list<Producto>> &productos_categoria, list<Cliente> &clientes, list<Venta> &ventas, list<Vendedor> &vendedores, queue<Proveedor> &proveedores){
    // Cargar la información de los productos desde un archivo:
    ifstream archivo_productos("productos.txt");
    if (archivo_productos.is_open()){
        Producto producto;
        while (archivo_productos >> producto.codigo >> producto.nombre >> producto.precio >> producto.cantidad >> producto.descripcion >> producto.categoria >> producto.proveedor.nombre >> producto.estado){
            productos.push_back(producto);
            productos_codigo[producto.codigo] = producto;
            productos_categoria[producto.categoria].push_back(producto);
        }
        archivo_productos.close();
    }

    // Cargar la información de los clientes desde un archivo:
    ifstream archivo_clientes("clientes.txt");
    if (archivo_clientes.is_open()){
        Cliente cliente;
        while (archivo_clientes >> cliente.nombre >> cliente.apellido >> cliente.telefono >> cliente.correo >> cliente.direccion >> cliente.nit){
            clientes.push_back(cliente);
        }
        archivo_clientes.close();
    }

    // Cargar la información de las ventas desde un archivo:
    ifstream archivo_ventas("ventas.txt");
    if (archivo_ventas.is_open()){
        Venta venta;
        while (archivo_ventas >> venta.nro_venta >> venta.fecha >> venta.cliente.nombre >> venta.total >> venta.vendedor.nombre){
            ventas.push_back(venta);
        }
        archivo_ventas.close();
    }

    // Cargar la información de los vendedores desde un archivo:
    ifstream archivo_vendedores("vendedores.txt");
    if (archivo_vendedores.is_open()){
        Vendedor vendedor;
        while (archivo_vendedores >> vendedor.nombre >> vendedor.apellido >> vendedor.telefono >> vendedor.correo >> vendedor.direccion >> vendedor.salario >> vendedor.ventas_realizadas){
            vendedores.push_back(vendedor);
        }
        archivo_vendedores.close();
    }

    // Cargar la información de los proveedores desde un archivo:
    ifstream archivo_proveedores("proveedores.txt");
    if (archivo_proveedores.is_open()){
        Proveedor proveedor;
        while (archivo_proveedores >> proveedor.id >> proveedor.nombre >> proveedor.telefono >> proveedor.correo){
            proveedores.push(proveedor);
        }
        archivo_proveedores.close();
    }
}


// Función para guardar la información en archivos:
void guardarInformacion(list<Producto> &productos, map<string, Producto> &productos_codigo, map<string, list<Producto>> &productos_categoria, list<Cliente> &clientes, list<Venta> &ventas, list<Vendedor> &vendedores, queue<Proveedor> &proveedores){
    // Guardar la información de los productos en un archivo:
    ofstream archivo_productos("productos.txt");
    for (list<Producto>::iterator it = productos.begin(); it != productos.end(); it++){
        archivo_productos << it->codigo << " " << it->nombre << " " << it->precio << " " << it->cantidad << " " << it->descripcion << " " << it->categoria << " " << it->proveedor.nombre << " " << it->estado << endl;
    }
    archivo_productos.close();
    // Guardar la información de los clientes en un archivo:
    ofstream archivo_clientes("clientes.txt");
    for (list<Cliente>::iterator it = clientes.begin(); it != clientes.end(); it++){
        archivo_clientes << it->nombre << " " << it->apellido << " " << it->telefono << " " << it->correo << " " << it->direccion << " " << it->nit << endl;
    }
    archivo_clientes.close();
    // Guardar la información de las ventas en un archivo:
    ofstream archivo_ventas("ventas.txt");
    for (list<Venta>::iterator it = ventas.begin(); it != ventas.end(); it++){
        archivo_ventas << it->nro_venta << " " << it->fecha << " " << it->cliente.nombre << " " << it->total << " " << it->vendedor.nombre << endl;
    }
    archivo_ventas.close();
    // Guardar la información de los vendedores en un archivo:
    ofstream archivo_vendedores("vendedores.txt");
    for (list<Vendedor>::iterator it = vendedores.begin(); it != vendedores.end(); it++){
        archivo_vendedores << it->nombre << " " << it->apellido << " " << it->telefono << " " << it->correo << " " << it->direccion << " " << it->salario << " " << it->ventas_realizadas << endl;
    }
    archivo_vendedores.close();
    // Guardar la información de los proveedores en un archivo:
    ofstream archivo_proveedores("proveedores.txt");
    while (!proveedores.empty()){
        Proveedor proveedor = proveedores.front();
        archivo_proveedores << proveedor.id << " " << proveedor.nombre << " " << proveedor.telefono << " " << proveedor.correo << endl;
        proveedores.pop();
    }
    archivo_proveedores.close();
}


void mostrarMenuPrincipal(){
    cout << "¡Bienvenido a la Tienda de Productos de Cómputo!" << endl;
    cout << "1. Vendedores\n";
    cout << "2. Productos\n";
    cout << "3. Ventas\n";
    cout << "4. Clientes\n";
    cout << "5. Listar Ventas\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
}

void mostrarMenuProductos(){
    cout << "Menú de opciones de productos:" << endl;
    cout << "1. Agregar producto\n";
    cout << "2. Modificar producto\n";
    cout << "3. Eliminar producto\n";
    cout << "4. Mostrar productos\n";
    cout << "0. Volver al menú principal\n";
    cout << "Seleccione una opción: ";
}

void mostrarMenuClientes(){
    cout << "Menú de opciones de clientes:" << endl;
    cout << "1. Agregar cliente\n";
    cout << "2. Mostrar clientes\n";
    cout << "3. Verificar cliente nuevo\n";
    cout << "4. Mostrar cliente nuevo\n";
    cout << "5. Actualizar monto total\n";
    cout << "0. Volver al menú principal\n";
    cout << "Seleccione una opción: ";
}

void mostrarMenuVentas(){
    cout << "Menú de opciones de ventas:" << endl;
    cout << "1. Agregar venta\n";
    cout << "2. Mostrar ventas\n";
    cout << "3. Mostrar detalle de venta\n";
    cout << "0. Volver al menú principal\n";
    cout << "Seleccione una opción: ";
}

void mostrarMenuVendedores(){
    cout << "Menú de opciones de vendedores:" << endl;
    cout << "1. Agregar vendedor\n";
    cout << "2. Mostrar vendedores\n";
    cout << "3. Verificar vendedor nuevo\n";
    cout << "4. Mostrar vendedor nuevo\n";
    cout << "0. Volver al menú principal\n";
    cout << "Seleccione una opción: ";
}

