#pragma once
#include "AsciiArt.h"
#include "ConsolaUtils.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>

#ifndef _WIN32
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
inline int _kbhit_linux() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}
#define _kbhit _kbhit_linux
#endif

namespace ColorUI {
    namespace AnimacionesUI {

        struct CursorGuard {
            CursorGuard() {
                std::cout << "\033[?25l" << std::flush;
            }
            ~CursorGuard() {
                std::cout << "\033[?25h" << std::flush;
            }
        };

        class AnimacionConsola {
        private:
            static void borrarSprite(int x, int y, const std::vector<std::string>& sprite) {
                for (size_t i = 0; i < sprite.size(); ++i) {
                    if (y + (int)i >= 0) {
                        gotoxy(x, y + (int)i);
                        std::cout << std::string(sprite[i].length(), ' ');
                    }
                }
            }

            
            static void dibujarSprite(int x, int y, const std::vector<std::string>& sprite, const std::vector<std::string>& paleta, bool transparent_spaces = true) {
                for (size_t i = 0; i < sprite.size(); ++i) {
                    if (y + (int)i >= 0) {
                        gotoxy(x, y + (int)i);
                        if (!transparent_spaces) {
                            ColorUI::printGradient(sprite[i], paleta, false, false);
                        } else {
                            ColorUI::printGradient(sprite[i], paleta, false, false);
                        }
                    }
                }
            }

            static void drawToCanvas(std::vector<std::string>& canvas, std::vector<std::vector<std::string>>& color_canvas, int x, int y, const std::vector<std::string>& sprite, const std::vector<std::string>& paleta, bool transparent_spaces = true) {
                int height = (int)canvas.size();
                if (height == 0) return;
                int width = (int)canvas[0].size();

                for (size_t r = 0; r < sprite.size(); ++r) {
                    int canvas_r = y + (int)r;
                    if (canvas_r < 0 || canvas_r >= height) continue;

                    int n = (int)sprite[r].length();
                    int numSections = (int)paleta.size() - 1;
                    float charsPerSection = (float)n / (numSections > 0 ? numSections : 1);

                    for (int c = 0; c < n; ++c) {
                        int canvas_c = x + c;
                        if (canvas_c < 0 || canvas_c >= width) continue;

                        char ch = sprite[r][c];
                        if (!transparent_spaces || ch != ' ') {
                            canvas[canvas_r][canvas_c] = ch;

                            if (!paleta.empty()) {
                                int section = (numSections > 0) ? (int)(c / (charsPerSection > 0 ? charsPerSection : 1)) : 0;
                                if (section >= numSections && numSections > 0) section = numSections - 1;
                                float localFactor = (numSections > 0) ? (c - (section * charsPerSection)) / (charsPerSection > 0 ? charsPerSection : 1) : 0;
                                ColorUI::RGB start = ColorUI::hexToRGB(paleta[section]);
                                ColorUI::RGB end = ColorUI::hexToRGB(paleta[numSections > 0 ? section + 1 : section]);
                                int rv = static_cast<int>(start.r + (end.r - start.r) * localFactor);
                                int gv = static_cast<int>(start.g + (end.g - start.g) * localFactor);
                                int bv = static_cast<int>(start.b + (end.b - start.b) * localFactor);
                                color_canvas[canvas_r][canvas_c] = "\033[38;2;" + std::to_string(rv) + ";" + std::to_string(gv) + ";" + std::to_string(bv) + "m";
                            } else {
                                color_canvas[canvas_r][canvas_c] = "\033[0m";
                            }
                        }
                    }
                }
            }

            static void renderCanvas(const std::vector<std::string>& canvas, const std::vector<std::vector<std::string>>& color_canvas) {
                gotoxy(0, 0);
                std::string frame_buffer;
                frame_buffer.reserve(canvas.size() * canvas[0].size() * 20);
                std::string current_color = "";

                for (size_t r = 0; r < canvas.size(); ++r) {
                    for (size_t c = 0; c < canvas[r].size(); ++c) {
                        const std::string& cell_color = color_canvas[r][c];
                        if (cell_color != current_color) {
                            frame_buffer += cell_color;
                            current_color = cell_color;
                        }
                        frame_buffer += canvas[r][c];
                    }
                    if (r < canvas.size() - 1) {
                        frame_buffer += "\n";
                    }
                }
                frame_buffer += "\033[0m";
                std::cout << frame_buffer << std::flush;
            }

