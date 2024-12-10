#include <iostream>
#include "Tablero.h"
#pragma once
#include <string>
#include <utility>

using namespace std;

pair<int, int> obtenerCoordenadas(int posicion) { 
    int fila = (posicion - 1) / 3; 
    int columna = (posicion - 1) % 3; 
    return {fila, columna}; 
}

void jugadoVSjugador(Tablero juego, char jugador1, char jugador2) {
    char JugadorActual = jugador1;

    while(true){
        cout << "Jugador vs Jugador.\n";
        juego.mostrarTablero();
        int pos;
	    cout << "Jugador " << JugadorActual << " es tu turno, introduce la posicion (1-9): " << endl;
        cin >> pos;
        
        pair<int, int> coordenadas = obtenerCoordenadas(pos);
        int fila = coordenadas.first; 
        int columna = coordenadas.second;
        
        if(juego.movimientoValido(fila, columna)){
            juego.hacerMovimiento(fila, columna, JugadorActual);
            
            if(juego.verificarGanador(JugadorActual)){
                juego.mostrarTablero();
                cout << JugadorActual << " gano" <<endl;
                break;
            }
            
            if(juego.hayEmpate()){
                juego.mostrarTablero();
                cout << " Es un empate " << endl;
                break;
            }
    
            if (JugadorActual == jugador1) {
                JugadorActual = jugador2;
            } else {
                JugadorActual = jugador1;
            }
        }else{
            cout << "Movimiento no valido, intenta de nuevo." << endl;
        }
    }
}

void jugadoVScomp(Tablero juego, char jugador1, char jugador2) {
    char JugadorActual = jugador1;

    while (true) {
        if (JugadorActual == jugador1) { 
            juego.mostrarTablero();
            int pos;
            cout << "Jugador " << JugadorActual << ", introduce la posición (1-9): " << endl;
            cin >> pos;

            pair<int, int> coordenadas = obtenerCoordenadas(pos);
            int fila = coordenadas.first;
            int columna = coordenadas.second;

            if (!juego.movimientoValido(fila, columna)) {
                cout << "Movimiento no válido, intenta de nuevo." << endl;
                continue;
            }

            juego.hacerMovimiento(fila, columna, JugadorActual);

            if (juego.verificarGanador(JugadorActual)) {
                juego.mostrarTablero();
                cout << JugadorActual << " ganó, felicidades humano." << endl;
                break;
            }

            JugadorActual = jugador2;
            
        } else { // Turno de la IA
            pair<int, int> mejorMovimiento = juego.encontrarMejorMovimiento();

            juego.hacerMovimiento(mejorMovimiento.first, mejorMovimiento.second, 'O');
            cout << "IA ha jugado en la posición: " << (mejorMovimiento.first * 3 + mejorMovimiento.second + 1) << endl;

            if (juego.verificarGanador('O')) {
                juego.mostrarTablero();
                cout << "IA ganó, estupido humano." << endl;
                break;
            }

            JugadorActual = jugador1;
        }

        if (juego.hayEmpate()) {
            juego.mostrarTablero();
            cout << "Es un empate." << endl;
            break;
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
			cout << "2. Jugador V/S Comp" << endl;
			cout << "0. SALIR " << endl;
			cout << "Seleccione una opcion: " << endl;
			cout << "--------------------------------------------------------" << endl;

			cin >> op;
			switch(op) {
			case 1:
				juego.posTablero();
				jugadoVSjugador(juego,jugador,IA);
				break;
			case 2:
			    juego.posTablero();
				jugadoVScomp(juego,jugador,IA);
				break;

			case 0:
				cout << "Esta saliendo del programa..." << endl;
				break;

			default:
				cout << "Opcion no valida. Presione Enter para continuar..." << endl;
				cin.ignore();
				cin.get();
				break;
			}

		} while(op != 0 );
	}
};
