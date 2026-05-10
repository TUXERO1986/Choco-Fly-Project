#include <iostream>
#include "Color.h"
#include "Windows.h"
#include "GestionPantallas.h"
#include "AdminPantallas.h"


using namespace std;
using namespace ColorUI;
string usuario, correo, password;


void RegisterScreen(ControladorPrincipal* principal) {
    char modo;
    do {
        system("cls");
        ImprimirBordes(registro);
        gotoxy(0, 6);
        ColorUI::printGradient("\n\n\n\t\t\t\t\tIngrese el modo 1-Admin 2-Usuario 0- Salir", Register, false);
        modo = _getch();
        switch (modo) {
        case '1':Admin(principal); break;
        case '2':LoginScreen(principal); break;
        case '0': system("cls"); return; break;
        }
    } while (true);
}

void LoginScreen(ControladorPrincipal* principal) {
    system("cls");
    string u_nombre, u_correo, u_password;

    ColorUI::printGradient(login, Register, false);
	gotoxy(0, 6);
    ColorUI::printGradient("\n\n\n\t\t\t\tIngrese su Nombre de usuario", Paletas::Register, false);
    cout << "\t\t\t\t"; cin >> u_nombre;

    ColorUI::printGradient("\n\t\t\t\tIngrese su Correo", Paletas::Register, false);
    cout << "\t\t\t\t"; cin >> u_correo;

    ColorUI::printGradient("\n\t\t\t\tIngrese su Contrasena", Paletas::Register, false);
    cout << "\t\t\t\t"; cin >> u_password;

    cin.ignore(1000, '\n');
    system("cls");

    Usuario* userLogeado = principal->VerificarInicioSesion(u_nombre, u_correo, u_password);

    if (userLogeado != nullptr) {
        system("pause>0");
        GestionPantallas* userUI = new GestionPantallas(principal, userLogeado);
        userUI->Menuprincipal();
        delete userUI;
        //RegisterScreen(principal); 
    }
    else {
        system("pause>0");
        //RegisterScreen(principal);
    }
}
void Admin(ControladorPrincipal* principal) {
    system("cls");

    ColorUI::printGradient(admin, Paletas::Tux, false);
	gotoxy(0, 6);
    ColorUI::printGradient("\n\n\n\t\t\t\t\tIngrese Datos ADMIN", Paletas::Tux, false);
    cout << "\t\t\t\t\t"; cin >> usuario;
    ColorUI::printGradient("\n\t\t\t\t\tIngrese contrasena ADMIN", Paletas::Tux, false);
    cout << "\t\t\t\t\t"; cin >> password;
    system("cls");
    AdminPantallas* adminUI = new AdminPantallas(principal);
    adminUI->MenuPrincipalAdmin();
    delete adminUI; 
}

//ZONA DE ASCII ART
void creditos() {
    cout << BLINK;
    string Creditos = R"(
        >>========================================<<
        ||   _____              _ _ _             ||
        ||  / ____|            | (_) |            ||
        || | |     _ __ ___  __| |_| |_ ___  ___  ||
        || | |    | '__/ _ \/ _` | | __/ _ \/ __| ||
        || | |____| | |  __/ (_| | | || (_) \__ \ ||
        ||  \_____|_|  \___|\__,_|_|\__\___/|___/ ||
        >>========================================<<
    )";
    ColorUI::printGradient(Creditos, rosa, false);
    cout << RESET;

    string ryan = R"(
      Ryan Nima Muro
    [Programador C++ Backend]

            .--.
           |o_o |
           |:_/ |
          //   \ \
         (|     | )
        /'\_   _/`\
        \___)=(___/ 
    )";

    string gengis = R"(
      Gengis cam pizarro
    [Frontend Console App]

           ,_     _
           |\_,-~/
           / _  _ |    ,--.
          (  @  @ )   / ,-'
           \  _T_/-._( (
           /         `. \
          |         _  \ |
           \ \ ,  /      |
            || |-_\__   /
           ((_/`(____,-'
    )";

    string santiago = R"(
      Santiago Ceron Diaz
    [Code Reviewer]

               __         __
              /  \.-"""-./  \
              \    -   -    /
               |   o   o   |
               \  .-'''-.  /
                '-\__Y__/-'
                   `---`
    )";

    ColorUI::printMultilinesSideBySide(
        ryan, Tux,
        gengis, gege,
        santiago, TemaPrincipal
    );
    system("pause>0");
}