        public:
            static void AvionVolando(int duracion_ms = 3000) {
                CursorGuard cursorGuard;
                LimpiarConsola();
                const int WIDTH = 100;
                const int HEIGHT = 20;
                int frames = duracion_ms / 50;

                for (int f = 0; f < frames; ++f) {
                    if (_kbhit()) {
                        char ch = _getch();
                        break;
                    }

                    std::vector<std::string> canvas(HEIGHT, std::string(WIDTH, ' '));
                    std::vector<std::vector<std::string>> color_canvas(HEIGHT, std::vector<std::string>(WIDTH, "\033[0m"));

                    int x = 5 + (f * 70) / (frames > 0 ? frames : 1);
                    int y = 5 + (int)round(3.0 * sin(f * 0.2));

                    std::vector<std::string> drone_actual = DRONE_TEMPLATE;
                    drone_actual[2] = PROP_FRAMES[(f / 2) % PROP_FRAMES.size()];

                    drawToCanvas(canvas, color_canvas, x, y, drone_actual, ColorUI::Paletas::TemaPrincipal, true);
                    renderCanvas(canvas, color_canvas);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
                LimpiarConsola();
            }

            static void AvionConEstela(int duracion_ms = 3000) {
                CursorGuard cursorGuard;
                LimpiarConsola();
                const int WIDTH = 100;
                const int HEIGHT = 20;
                int frames = duracion_ms / 50;
                std::vector<std::string> estela = { " .--. ", " ~~~  ", " --   " };

                for (int f = 0; f < frames; ++f) {
                    if (_kbhit()) {
                        char ch = _getch();
                        break;
                    }

                    std::vector<std::string> canvas(HEIGHT, std::string(WIDTH, ' '));
                    std::vector<std::vector<std::string>> color_canvas(HEIGHT, std::vector<std::string>(WIDTH, "\033[0m"));

                    int x = 5 + (f * 70) / (frames > 0 ? frames : 1);
                    int y = 8 + (int)round(2.0 * cos(f * 0.2));

                    if (x - 6 >= 0) {
                        drawToCanvas(canvas, color_canvas, x - 6, y + 2, {estela[f % estela.size()]}, ColorUI::Paletas::Register, true);
                    }

                    std::vector<std::string> drone_actual = DRONE_TEMPLATE;
                    drone_actual[2] = PROP_FRAMES[(f / 2) % PROP_FRAMES.size()];

                    drawToCanvas(canvas, color_canvas, x, y, drone_actual, ColorUI::Paletas::gege, true);
                    renderCanvas(canvas, color_canvas);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
                LimpiarConsola();
            }

            static void TransicionAvion() {
                CursorGuard cursorGuard;
                int frames = 14;
                int old_x = 0, y = 12;

                for (int f = 0; f <= frames; ++f) {
                    int x = (f * 88) / frames;
                    
                    if (f > 0 && x != old_x) {
                        int wipe_width = x - old_x + 6;
                        std::string espacios(wipe_width, ' ');
                        for (int r = 0; r <= 26; ++r) {
                            if (r < y || r >= y + (int)DRONE_TEMPLATE.size()) {
                                gotoxy(old_x, r);
                                std::cout << espacios;
                            } else {
                                gotoxy(old_x, r);
                                std::cout << std::string(x - old_x + 4, ' ');
                            }
                        }
                    }

                    if (f < frames) {
                        std::vector<std::string> drone_actual = DRONE_TEMPLATE;
                        drone_actual[2] = PROP_FRAMES[f % PROP_FRAMES.size()];
                        dibujarSprite(x, y, drone_actual, ColorUI::Paletas::rosa);
                    }
                    old_x = x;

                    std::cout << std::flush;
                    std::this_thread::sleep_for(std::chrono::milliseconds(15));
                }
                LimpiarConsola();
            }

            static void CieloAnimado(int duracion_ms = 4000) {
                CursorGuard cursorGuard;
                LimpiarConsola();
                const int WIDTH = 100;
                const int HEIGHT = 26;
                int frames = duracion_ms / 50;

                for (int f = 0; f < frames; ++f) {
                    if (_kbhit()) {
                        char ch = _getch();
                        break;
                    }

                    std::vector<std::string> canvas(HEIGHT, std::string(WIDTH, ' '));
                    std::vector<std::vector<std::string>> color_canvas(HEIGHT, std::vector<std::string>(WIDTH, "\033[0m"));

                    int banner_x = 22, banner_y = 2;
                    drawToCanvas(canvas, color_canvas, banner_x, banner_y, BANNER_CHOCOFLY, ColorUI::Paletas::TemaPrincipal, false);

                    drawToCanvas(canvas, color_canvas, 5, 3, SPRITE_NUBE, ColorUI::Paletas::azul, true);
                    drawToCanvas(canvas, color_canvas, 70, 5, SPRITE_NUBE, ColorUI::Paletas::azul, true);
                    drawToCanvas(canvas, color_canvas, 40, 18, SPRITE_NUBE, ColorUI::Paletas::azul, true);

                    std::string texto_cont = " [ PRESIONA CUALQUIER TECLA PARA CONTINUAR ] ";
                    drawToCanvas(canvas, color_canvas, 26, 23, {texto_cont}, ColorUI::Paletas::dato, true);

                    int x1 = 5 + (int)round(15.0 * sin(f * 0.1));
                    int y1 = 8 + (int)round(2.0 * cos(f * 0.15));

                    int x2 = 65 - (int)round(15.0 * sin(f * 0.1));
                    int y2 = 14 + (int)round(2.0 * sin(f * 0.15));

                    std::vector<std::string> drone_actual = DRONE_TEMPLATE;
                    drone_actual[2] = PROP_FRAMES[(f / 2) % PROP_FRAMES.size()];

                    drawToCanvas(canvas, color_canvas, x1, y1, drone_actual, ColorUI::Paletas::TemaPrincipal, true);
                    drawToCanvas(canvas, color_canvas, x2, y2, drone_actual, ColorUI::Paletas::gege, true);

                    renderCanvas(canvas, color_canvas);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
                LimpiarConsola();
            }

            static void BarraProgresoAvion(const std::string& texto, int duracion_ms = 1500, const std::string& sangria = "\t\t\t") {
                CursorGuard cursorGuard;
                int pasos = 20;
                int ms_por_paso = duracion_ms / pasos;
                if (ms_por_paso < 20) ms_por_paso = 20;

                std::cout << "\n";
                for (int i = 0; i <= pasos; ++i) {
                    int porcentaje = (i * 100) / pasos;
                    int chars_llenos = (i * 15) / pasos;
                    std::string barra = "[" + std::string(chars_llenos, '=') + ">" + std::string(15 - chars_llenos, ' ') + "]";
                    std::string frame = "\r" + sangria + barra + " " + std::to_string(porcentaje) + "% - " + texto + "   ";
                    
                    std::cout << "\r";
                    ColorUI::printGradient(frame, ColorUI::Paletas::Register, false, false);
                    std::cout << std::flush;
                    std::this_thread::sleep_for(std::chrono::milliseconds(ms_por_paso));
                }
                std::cout << "\r" << sangria << "                                                                                \r";
            }

            static char AnimarMenuPrincipal() {
                CursorGuard cursorGuard;
                const int WIDTH = 100;
                const int HEIGHT = 26;
                int frame_count = 0;

                std::vector<std::pair<std::string, std::vector<std::string>>> menu_options = {
                    {"[1] CATALOGOS DE SERVICIOS", ColorUI::Paletas::Exito},
                    {"[2] RESERVAR UN SERVICIO", ColorUI::Paletas::Exito},
                    {"[3] VERIFICAR MIS DATOS", ColorUI::Paletas::Exito},
                    {"[4] MI HISTORIAL DE RESERVAS", ColorUI::Paletas::Exito},
                    {"[5] CANCELAR RESERVA", ColorUI::Paletas::Exito},
                    {"[6] CALIFICAR HOTEL", ColorUI::Paletas::Exito},
                    {"[7] CREDITOS", ColorUI::Paletas::Exito},
                    {"[0] Cerrar Sesion", ColorUI::Paletas::Alerta}
                };

                while (true) {
                    if (_kbhit()) {
                        char ch = _getch();
                        if (ch >= '0' && ch <= '7') {
                            return ch;
                        }
                    }

                    std::vector<std::string> canvas(HEIGHT, std::string(WIDTH, ' '));
                    std::vector<std::vector<std::string>> color_canvas(HEIGHT, std::vector<std::string>(WIDTH, "\033[0m"));

                    double time_sec = frame_count * 0.05;

                    std::string header = "=== SIMULADOR CHOCOFLY - MENU PRINCIPAL DE SERVICIOS ===";
                    drawToCanvas(canvas, color_canvas, (WIDTH - (int)header.length()) / 2, 1, {header}, ColorUI::Paletas::TemaPrincipal, true);

                    int banner_x = (int)round(27.0 + 1.5 * cos(time_sec * 1.2));
                    int banner_y = (int)round(3.0 + 0.5 * sin(time_sec * 1.5));
                    drawToCanvas(canvas, color_canvas, banner_x, banner_y, BANNER_CHOCOFLY, ColorUI::Paletas::TemaPrincipal, false);

                    std::vector<std::string> active_drone = DRONE_TEMPLATE;
                    active_drone[2] = PROP_FRAMES[(frame_count / 2) % PROP_FRAMES.size()];

                    int left_x = (int)round(3.0 + 2.0 * sin(time_sec * 1.5));
                    int left_y = (int)round(12.0 + 5.0 * sin(time_sec * 1.8));
                    drawToCanvas(canvas, color_canvas, left_x, left_y, active_drone, ColorUI::Paletas::TemaPrincipal, true);

                    int right_x = (int)round(75.0 - 2.0 * sin(time_sec * 1.5));
                    int right_y = (int)round(12.0 + 5.0 * cos(time_sec * 1.8));
                    drawToCanvas(canvas, color_canvas, right_x, right_y, active_drone, ColorUI::Paletas::gege, true);

                    int menu_start_y = 10;
                    int menu_x = 34;
                    for (size_t i = 0; i < menu_options.size(); ++i) {
                        int option_y = menu_start_y + (int)(i * 2);
                        drawToCanvas(canvas, color_canvas, menu_x, option_y, {menu_options[i].first}, menu_options[i].second, false);
                    }

                    renderCanvas(canvas, color_canvas);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    frame_count++;
                }
            }
        };

    }
}
using namespace ColorUI::AnimacionesUI;
