#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <cstring>

using namespace std;

// ==================== ESTRUCTURAS ====================

struct Usuario {
    int idUsuario;
    string nombre;
    string correoElectronico;
    string contrasena;
    string direccion;
    string metodoDePago;
    double bonoPorcentaje; // 0 = sin bono, 50 = 50% descuento
};

struct Producto {
    int idProducto;
    string nombre;
    string descripcion;
    double precio;
    int stock;
};

struct ProductoCarrito {
    Producto producto;
    int cantidad;
};

struct CarritoDeCompras {
    int idCarrito;
    int idUsuario;
    ProductoCarrito items[50];
    int cantItems;
    double subtotal;
    double impuestos;
    int pagado; // 0 = pendiente, 1 = pagado
};

struct OrdenDeCompra {
    int idOrden;
    int idUsuario;
    ProductoCarrito productos[50];
    int cantProductos;
    double subtotal;
    double impuestos;
    double envio;
    double descuento;
    double total;
};

struct Comentario {
    int idComentario;
    string producto;
    string usuario;
    string comentario;
    string fecha;
};

// ==================== VARIABLES GLOBALES ====================

CarritoDeCompras carritos[100];
int totalCarritos = 0;

OrdenDeCompra ordenes[100];
int totalOrdenes = 0;

Usuario usuarioActivo;

// ==================== PROTOTIPOS ====================

int  iniciarSesion(Usuario u[5], int &indiceUsuario);
////////////////////////////////////////////////////////
void cargarUsuarios(Usuario u[5]);
////////////////////////////////////////////////////////
void cargarProductos(Producto p[50]);
////////////////////////////////////////////////////////
void cargarComentarios(Comentario c[50]);
////////////////////////////////////////////////////////
void guardarProductos(Producto p[50]);
////////////////////////////////////////////////////////
void guardarCarrito();
////////////////////////////////////////////////////////
void cargarCarrito(Producto p [50]);
////////////////////////////////////////////////////////
void listarProductos(Producto p[50]);
////////////////////////////////////////////////////////
void mostrarComentarios(Comentario c[50]);
////////////////////////////////////////////////////////
void listarUsuarios(Usuario u[5]);
////////////////////////////////////////////////////////
void agregarAlCarrito(Producto p[50], int idUsuario);
////////////////////////////////////////////////////////
void listarCarritosUsuario(int idUsuario);
////////////////////////////////////////////////////////
void pagarCarrito(Producto p[50], int idUsuario, Usuario u[5]);
////////////////////////////////////////////////////////
void listarProductosMasVendidos();
////////////////////////////////////////////////////////
void mostrarGanancias(Usuario u[5]);
////////////////////////////////////////////////////////
void guardarOrdenEnArchivo(OrdenDeCompra &o, Usuario &u);
////////////////////////////////////////////////////////
int obtenerCarritosPendientes(int idUsuario);
////////////////////////////////////////////////////////
void guardarUsuarios(Usuario u[5]);
////////////////////////////////////////////////////////
void guardarOrdenes();
////////////////////////////////////////////////////////
void cargarOrdenes();
////////////////////////////////////////////////////////
string nombreToUpper(string s);
////////////////////////////////////////////////////////

// ==================== MAIN ====================

int main() {
    setlocale(LC_ALL, "spanish");

    Usuario usuarios[5];
    Producto productos[50];
    Comentario comentarios[50];


	cargarUsuarios(usuarios);
	cargarProductos(productos);
	cargarComentarios(comentarios);
	//cargarCarrito(productos);
	//cargarOrdenes();
	
    cout << "\n Bienvenido a Tecnonline" << endl;

    int indiceUsuario = -1;

    if (iniciarSesion(usuarios, indiceUsuario) == 1) {
        usuarioActivo = usuarios[indiceUsuario];

        int opc = 0;
        do {
            system("pause");
            system("cls");

            cout << "\n -----  PORTAL DE USUARIOS  -----" << endl;
            cout << "\n\t1. Listar Productos" << endl;
            cout << "\t2. Comentarios" << endl;
            cout << "\t3. Listar Usuarios" << endl;
            cout << "\t4. Agregar productos al carrito" << endl;
            cout << "\t5. Ver mis carritos" << endl;
            cout << "\t6. Pagar carrito" << endl;
            cout << "\t7. Productos mas vendidos" << endl;
            cout << "\t8. Ganancias de la plataforma" << endl;
            cout << "\t9. Salir" << endl;
            cout << "\n\tOpcion: "; cin >> opc;

            switch (opc) {
                case 1:
                    system("pause"); system("cls");
                    listarProductos(productos);
                    break;
                case 2:
                    system("pause"); system("cls");
                    mostrarComentarios(comentarios);
                    break;
                case 3:
                    system("pause"); system("cls");
                    listarUsuarios(usuarios);
                    break;
                case 4:
                    system("pause"); system("cls");
                    agregarAlCarrito(productos, usuarioActivo.idUsuario);
                    break;
                case 5:
                    system("pause"); system("cls");
                    //listarCarritosUsuario(usuarioActivo.idUsuario);
                    break;
                case 6:
                    system("pause"); system("cls");
                    //pagarCarrito(productos, usuarioActivo.idUsuario, usuarios);
                    // Actualizar usuario activo por si recibio bono
                    for (int i = 0; i < 5; i++) {
                        if (usuarios[i].idUsuario == usuarioActivo.idUsuario) {
                            usuarioActivo = usuarios[i];
                            break;
                        }
                    }
                    break;
                case 7:
                    system("pause"); system("cls");
                    //listarProductosMasVendidos();
                    break;
                case 8:
                    system("pause"); system("cls");
                    //mostrarGanancias(usuarios);
                    break;
                case 9:
                    system("pause"); system("cls");
                    cout << "Saliendo del portal..." << endl;
                    break;
                default:
                    system("pause"); system("cls");
                    cout << "Opcion invalida. Intente de nuevo." << endl;
            }

        } while (opc != 9);
    }

    system("pause");
    return 0;
}



