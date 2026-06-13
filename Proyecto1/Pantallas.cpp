#ifdef _WIN32
    // Todo lo que esté aquí SOLO se compilará en las PCs de tus amigos (Windows)
    #include <windows.h>
    #include <conio.h>
#else
    // Todo lo que esté aquí SOLO se compilará en tu PC (Linux/Mac)
    #include <iostream>
    #include <unistd.h> 
#endif
#include "AdminPantallas.h"


using namespace std;
using namespace ColorUI;
string usuario, correo, password;


void RegisterScreen(ControladorPrincipal* principal) {
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
        case '1': Admin(principal); break;
        case '2': LoginScreen(principal); break; // Llama al login
        case '0': LimpiarConsola();; exit(0); // Cierra la consola y el programa
        }
    } while (true); // Siempre vuelve a pintar el menú inicial si Admin o Login terminan
}

void LoginScreen(ControladorPrincipal* principal) {
string u_nombre, u_correo, u_password;
    Usuario* userLogeado = nullptr; // Inicializa el puntero
    
    // Bucle para intentar loguearse (o salir)
    do {
        LimpiarConsola();
        ColorUI::printGradient(login, Register, false); // Imprime el ASCII
        gotoxy(0, 6);
        
        // NO poner LimpiarConsola() aquí, o borrarás el ASCII de arriba

        ColorUI::printGradient("\n\n\n\t\t\t\tIngrese su Nombre de usuario", Register, false);
        cout << "\t\t\t\t"; getline(cin,u_nombre);

        ColorUI::printGradient("\n\t\t\t\tIngrese su Correo", Register, false);
        cout << "\t\t\t\t"; cin >> u_correo;

        ColorUI::printGradient("\n\t\t\t\tIngrese su Contrasena", Register, false);
        cout << "\t\t\t\t"; cin >> u_password; // <-- AQUÍ DEBE IR EL CIN
        
        // AHORA SÍ verificamos con los tres datos ya ingresados
        userLogeado = principal->VerificarInicioSesion(u_nombre, u_correo, u_password);
        
        if (userLogeado == nullptr) {
             ColorUI::printGradient("\nCredenciales incorrectas. Presione Enter para intentar de nuevo.", Alerta, false);
             cin.ignore(1000, '\n'); // Limpia basurita del buffer por si acaso
             cin.get(); // Espera el Enter
        }
    } while (userLogeado == nullptr);

    // Si sale del bucle, el login fue exitoso
    pausarConsola();
    GestionPantallas* userUI = new GestionPantallas(principal, userLogeado);
    userUI->Menuprincipal(); // Se queda atrapado aquí hasta que cierre sesión
    
    // Instrucción 2: Uso correcto de delete tras salir del ciclo de vida del objeto
    delete userUI;
}
void Admin(ControladorPrincipal* principal) {
    LimpiarConsola();

    ColorUI::printGradient(admin, 
        Tux, false);
	gotoxy(0, 6);
    ColorUI::printGradient("\n\n\n\t\t\t\t\tIngrese Datos ADMIN", Tux, false);
    cout << "\t\t\t\t\t"; cin >> usuario;
    ColorUI::printGradient("\n\t\t\t\t\tIngrese contrasena ADMIN", Tux, false);
    cout << "\t\t\t\t\t"; cin >> password;
    LimpiarConsola();
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

