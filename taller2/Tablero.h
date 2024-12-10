#include <iostream>
#pragma once
#include <string>
#include <utility>

using namespace std;

class Tablero {
    
    private:
        char tablero[3][3];
        
    public:
        Tablero();
        void posTablero();
        void mostrarTablero();
        bool movimientoValido(int fila, int columna);
        void hacerMovimiento(int fila, int columna, char jugador);
        bool verificarGanador(char jugador);
        bool hayEmpate();
        char obtenerCelda(int fila, int columna) const;
        void setCelda(int fila, int columna, char valor);
        int miniMaxSin(Tablero& tab, int profundidad, bool isMaximing);
        int miniMaxCon(Tablero& tab, int profundidad, int alfa,int beta, bool isMaximing);
        pair<int, int> encontrarMejorMovimiento();
};
