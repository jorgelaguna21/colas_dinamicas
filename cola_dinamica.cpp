#include <iostream>
#include <string>
#include <stdexcept>

template<class T>
class LSLSE;

template<class T>
class node {
private:
    T data;
    node<T>* sig;
public:
    node() : sig(nullptr) {}
    friend class LSLSE<T>;
};

template<class T>
class LSLSE {
private:
    node<T>* frente; // Apunta al primer elemento (frente de la cola)
    node<T>* fondo;  // Apunta al último elemento (fondo de la cola)
public:
    LSLSE() : frente(nullptr), fondo(nullptr) {}
    bool vacia() const;
    void encolar(T elem);
    T desencolar();
    void imprimir() const;
    int contarSolicitudes() const; // Método para contar las solicitudes
};

template<class T>
void LSLSE<T>::imprimir() const {
    node<T>* aux = frente;
    while (aux != nullptr) {
        std::cout << aux->data << std::endl; // Se imprime cada solicitud en una nueva línea
        aux = aux->sig;
    }
}

template<class T>
bool LSLSE<T>::vacia() const {
    return frente == nullptr;
}

template<class T>
void LSLSE<T>::encolar(T elem) {
    node<T>* nuevo = new node<T>;
    nuevo->data = elem;
    nuevo->sig = nullptr;

    if (vacia()) {
        frente = nuevo; // Si la cola está vacía, el nuevo nodo es el frente
    } else {
        fondo->sig = nuevo; // Agregar el nuevo nodo al final
    }
    fondo = nuevo; // Actualizar el fondo
}

template<class T>
T LSLSE<T>::desencolar() {
    if (vacia()) {
        throw std::runtime_error("Cola vacía, no se puede desencolar.");
    }

    T valor = frente->data; // Obtener el dato del nodo frente
    node<T>* temp = frente; // Guardar el nodo frente para eliminarlo
    frente = frente->sig; // Mover el frente al siguiente nodo
    delete temp; // Eliminar el nodo que estaba al frente

    // Si la cola queda vacía, también actualizamos el fondo
    if (frente == nullptr) {
        fondo = nullptr;
    }

    return valor; // Retornar el valor desencolado
}

// Método para contar el número de solicitudes en la cola
template<class T>
int LSLSE<T>::contarSolicitudes() const {
    int contador = 0;
    node<T>* aux = frente;
    while (aux != nullptr) {
        contador++;
        aux = aux->sig;
    }
    return contador;
}

// Clase Solicitud
class Solicitud {
public:
    std::string nombre;
    std::string carrera;
    int materiasAprobadas;
    float promedio;

    // Constructor que recibe todos los parámetros
    Solicitud(std::string n, std::string c, int m, float p)
        : nombre(n), carrera(c), materiasAprobadas(m), promedio(p) {}

    // Constructor predeterminado
    Solicitud() : nombre(""), carrera(""), materiasAprobadas(0), promedio(0.0f) {}

    // Sobrecarga del operador de salida
    friend std::ostream& operator<<(std::ostream& os, const Solicitud& s) {
        os << "Nombre: " << s.nombre << "\n"
           << "Carrera: " << s.carrera << "\n"
           << "Materias Aprobadas: " << s.materiasAprobadas << "\n"
           << "Promedio: " << s.promedio;
        return os;
    }
};

int main() {
    LSLSE<Solicitud> colaSolicitudes;
    int opcion;

    do {
        std::cout << "\n  Menú de Opciones:\n\n";

        std::cout << "1. Dar de alta la solicitud de un alumno\n";
        std::cout << "2. Elaborar una constancia\n";
        std::cout << "3. Ver las solicitudes en cola\n";
        std::cout << "4. Salir\n";
        std::cout << "Elija una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                std::string nombre, carrera;
                int materiasAprobadas;
                float promedio;

                std::cout << "\n Alta de Alumnos:\n";
                std::cout << "*******\n";

                std::cout << "Ingrese el nombre del Alumno: ";
                std::cin.ignore(); // Limpiar el buffer
                std::getline(std::cin, nombre);
                std::cout << "Ingrese la carrera: ";
                std::getline(std::cin, carrera);
                std::cout << "Ingrese el total de materias aprobadas: ";
                std::cin >> materiasAprobadas;
                std::cout << "Ingrese el promedio: ";
                std::cin >> promedio;

                Solicitud nuevaSolicitud(nombre, carrera, materiasAprobadas, promedio);
                colaSolicitudes.encolar(nuevaSolicitud);
                std::cout << "\nLa solicitud de " << nombre << " esta en proceso." << std::endl;
                break;
            }
            case 2: {
                if (!colaSolicitudes.vacia()) {
                    Solicitud s = colaSolicitudes.desencolar();

                    std::cout << "\n Constancias:\n";
                    std::cout << "*******\n";
                    std::cout << "Elaborando constancia para:\n" << s << std::endl;
                    int solicitudesRestantes = colaSolicitudes.contarSolicitudes();
                    std::cout << "Solicitudes restantes por atender: " << solicitudesRestantes << std::endl;
                } else {
                    std::cout << "No hay solicitudes en la cola para atender." << std::endl;
                }
                break;
            }
            case 3: {
                int totalSolicitudes = colaSolicitudes.contarSolicitudes();
                if (totalSolicitudes == 0) {
                    std::cout << "\nNo hay ninguna solicitud en cola.\n"; // Mensaje con salto de línea
                } else {
                    std::cout << "Solicitudes en la cola: " << totalSolicitudes << std::endl;
                    colaSolicitudes.imprimir();
                }
                break;
            }
            case 4:
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}
