#ifndef AED_H
#define AED_H

#include <iostream>
using namespace std;

// Nodo genérico
template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;

    Nodo(T val) : dato(val), siguiente(nullptr) {}
};

// Lista genérica enlazada simple
template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;

public:
    Lista() : cabeza(nullptr) {}

    ~Lista() {
        while (!estaVacia()) {
            eliminarInicio();
        }
    }

    bool estaVacia() const {
        return cabeza == nullptr;
    }

    void insertarInicio(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    void insertarFin(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (estaVacia()) {
            cabeza = nuevo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

    void eliminarInicio() {
        if (!estaVacia()) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    T obtenerInicio() const {
        if (!estaVacia()) {
            return cabeza->dato;
        }
        throw runtime_error("La lista está vacía");
    }

    void mostrar() const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->dato << " -> ";
            actual = actual->siguiente;
        }
        cout << "NULL" << endl;
    }
    void insertarOrdenado(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);

        if (estaVacia() || valor < cabeza->dato) {
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
            return;
        }

        Nodo<T>* actual = cabeza;
        while (actual->siguiente != nullptr && actual->siguiente->dato < valor) {
            actual = actual->siguiente;
        }

        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
    Nodo<T>* obtenerCabeza() const {
        return cabeza; // se crea para poder recorrer desde afuera 
    }

    

};

// Pila basada en lista
template <typename T>
class Pila {
private:
    Lista<T> lista;

public:
    void push(T valor) {
        lista.insertarInicio(valor);
    }

    void pop() {
        if (!estaVacia()) {
            lista.eliminarInicio();
        } else {
            cout << "La pila está vacía." << endl;
        }
    }

    T tope() const {
        return lista.obtenerInicio();
    }

    bool estaVacia() const {
        return lista.estaVacia();
    }

    void mostrar() const {
        cout << "Pila (tope primero): ";
        lista.mostrar();
    }
};

// Cola basada en lista
template <typename T>
class Cola {
private:
    Lista<T> lista;

public:
    void encolar(T valor) {
        lista.insertarFin(valor);
    }

    void desencolar() {
        if (!estaVacia()) {
            lista.eliminarInicio();
        } else {
            cout << "La cola está vacía." << endl;
        }
    }

    T frente() const {
        return lista.obtenerInicio();
    }

    bool estaVacia() const {
        return lista.estaVacia();
    }

    void mostrar() const {
        cout << "Cola (frente primero): ";
        lista.mostrar();
    }
};

#endif // AED_H
