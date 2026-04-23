#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Windows.h"

/**
 * ============================================================================
 * LIBRERIA DE INTERFAZ DE USUARIO (UI) - EXTENSION VISUAL
 * ============================================================================
 * Nota: Este modulo es opcional y puramente decorativo (Mejora de UX).
 * No interfiere ni modifica la logica de negocio o los algoritmos principales.
 * * Implementacion basada en el uso de Secuencias de Escape ANSI (True Color 24-bit)
 * y la interpolacion lineal (LERP) para el calculo de degradados RGB.
 * * Fuentes y Documentacion Oficial consultada:
 * 1. Microsoft Docs - Console Virtual Terminal Sequences:
 * https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
 * * 2. Estandar ANSI / ISO-6429 (Colores de terminal de 24 bits):
 * https://en.wikipedia.org/wiki/ANSI_escape_code#24-bit
 * ============================================================================
 */

//definicion de funciones:
void PruebaColor();
void Menuprincipal();


// Espacio de nombres para encapsular toda la funcionalidad relacionada con la UI de colores
namespace ColorUI {

    struct RGB {
        int r, g, b;
    };

    // Función auxiliar para convertir Hexadecimal a RGB
    inline RGB hexToRGB(const std::string& hex) {
        using namespace std; 

        size_t offset = (hex[0] == '#') ? 1 : 0;
        return {
            stoi(hex.substr(offset, 2), nullptr, 16),
            stoi(hex.substr(offset + 2, 2), nullptr, 16),
            stoi(hex.substr(offset + 4, 2), nullptr, 16)
        };
    }

    // Función principal para imprimir degradados
    inline void printGradient(const std::string& text, const std::vector<std::string>& hexColors, bool isBackground = false, bool newLine = true) {
        using namespace std; // Código interior limpio

        if (hexColors.empty()) {
            cout << text << (newLine ? "\n" : "");
            return;
        }

        int n = text.length();
        int numSections = hexColors.size() - 1;
        float charsPerSection = (float)n / (numSections > 0 ? numSections : 1);
        string mode = isBackground ? "48" : "38";

        for (int i = 0; i < n; ++i) {
            int section = (numSections > 0) ? i / charsPerSection : 0;
            if (section >= numSections && numSections > 0) section = numSections - 1;

            float localFactor = (numSections > 0) ? (i - (section * charsPerSection)) / charsPerSection : 0;

            RGB start = hexToRGB(hexColors[section]);
            RGB end = hexToRGB(hexColors[numSections > 0 ? section + 1 : section]);

            int r = static_cast<int>(start.r + (end.r - start.r) * localFactor);
            int g = static_cast<int>(start.g + (end.g - start.g) * localFactor);
            int b = static_cast<int>(start.b + (end.b - start.b) * localFactor);

            cout << "\033[" << mode << ";2;" << r << ";" << g << ";" << b << "m" << text[i];
        }

        // Reseteo suave para no arruinar el fondo global
        string resetMode = isBackground ? "49" : "39";
        cout << "\033[" << resetMode << "m" << (newLine ? "\n" : "");
    }

    // Función para pintar toda la pantalla de un color
    inline void setBackgroundColor(const std::string& hex) {
        using namespace std;

        RGB color = hexToRGB(hex);

        cout << "\033[48;2;" << color.r << ";" << color.g << ";" << color.b << "m";

        cout << "\033[2J\033[H";
    }

    inline void resetConsole() {
        using namespace std;

        cout << "\033[0m\033[2J\033[H";
    }

    /*
    ============================================================================
	PALETAS DE COLORES PREDEFINIDAS 
	============================================================================
    */

    namespace Paletas {
        const std::vector<std::string> TemaPrincipal = { "#4facfe", "#00f2fe" };
        const std::vector<std::string> Alerta = { "#ff416c", "#ff4b2b" };
        const std::vector<std::string> Exito = { "#11998e", "#38ef7d" };
        const std::vector<std::string> gege = { "#00F719", "#15DE1C", "#1EC51E", "#22AD1F" };
        const std::vector<std::string> femboy = { "#E727F5","#D028DC","#B928C4","#A327AC" };
    }

    namespace Estilo {
        const std::string BOLD = "\033[1m";
        const std::string ITALIC = "\033[3m";
        const std::string UNDERLINE = "\033[4m";
        const std::string BLINK = "\033[5m";
        const std::string REVERSE = "\033[7m";
        const std::string RESET = "\033[0m";
    }

    using namespace Estilo;
    using namespace Paletas;
} 
