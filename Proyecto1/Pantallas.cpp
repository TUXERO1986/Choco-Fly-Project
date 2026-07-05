#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <iostream>
    #include <unistd.h> 
#endif
#include "AdminPantallas.h"
#include "AnimacionConsola.h"


using namespace std;
using namespace ColorUI;
string usuario, correo, password;


void RegisterScreen(ControladorPrincipal* principal) {
    static bool bienvenida_mostrada = false;
    if (!bienvenida_mostrada) {
        AnimacionConsola::CieloAnimado(3500);
        bienvenida_mostrada = true;
    }
    char modo;
    do {
        LimpiarConsola();
        
        #ifndef _WIN32
        std::cout << "\e[8;40;120t";
        #endif
        
        ColorUI::printGradient(registro, Register, false);
        gotoxy(0, 6);
        ColorUI::printGradient("\n\n\n\t\t\t\t\tIngrese el modo: \n", Register, false);
        ColorUI::printGradient("\t\t\t\t\t\t[1] Admin ", Register, false);
        ColorUI::printGradient("\t\t\t\t\t\t[2] Usuario", Register, false);
        ColorUI::printGradient("\t\t\t\t\t\t[0] Salir", Register, false); 

        modo = _getch();
        switch (modo) {
        case '1': AnimacionConsola::TransicionAvion(); Admin(principal); break;
        case '2': AnimacionConsola::TransicionAvion(); LoginScreen(principal); break; 
        case '0': LimpiarConsola(); exit(0); 
        }
    } while (true);
}

void LoginScreen(ControladorPrincipal* principal) {
string u_nombre, u_correo, u_password;
    Usuario* userLogeado = nullptr;
    
  
    do {
        LimpiarConsola();
        ColorUI::printGradient(login, Register, false); 
        gotoxy(0, 6);

        ColorUI::printGradient("\n\n\n\t\t\t\tIngrese su Nombre de usuario", Register, false);
        cout << "\t\t\t\t"; cin >> ws; getline(cin,u_nombre);

        ColorUI::printGradient("\n\t\t\t\tIngrese su Correo", Register, false);
        cout << "\t\t\t\t"; cin >> u_correo;

        ColorUI::printGradient("\n\t\t\t\tIngrese su Contrasena", Register, false);
        cout << "\t\t\t\t"; cin >> u_password; 
        
        userLogeado = principal->VerificarInicioSesion(u_nombre, u_correo, u_password);
        
        if (userLogeado == nullptr) {
             ColorUI::printGradient("\nCredenciales incorrectas. Presione Enter para intentar de nuevo.", Alerta, false);
             cin.ignore(1000, '\n'); 
             cin.get(); 
        }
    } while (userLogeado == nullptr);


    pausarConsola();
    LimpiarConsola();
    AnimacionConsola::AvionVolando(2000);
    GestionPantallas* userUI = new GestionPantallas(principal, userLogeado);
    userUI->IniciarMotorNavegacion(); 
    

    delete userUI;
}
void Admin(ControladorPrincipal* principal) {
    LimpiarConsola();
    ColorUI::printGradient(admin, Tux, false);
    gotoxy(0, 6);
    ColorUI::printGradient("\n\n\n\t\t\t\t\tIngrese Datos ADMIN", Tux, false);
    cout << "\t\t\t\t\t"; cin >> usuario;
    ColorUI::printGradient("\n\t\t\t\t\tIngrese contrasena ADMIN", Tux, false);
    cout << "\t\t\t\t\t"; cin >> password;

    if (usuario != "admin" || password != "chocofly2026") {
        ColorUI::printGradient("\n\n\t\t\t\t\t[!] ACCESO DENEGADO. Credenciales invalidas.", Alerta, false);
        pausarConsola();
        return; 
    }

    LimpiarConsola();
    principal->getControladorRegistros()->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Inicio de sesion ADMIN");
    AnimacionConsola::AvionConEstela(2000);
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
    pausarConsola();
}

