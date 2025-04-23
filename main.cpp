#include "aed.h"
#include <iostream>
using namespace std;

class ListaEnlazadaEnteros : public Lista<int>
{
};
class PilaPrincipal : public Pila<int>
{
};
class ColaEnteros : public Cola<int>
{
};

// Clase con lógica del promedio
class PilaConPromedio : public PilaPrincipal
{
private:
    int promedio = 0;

public:
    int calcularPromedio()
    {
        if (estaVacia())
            return 0;

        Pila<int> auxiliar;
        int suma = 0, contador = 0;

        while (!estaVacia())
        {
            int valor = tope();
            pop();
            suma += valor;
            contador++;
            auxiliar.push(valor);
        }

        while (!auxiliar.estaVacia())
        {
            push(auxiliar.tope());
            auxiliar.pop();
        }

        promedio = suma / contador;
        return promedio;
    }

    Lista<int> obtenerElementosFueraDeRango()
    {
        Lista<int> listaFuera;
        if (promedio == 0)
            calcularPromedio();

        float min = promedio * 0.90;
        float max = promedio * 1.10;

        Pila<int> auxiliar;

        while (!estaVacia())
        {
            int valor = tope();
            pop();

            if (valor < min || valor > max)
            {
                listaFuera.insertarFin(valor);
            }

            auxiliar.push(valor);
        }

        while (!auxiliar.estaVacia())
        {
            push(auxiliar.tope());
            auxiliar.pop();
        }

        return listaFuera;
    }

    void mostrarPila()
    {
        Pila<int> auxiliar;
        while (!estaVacia())
        {
            int valor = tope();
            cout << valor << " ";
            auxiliar.push(valor);
            pop();
        }
        cout << endl;
        while (!auxiliar.estaVacia())
        {
            push(auxiliar.tope());
            auxiliar.pop();
        }
    }

    void cargarEjemplo()
    {
        push(23);
        push(22);
        push(45);
        push(40);
        push(76);
        push(44);
        push(39);
        push(41);
        push(17);
    }

    int obtenerPromedio() const
    {
        return promedio;
    }
};
#include <fstream>
using namespace std;

class ConsignaDos : public Lista<int>
{
public:
    void cargarDesdeArchivo(const string &nombreArchivo)
    {
        ifstream archivo(nombreArchivo);
        if (!archivo)
        {
            cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
            return;
        }

        int numero;
        while (archivo >> numero)
        {
            insertarOrdenado(numero); // Usa el método heredado
        }

        archivo.close();
    }

    void mostrarLista()
    {
        mostrar(); // Método heredado de Lista<T>
    }

    void procesarListaYPasarAPilaYCola(const ConsignaDos &listaOriginal)
    { // Esto es una forma eficiente y segura de pasar un objeto como parámetro a una función.

        Pila<int> pilaPares;
        Cola<int> colaMenores10;

        Nodo<int> *actual = listaOriginal.obtenerCabeza();
        while (actual != nullptr)
        {
            if (actual->dato % 2 == 0)
            {
                pilaPares.push(actual->dato);
            }
            if (actual->dato < 10)
            {
                colaMenores10.encolar(actual->dato);
            }
            actual = actual->siguiente;
        }

        cout << "Lista original:" << endl;
        listaOriginal.mostrar();

        cout << "Pila con elementos pares:" << endl;
        pilaPares.mostrar();

        cout << "Cola con elementos < 10:" << endl;
        colaMenores10.mostrar();
    }
};

int main()
{
    PilaConPromedio miPila;
    ListaEnlazadaEnteros listaFuera;
    int opcion;

    do
    {
        cout << "\n=== MENÚ DE OPCIONES ===" << endl;
        cout << "1. Cargar pila y calcular promedio" << endl;
        cout << "2. Obtener lista con elementos fuera del ±10%" << endl;
        cout << "3. Mostrar pila actual" << endl;
        cout << "4. Cargar Pila Pares" << endl;
        cout << "6. Cargar Cola < 10" << endl;

        cout << "10. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            miPila = PilaConPromedio(); // Reiniciar pila();
            miPila.cargarEjemplo();
            cout << "Pila cargada." << endl;
            cout << "Promedio: " << miPila.calcularPromedio() << endl;
            break;

        case 2:
            if (miPila.estaVacia())
            {
                cout << "Primero tenés que cargar la pila (opción 1)." << endl;
            }
            else
            {
                cout << "Elementos fuera del ±10% del promedio:" << endl;
                miPila.obtenerElementosFueraDeRango().mostrar();
            }
            break;

        case 3:
            cout << "Pila actual:" << endl;
            miPila.mostrarPila();
            break;

        case 4:
        {
            ConsignaDos listaOrdenada;
            listaOrdenada.cargarDesdeArchivo("archivo.txt");
            cout << "Lista ordenada cargada desde el archivo:" << endl;
            listaOrdenada.mostrarLista();
            break;
        }
        case 5:
        {
            ConsignaDos lista;
            lista.cargarDesdeArchivo("archivo.txt");
            lista.procesarListaYPasarAPilaYCola(lista);
            break;
        }

        break;

        default:
            cout << "Saliendo del Sistema.." << endl;
        }
    } while (opcion != 10);

    return 0;
}
