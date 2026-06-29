#pragma once
#include "Reserva.h"
#include <functional>
class ReservaVuelo : public Reserva
{
private:
	string nombre;
	string origen;
	string destino;
	string escalas;
	string fecha;
	float distancia;
	int equipaje;
	int equipajecabina;
	int clase;
	int asiento;
	function<string(int)> obtenerClase;
public:
	ReservaVuelo(string codigoUsuario,string nombreUsuario,string origen, string destino, 
		string escalas, string fecha,float distancia, int equipaje, int equipajecabina,int clase,
		int asiento);
	void MostrarReserva() override;
	string aTextoArchivo() override;
	string getNombre();
	string getOrigen();
	string getDestino();
	string getEscalas();
	float getPrecioTotal() override;
	float getDistancia();
	string getFecha();
	int getClase();
	int getAsiento();
	int getEquipaje();
	int getEquipajeCabina();
	void setOrigen(string origen);
	void setDestino(string destino);
	void setEscalas(string escalas);
	void setDistancia(float distancia);
	void setEquipaje(int equipaje);
	void setEquipajeCabina(int equipajecabina);
	void setNombre(string nombre);
};

