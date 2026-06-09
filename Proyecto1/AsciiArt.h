#pragma once
#ifdef _WIN32
    // Todo lo que esté aquí SOLO se compilará en las PCs de tus amigos (Windows)
    #include <windows.h>
    #include <conio.h>
#else
    // Todo lo que esté aquí SOLO se compilará en tu PC (Linux/Mac)
    #include <iostream>
    #include <unistd.h> 
#endif
#include "Color.h"
extern std::string chocofly, chocoadmin, admin, registro, login, quepaso,PanelControlADM,reportesADM,mantenimiento, eliminacion,datos;


void ImprimirBordes(const std::string& arteAscii);

void gotoxy(int,int);