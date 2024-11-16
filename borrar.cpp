#include <iostream>
#include <iomanip>

using namespace std;

// Estructura de nodo del árbol binario
struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int v) : valor(v), izquierdo(nullptr), derecho(nullptr) {}
};

// Función para insertar un nodo en el árbol
Nodo* insertar(Nodo* nodo, int valor) {
    if (nodo == nullptr) {
        return new Nodo(valor);
    }

    if (valor < nodo->valor) {
        nodo->izquierdo = insertar(nodo->izquierdo, valor);
    } else if (valor > nodo->valor) {
        nodo->derecho = insertar(nodo->derecho, valor);
    }

    return nodo;
}

// Encuentra el nodo con el valor mínimo en un subárbol
Nodo* encontrarMinimo(Nodo* nodo) {
    while (nodo && nodo->izquierdo != nullptr) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

// Función para eliminar un nodo en el árbol binario
Nodo* eliminarNodo(Nodo* raiz, int valor) {
    if (raiz == nullptr) {
        cout << "El valor " << valor << " no se encuentra en el árbol.\n";
        return raiz;
    }

    if (valor < raiz->valor) {
        raiz->izquierdo = eliminarNodo(raiz->izquierdo, valor);
    } else if (valor > raiz->valor) {
        raiz->derecho = eliminarNodo(raiz->derecho, valor);
    } else {
        // Caso 1: Nodo sin hijos
        if (raiz->izquierdo == nullptr && raiz->derecho == nullptr) {
            cout << "Eliminando nodo sin hijos: " << raiz->valor << "\n";
            delete raiz;
            return nullptr;
        }
        // Caso 2: Nodo con un solo hijo
        else if (raiz->izquierdo == nullptr || raiz->derecho == nullptr) {
            cout << "Eliminando nodo con un hijo: " << raiz->valor << "\n";
            Nodo* temp = (raiz->izquierdo != nullptr) ? raiz->izquierdo : raiz->derecho;
            delete raiz;
            return temp;
        }
        // Caso 3: Nodo con dos hijos
        else {
            cout << "Eliminando nodo con dos hijos: " << raiz->valor << "\n";
            Nodo* temp = encontrarMinimo(raiz->derecho);
            raiz->valor = temp->valor;  // Reemplazar valor con el sucesor en orden
            raiz->derecho = eliminarNodo(raiz->derecho, temp->valor);  // Eliminar el nodo duplicado
        }
    }

    return raiz;
}

// Función para imprimir el árbol de forma jerárquica
void imprimirArbol(Nodo* nodo, int espacio = 0, int incremento = 5) {
    if (nodo == nullptr) return;

    // Incrementar la cantidad de espacio entre niveles
    espacio += incremento;

    // Procesar primero el subárbol derecho
    imprimirArbol(nodo->derecho, espacio);

    // Imprimir el nodo actual después de los espacios
    cout << endl;
    cout << setw(espacio) << nodo->valor << endl;

    // Procesar el subárbol izquierdo
    imprimirArbol(nodo->izquierdo, espacio);
}

// Función para crear un árbol binario predefinido de nivel 4
Nodo* crearArbolBase() {
    Nodo* raiz = new Nodo(10);
    insertar(raiz, 5);
    insertar(raiz, 3);
    insertar(raiz, 7);
    insertar(raiz, 15);
    insertar(raiz, 13);
    insertar(raiz, 17);
    insertar(raiz, 1);
    insertar(raiz, 4);
    insertar(raiz, 6);
    insertar(raiz, 8);
    insertar(raiz, 12);
    insertar(raiz, 14);
    insertar(raiz, 16);
    insertar(raiz, 18);
    return raiz;
}

// Función para mostrar el menú de opciones
void mostrarMenu() {
    cout << "\n--- Menú ---\n";
    cout << "1. Insertar un valor en el árbol\n";
    cout << "2. Eliminar un valor del árbol\n";
    cout << "3. Mostrar el árbol\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    Nodo* raiz = crearArbolBase();
    int opcion, valor;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese un valor para insertar en el árbol: ";
                cin >> valor;
                raiz = insertar(raiz, valor);
                break;
            case 2:
                cout << "Ingrese un valor para eliminar del árbol: ";
                cin >> valor;
                raiz = eliminarNodo(raiz, valor);
                break;
            case 3:
                cout << "Árbol binario:\n";
                imprimirArbol(raiz);
                cout << endl;
                break;
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida.\n";
                break;
        }
    } while (opcion != 4);

    return 0;
}
