#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <cstdlib>

#ifdef _WIN32
    //#include <windows.h>//solo para windows aunque lo comente o borre igual va funcionar
    #define CLEAR_COMMAND "cls"//comando para limpiar pantlla
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    #include <unistd.h>//ayuda en el desenpeño de la pantalla 
    #include <termios.h>
    #define CLEAR_COMMAND "clear"//comando para limpiar pantalla
#endif

void mostrar_caratula() {
    std::system(CLEAR_COMMAND);            // Borrar todo el contenido de la pantalla
    std::cout << "\x1B[H";          // Mover el cursor a la esquina superior izquierda

    std::cout << "\x1B[200;90;106m";         // Aplicar color y estilo
    std::cout << "/***************************************************************************************/" << std::endl; 
    std::cout << "\x1B[m";             // Restablecer color a valor por defecto
    std::cout << "\x1B[31;1m                         Universidad Catolica San Pablo \x1B[m" << std::endl; 
    std::cout << "\x1B[33;1m              Escuela Profesional de Ciencia de la Computacion \x1B[m" << std::endl; 
    std::cout << "\x1B[22;1m                     Curso de Ciencia de la Computacion II \x1B[m" << std::endl; 
    std::cout << "\x1B[38;5;63m                 Estudiante - Jhon Alexander Flores Condori  \x1B[m" << std::endl; 
    std::cout << "\x1B[3;38;5;160m                          Arequipa 2024 - Semestre III \x1B[m" << std::endl; 
    std::cout << "\x1B[200;90;106m";         // Aplicar color y estilo de nuevo
    std::cout << "/***************************************************************************************/" << std::endl;
    std::cout << "\x1B[m";             // Restablecer color a valor por defecto 
    std::cout << "\n !! PUZZLE !! \n\n"; // Mostrar título del proyecto
}

void imprimirtablero(int* tablero) {
    std::cout << "\nTABLERO\n";
    std::cout << "+---+---+---+\n";
    for(int i = 0; i < 3; i++) {
        std::cout << "|";
        for(int j = 0; j < 3; j++) {
            if (*(tablero + i*3 + j) == 9) {
                std::cout << "   |";
            } else {
                std::cout << " " << *(tablero + i*3 + j) << " |";
            }
        }
        std::cout << "\n+---+---+---+\n";
    }
}

void mover_espacio(int* tablero, char movimiento) {
    int espacio = 0, columna = 0;
    // Encontrar el espacio vacío
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (*(tablero + i*3 + j) == 9) {
                espacio = i;
                columna = j;
            }
        }
    }

    switch(movimiento) {
        case 'w': case 'W':    
            if(espacio > 0) {
                std::swap(*(tablero + espacio*3 + columna), 
                         *(tablero + (espacio-1)*3 + columna));
            }
            break;
        
        case 's': case 'S':    
            if(espacio < 2) {
                std::swap(*(tablero + espacio*3 + columna), 
                         *(tablero + (espacio+1)*3 + columna));
            }
            break;
        
        case 'a': case 'A':    
            if(columna > 0) {
                std::swap(*(tablero + espacio*3 + columna), 
                         *(tablero + espacio*3 + (columna-1)));
            }
            break;
        
        case 'd': case 'D':    
            if(columna < 2) {
                std::swap(*(tablero + espacio*3 + columna), 
                         *(tablero + espacio*3 + (columna+1)));
            }
            break;
    }
}

bool definir_ganador(int* tablero) {
    const int tablero_objetivo[9] = {1,2,3,4,5,6,7,8,9};
    
    for(int i = 0; i < 9; i++) {
        if(*(tablero + i) != tablero_objetivo[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    mostrar_caratula();

    // Crear vector con números del 1 al 8
    std::vector<int> numeros = {1,2,3,4,5,6,7,8};
    
    // Crear generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(numeros.begin(), numeros.end(), gen);

    // Crear el tablero con memoria dinámica
    int* tablero = new int[9];  // Array unidimensional de 9 elementos
    
    // Llenar el tablero
    int k = 0;
    for(int i = 0; i < 9; i++) {
        if(i == 8) {  // Última posición
            tablero[i] = 9;
        } else {
            tablero[i] = numeros[k++];
        }
    }

    char tecla;
    while(true) {
        imprimirtablero(tablero);
        
        if(definir_ganador(tablero)) {
            std::cout << "\n¡¡¡FELICITACIONES, GANASTE!!!\n";
            break;
        }
        
        std::cout << "\nUsa W-A-S-D para mover (Q para salir): ";
        std::cin >> tecla;
        
        if(tecla == 'q' || tecla == 'Q') 
            break;
            
        mover_espacio(tablero, tecla);
        std::system(CLEAR_COMMAND);
    }
    
    // Liberar memoria
    delete[] tablero;
    
    return 0;
}