// ==================== INICIO DE SESION ====================

int iniciarSesion(Usuario u[5], int &indiceUsuario) {
    setlocale(LC_ALL, "spanish");

    string nombre, contrasena;
    int aux = 0;

    do {
        cout << "\n -----  INICIO DE SESION  -----\n" << endl;
        cout << "Ingrese su nombre de usuario: ";
        fflush(stdin); getline(cin, nombre);
        cout << "Ingrese su contrasena: ";
        fflush(stdin); getline(cin, contrasena);

	
	for(int i=0; i<5; i++)
	{
	    if(nombre == u[i].nombre &&
	       contrasena == u[i].contrasena)
	    {
	        cout << "Inicio de sesion exitoso." << endl;
	        indiceUsuario = i;
	        return 1;
	    }
	}
	 
	    for (int i = 0; i < 5; i++) {
            if (nombre == u[i].nombre && contrasena == u[i].contrasena) {
                cout << "Inicio de sesion exitoso." << endl;
                indiceUsuario = i;
                return 1;
            }
        }

        if (aux == 0) {
            cout << "Usuario y/o contrasena invalidos. Por favor intente de nuevo." << endl;
            system("pause");
            system("cls");
        }

    } while (aux == 0);

    return 0;
}

// ==================== CARGA DE ARCHIVOS ====================

void cargarUsuarios(Usuario u[5])
{
    ifstream archivo("Usuarios.txt");

    string aux;

    getline(archivo, aux); // encabezado

    for(int i=0; i<5; i++)
    {
        getline(archivo, aux, ',');
        u[i].idUsuario = atoi(aux.c_str());

        getline(archivo, u[i].nombre, ',');
        getline(archivo, u[i].correoElectronico, ',');
        getline(archivo, u[i].contrasena, ',');
        getline(archivo, u[i].direccion, ',');
        getline(archivo, u[i].metodoDePago, ',');

        getline(archivo, aux);
        u[i].bonoPorcentaje = atof(aux.c_str());
    }

    archivo.close();
}

void cargarProductos(Producto p[50])
{
    ifstream archivo("productos.txt");

    string aux;

    getline(archivo, aux);

    for(int i=0;i<50;i++)
    {
        getline(archivo, aux, ',');
        p[i].idProducto = atoi(aux.c_str());

        getline(archivo, p[i].nombre, ',');
        getline(archivo, p[i].descripcion, ',');

        getline(archivo, aux, ',');
        p[i].precio = atof(aux.c_str());

        getline(archivo, aux);
        p[i].stock = atoi(aux.c_str());
    }

    archivo.close();
}

void cargarComentarios(Comentario c[50])
{
    ifstream archivo("Comentarios.txt");

    string aux;

    getline(archivo, aux);

    for(int i=0;i<50;i++)
    {
        getline(archivo, aux, ',');
        c[i].idComentario = atoi(aux.c_str());

        getline(archivo, c[i].producto, ',');
        getline(archivo, c[i].usuario, ',');
        getline(archivo, c[i].comentario, ',');
        getline(archivo, c[i].fecha);
    }

    archivo.close();
}


// ==================== LISTAR PRODUCTOS (stock < 15) ====================

void listarProductos(Producto p[50]) {
    cout << "\n -----  PRODUCTOS CON STOCK BAJO  -----\n" << endl;
    for (int i = 0; i < 50; i++) {
        if (p[i].stock < 15) {
            cout << "ID " << p[i].idProducto << " - " << p[i].nombre
                 << " --- " << p[i].stock << " unidades." << endl;
        }
    }
}

// ==================== COMENTARIOS POR FECHA ====================

