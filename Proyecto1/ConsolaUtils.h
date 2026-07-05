#pragma once

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <iostream> 
    #include <cstdlib>

    inline int _getch() {
        struct termios oldt, newt;
        int ch;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;

        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        
        ch = getchar();
        
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif 

inline void pausarConsola() {
    std::cout << "\n\tPresione cualquier tecla para continuar...";
    _getch(); 
}

inline void LimpiarConsola() {
#ifdef _WIN32
    system("cls");   
#else
    system("clear"); 
#endif
}

#include <string>
#include <functional>
#include <iostream>
#include "Lista.h"
#include "Color.h"

template <typename T>
inline void MostrarResultadosPaginados(Lista<T*>* listaOriginal, const std::string& titulo, std::function<bool(T*)> filtro, std::function<void(T*, int)> mostrarItem) {
    int* indicesFiltrados = new int[listaOriginal->longitud()];
    int totalFiltrados = 0;
    
    for (int i = 0; i < listaOriginal->longitud(); i++) {
        T* aux = listaOriginal->obtenerPos(i);
        if (filtro(aux)) {
            indicesFiltrados[totalFiltrados++] = i;
        }
    }
    
    if (totalFiltrados == 0) {
        ColorUI::Alertas::MostrarInfo("No se encontraron resultados para la busqueda.");
        pausarConsola();
        delete[] indicesFiltrados;
        return;
    }
    
    int itemsPorPagina = 3;
    int paginasTotales = (totalFiltrados + itemsPorPagina - 1) / itemsPorPagina;
    int paginaActual = 1;
    char opcion = ' ';
    
    do {
        LimpiarConsola();
        ColorUI::printGradient("\t=== " + titulo + " (Pag " + std::to_string(paginaActual) + "/" + std::to_string(paginasTotales) + ") ===", ColorUI::Paletas::TemaPrincipal, false);
        std::cout << "\n";
        
        int inicio = (paginaActual - 1) * itemsPorPagina;
        int fin = (inicio + itemsPorPagina < totalFiltrados) ? inicio + itemsPorPagina : totalFiltrados;
        
        for (int i = inicio; i < fin; i++) {
            int indiceReal = indicesFiltrados[i];
            T* aux = listaOriginal->obtenerPos(indiceReal);
            mostrarItem(aux, indiceReal);
            std::cout << "\n";
        }
        
        ColorUI::printGradient("\n\t[A] Anterior  |  [S] Siguiente  |  [ENTER / Q] Continuar / Salir", ColorUI::Paletas::azul, false);
        std::cout << "\n\t> ";
        opcion = _getch();
        
        if ((opcion == 's' || opcion == 'S') && paginaActual < paginasTotales) paginaActual++;
        else if ((opcion == 'a' || opcion == 'A') && paginaActual > 1) paginaActual--;
        else if (opcion != 's' && opcion != 'S' && opcion != 'a' && opcion != 'A') {
            if (opcion >= '0' && opcion <= '9') {
                std::cin.putback(opcion);
            }
            break;
        }
    } while (opcion != 'q' && opcion != 'Q');
    
    delete[] indicesFiltrados;
}

