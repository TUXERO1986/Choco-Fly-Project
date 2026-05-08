#pragma once
#include "Reserva.h"
class ReservaHotel : public Reserva
{
private:
	string nombreHotel;
	string ciudad;
	int noches;
	float precioNoche;
public:
	ReservaHotel(string codigoUsuario, string nombreUsuario, string nombreHotel, string ciudad, float precioNoche, int noches);
	void MostrarReserva() override;
	string aTextoArchivo() override;
	string getNombreHotel();
	string getCiudad();
	int getNoches();
	float getPrecioTotal();
	void setNombreHotel(string nombreHotel);
	void setCiudad(string ciudad);
	void setNoches(int noches);
	void setPrecioNoche(float precioNoche);
};