void mostrarComentarios(Comentario c[50])
{
    string fechaFiltro;

    cout << "----- FILTRAR COMENTARIOS POR FECHA -----" << endl;
    cout << "Ingrese una fecha (yyyy-mm-dd): ";
    cin.ignore();
    getline(cin, fechaFiltro);

    cout << "\n----- COMENTARIOS DESDE " << fechaFiltro << " -----\n";

    for(int i = 0; i < 50; i++)
    {
        if(c[i].fecha >= fechaFiltro)
        {
            cout << "\nProducto: " << c[i].producto << endl;
            cout << "Usuario: " << c[i].usuario << endl;
            cout << "Comentario: " << c[i].comentario << endl;
            cout << "Fecha: " << c[i].fecha << endl;
            cout << "-----------------------------------------" << endl;
        }
    }
}

// ==================== LISTAR USUARIOS ====================

void listarUsuarios(Usuario u[5]) {
    cout << "\n-----  USUARIOS  -----\n" << endl;
    for (int i = 0; i < 5; i++) {
        cout << nombreToUpper(u[i].nombre) << " --- " << u[i].correoElectronico << endl;
    }
}

// ==================== UTILIDAD: MAYUSCULAS ====================

string nombreToUpper(string s) {
    for (int i = 0; i < (int)s.size(); i++)
        s[i] = toupper((unsigned char)s[i]);
    return s;
}

// ==================== CONTAR CARRITOS DE UN USUARIO ====================

int obtenerCarritosPendientes(int idUsuario)
{
    int count = 0;

    for(int i=0;i<totalCarritos;i++)
    {
        if(carritos[i].idUsuario == idUsuario &&
           carritos[i].pagado == 0)
        {
            count++;
        }
    }

    return count;
}

// ==================== AGREGAR AL CARRITO ====================

void agregarAlCarrito(Producto p[50], int idUsuario) {
    setlocale(LC_ALL, "spanish");

	int indiceCarrito = -1;
	int cantidadCarritos = obtenerCarritosPendientes(idUsuario);

	if(cantidadCarritos >= 2)
	{
	    cout << "Ya alcanzaste el maximo de 2 carritos." << endl;
	    return;
	}

	int opcion;

	cout << "\n1. Usar carrito existente";
	cout << "\n2. Crear carrito nuevo";
	cout << "\nOpcion: ";
	cin >> opcion;
	
	if(opcion == 2)
	{
	    if(obtenerCarritosPendientes(idUsuario) >= 2)
	    {
	        cout<<"Ya tiene 2 carritos."<<endl;
	        return;
	    }
	
	    carritos[totalCarritos].idCarrito = totalCarritos + 1;
	    carritos[totalCarritos].idUsuario = idUsuario;
	    carritos[totalCarritos].cantItems = 0;
	    carritos[totalCarritos].subtotal = 0;
	    carritos[totalCarritos].impuestos = 0;
	    carritos[totalCarritos].pagado = 0;
	
	    indiceCarrito = totalCarritos;
	    totalCarritos++;
	}
	
	else
	{
	    int idCarritoBuscar;
	
	    cout << "Ingrese ID del carrito: ";
	    cin >> idCarritoBuscar;
	
	    for(int i=0;i<totalCarritos;i++)
	    {
	        if(carritos[i].idCarrito == idCarritoBuscar &&
	           carritos[i].idUsuario == idUsuario)
	        {
	            indiceCarrito = i;
	            break;
	        }
	    }
	}

	if(indiceCarrito == -1)
	{
	    cout << "Carrito no encontrado." << endl;
	    return;
	}
	
    int id, cantidad, opc;

    do {
        cout << "\n ----- AGREGAR PRODUCTO AL CARRITO #"
             << carritos[indiceCarrito].idCarrito << " -----\n" << endl;
        cout << "Ingrese el ID del producto: ";
        cin >> id;

        int encontrado = 0;
        for (int i = 0; i < 50; i++) {
            if (p[i].idProducto == id) {
                encontrado = 1;
                cout << "Producto: " << p[i].nombre  << endl;
                cout << "Precio: $"  << p[i].precio   << endl;
                cout << "Stock disponible: " << p[i].stock << endl;
                cout << "Cantidad a comprar: ";
                cin >> cantidad;

                if (cantidad > 0 && cantidad <= p[i].stock) {
                    int cantItems = carritos[indiceCarrito].cantItems;
                    carritos[indiceCarrito].items[cantItems].producto = p[i];
                    carritos[indiceCarrito].items[cantItems].cantidad  = cantidad;
                    carritos[indiceCarrito].subtotal += p[i].precio * cantidad;
                    /////////////
                    carritos[indiceCarrito].cantItems++;
                    cout << "Producto agregado correctamente." << endl;
                } else {
                    cout << "Cantidad no valida o insuficiente en stock." << endl;
                }
                break;
            }
        }

        if (!encontrado)
            cout << "No se encontro un producto con ese ID." << endl;

        system("pause"); system("cls");
        cout << "\nDesea agregar otro producto?\n\n1. Si\n2. No\n\nOpcion: ";
        cin >> opc;
        system("cls");

    } while (opc == 1);

}

// ==================== LISTAR CARRITOS DEL USUARIO ====================

void listarCarritosUsuario(int idUsuario) {
    
}
