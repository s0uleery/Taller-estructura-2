#include <iostream>
#include "Tablero.h"
#pragma once
#include <string>

using namespace std;

pair<int, int> obtenerCoordenadas(int posicion) { 
    int fila = (posicion - 1) / 3; 
    int columna = (posicion - 1) % 3; 
    return {fila, columna}; 
}

void jugadoVSjugador(Tablero& juego, char jugador1, char jugador2) {
    char JugadorActual = jugador1;

    while(true){
        
        juego.mostrarTablero();
        int pos;
	    cout << "Jugador " << JugadorActual << ", introduce la posiciC3n (1-9): " << endl;
        cin >> pos;
        
        pair<int, int> coordenadas = obtenerCoordenadas(pos);
        int fila = coordenadas.first; 
        int columna = coordenadas.second;
        
        if(juego.movimientoValido(fila, columna)){
            juego.hacerMovimiento(fila, columna, JugadorActual);
            
            if(juego.verificarGanador(JugadorActual)){
                juego.mostrarTablero();
                cout << "¡" << JugadorActual << " ha ganado!" <<endl;
                break;
            }
            
            if(juego.hayEmpate()){
                juego.mostrarTablero();
                cout << "Es un empate. ¡Bien jugado ambos jugadores!" << endl;
                break;
            }
            
            JugadorActual = (JugadorActual == jugador1) ? jugador2 : jugador1;
            
        }else{
            cout << "Movimiento inválido, intenta de nuevo." << endl;
        }
    }
}

class Menu {

public:
	Tablero juego;
	char jugador = 'X';
	char IA = 'O';
	int op;

	void ImprimirMenu() {
		do {
			cout << "--------------------------------------------------------" << endl;
			cout << "El Gato" << endl;
			cout << "1. Jugador V/S Jugador" << endl;
			cout << "2. Jugador V/S IA" << endl;
			cout << "0. SALIR " << endl;
			cout << "Seleccione una opciC3n: " << endl;
			cout << "--------------------------------------------------------" << endl;



			cin >> op;
			switch(op) {
			case 1:
				juego.posTablero();
				jugadoVSjugador(juego,jugador,IA);
				break;
			case 2:

				cout << "2..." << endl;
				break;

			case 0:
				cout << "Esta saliendo del programa..." << endl;
				break;

			default:
				cout << "OpciC3n no vC!lida. Presione Enter para continuar..." << endl;
				cin.ignore();
				cin.get();
				break;
			}

		} while(op != 0 );
	}
};