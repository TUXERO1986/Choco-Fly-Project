#include "ReservaPaquete.h"
ReservaPaquete::ReservaPaquete(string codUser, string nomUser, Ticket* vueloida, Ticket* vueloretorno, ReservaHotel* hotel)
    : Reserva(codUser, nomUser)
{
    this->vueloReservado = vueloida;
    this->vueloRetorno = vueloretorno;
    this->hotelReservado = hotel;
}

ReservaPaquete::~ReservaPaquete() {
    delete vueloReservado;
    delete vueloRetorno;
    delete hotelReservado;
}

void ReservaPaquete::MostrarReserva() {
    cout << "======================================" << endl;
    cout << "        PAQUETE TURISTICO             " << endl;
    cout << "Pasajero: " << nombreUsuario << endl;
    cout << "======================================" << endl;

    if (vueloReservado != nullptr) vueloReservado->MostrarReserva();
    cout << "--------------------------------------" << endl;
    if (hotelReservado != nullptr) hotelReservado->MostrarReserva();

    float total = vueloReservado->getPrecioTotal() + hotelReservado->getPrecioTotal();
    cout << "======================================" << endl;
    cout << "PRECIO TOTAL DEL PAQUETE: $" << total << endl;
    cout << "======================================" << endl;
}
string ReservaPaquete::aTextoArchivo() {
    return "PAQUETE," + codigoUsuario + "," + nombreUsuario + "|" + vueloReservado->aTextoArchivo() +"|"+vueloRetorno->aTextoArchivo() + "|" + hotelReservado->aTextoArchivo();
}
Ticket* ReservaPaquete::getVueloReservado() { return vueloReservado; }
ReservaHotel* ReservaPaquete::getHotelReservado() { return hotelReservado; }
Ticket* ReservaPaquete::getVueloRetorno() { return vueloRetorno; }
void ReservaPaquete::setVueloReservado(Ticket* vuelo) { this->vueloReservado = vuelo; }
void ReservaPaquete::setHotelReservado(ReservaHotel* hotel) { this->hotelReservado = hotel; }
void ReservaPaquete::setVueloRetorno(Ticket* vuelo) { this->vueloRetorno = vuelo; }
float ReservaPaquete::getPrecioTotal() {
    return vueloReservado->getPrecioTotal() + hotelReservado->getPrecioTotal();
}