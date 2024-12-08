#include <iostream>
#pragma once
#include <string>

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
};
