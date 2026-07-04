#pragma once
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <iostream>
    #include <unistd.h> 
#endif
#include "Color.h"
#include <vector>
#include <string>
extern std::string chocofly, admin, registro, login, PanelControlADM, reportesADM, mantenimiento, eliminacion, datos;
extern std::string spriteAvion, spriteHotel, spritePaquete;

//  animacion
extern std::vector<std::string> DRONE_TEMPLATE, PROP_FRAMES;
extern std::vector<std::string> BANNER_CHOCOFLY, BANNER_REGISTRO, BANNER_ADMIN, BANNER_ACCESO;
extern std::vector<std::string> SPRITE_NUBE;

void gotoxy(int,int);