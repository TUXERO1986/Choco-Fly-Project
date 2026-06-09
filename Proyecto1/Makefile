# ============================================================
# Makefile Cross-Platform - Proyecto1 (ChocoflyApp)
# Compatible: Linux / macOS / Windows (con MinGW/MSYS2)
# Uso:
#   Linux/macOS : make
#   Windows     : mingw32-make   (o make si está en PATH)
# ============================================================

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wno-return-type
TARGET   := app_vuelos

SRCS := \
    Pirncipal.cpp \
    AdminPantallas.cpp \
    AsciiArt.cpp \
    Asiento.cpp \
    CiudadID.cpp \
    ControladorArchivos.cpp \
    ControladorAsientos.cpp \
    ControladorHabitaciones.cpp \
    ControladorHoteles.cpp \
    ControladorPaquetes.cpp \
    ControladorPrincipal.cpp \
    ControladorReservas.cpp \
    ControladorRutas.cpp \
    ControladorUsuarios.cpp \
    ControladorVuelos.cpp \
    GestionPantallas.cpp \
    Habitacion.cpp \
    Hotel.cpp \
    Pantallas.cpp \
    Paquete.cpp \
    Reserva.cpp \
    ReservaHotel.cpp \
    ReservaPaquete.cpp \
    Ruta.cpp \
    Ticket.cpp \
    Usuario.cpp \
    Vuelo.cpp

# Detección automática del sistema operativo
ifeq ($(OS), Windows_NT)
    TARGET  := $(TARGET).exe
    RM      := del /Q
else
    RM      := rm -f
endif

# --- Reglas ---

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)
	@echo "===> Compilacion exitosa: $(TARGET)"

clean:
	$(RM) $(TARGET)

run: $(TARGET)
ifeq ($(OS), Windows_NT)
	$(TARGET)
else
	./$(TARGET)
endif

.PHONY: all clean run
