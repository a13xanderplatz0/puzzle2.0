#include <iostream>
#include <random>//para genrar numeros aleatorios
#include <algorithm>//para std::random_shuffle
#include <vector>//para std::vector
/*ya no se usa #include<cstdlib> rand()  y#include<ctime> time()
es obsoleto */
// Hello World program 
// ANSI Codes
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797


#ifdef _WIN32
    //#include <windows.h>//solo para windows aunque lo comente o borre igual va funcionar
    #define CLEAR_COMMAND "cls"//comando para limpiar pantlla
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    #include <unistd.h>//ayuda en el desenpeño de la pantalla 
    #include <termios.h>
    #define CLEAR_COMMAND "clear"//comando para limpiar pantalla
#endif
void mostrar_caratula(){
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



void imprimirtablero(int tablero[3][3] )
{
    std::cout<<"\nTABLERO\n";
    std::cout<<"+---+---+---+\n";
    for(int i=0;i<3;i++)
    {
        std::cout<<"|";
        for(int j=0;j<3;j++)
        {
            if (tablero[i][j]==9)
            /*| y numero*/
            {
               std::cout<<"   |";
            }
            else
                {
                    std::cout<<" "<<tablero[i][j]<<" |";
                }
        }
        std::cout<<"\n+---+---+---+\n";
    }

}
void mover_espacio(int tablero[3][3], char movimiento)
{
    int espacio, columna;
    for(int i=0; i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if (tablero[i][j]==9)
            {
                espacio=i;
                columna=j;
            }
        }
    }
switch(movimiento)
{
    case 'w': case 'W':    
        if(espacio > 0)
        {
            std::swap(tablero[espacio][columna], tablero[espacio - 1][columna]);
        }
        break;
        
    case 's': case 'S':    
        if(espacio < 2)
        {
            std::swap(tablero[espacio][columna], tablero[espacio + 1][columna]);
        }
        break;
        
    case 'a': case 'A':    
        if(columna > 0)
        {
            std::swap(tablero[espacio][columna], tablero[espacio][columna - 1]); 
        }
        break;
        
    case 'd': case 'D':    
        if(columna < 2)
        {
            std::swap(tablero[espacio][columna], tablero[espacio][columna + 1]); 
        }
        break;
}
}
bool definir_ganador(int tablero[3][3])  // Cambié el nombre del parámetro
{
    // Definimos el tablero objetivo (estado ganador)
    const int tablero_objetivo[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    
    // Comparamos cada posición
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(tablero[i][j] != tablero_objetivo[i][j])
            {
                return false;
            }
        }
    }
    return true;
}


int main()
{
    mostrar_caratula();
    //crear un vector con numeros del 1 al 8
    std::vector<int> numeros ={1,2,3,4,5,6,7,8};
    //crear generdor de numeros aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    //mezclar los numeros aleatoriamente
    std::shuffle(numeros.begin(),numeros.end(),gen);

    //crear el tablero con los numeros mezclados y el 9 estara fijo
    int tablero[3][3];
    int k=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i==2 && j==2)
            {
                tablero[i][j]=9;
            }
            else
            {
                tablero[i][j]=numeros[k++];
            }
        }
    }


    char tecla;
    
    while(true) {
        imprimirtablero(tablero);
        //verificar si gano
        if(definir_ganador(tablero))
        {
            std::cout<<"\nFELICITACIONES USTED GANO\n";
            break;
        }
        std::cout << "\nUsa W-A-S-D para mover el espacio (Q para salir): ";
        std::cin >> tecla;
        
        if(tecla == 'q' || tecla == 'Q') 
            break;
            
        mover_espacio(tablero, tecla);
        std::system(CLEAR_COMMAND);
    }
    
    return 0;
}
