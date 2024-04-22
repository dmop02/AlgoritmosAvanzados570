/*
En equipos de máximo 3 personas, escribe un programa en C++ que lea 5 archivos
de texto (de nombre fijo, no se piden al usuario) que contienen exclusivamente
caracteres del 0 al 9, caracteres entre A y F y saltos de línea
     transmission1.txt
     transmission2.txt
     mcode1.txt
     mcode2.txt
     mcode3.txt

Los archivos de transmision contienen caracteres de texto que representan el
envío de datos de un dispositivo a otro. Los archivos mcodex.txt representan
código malicioso que se puede encontrar dentro de una transmisión.

El programa debe analizar si el contenido de los archivos mcode1.txt, mcode2.txt
y mcode3.,txt están contenidos en los archivos transmission1.txt y
transmission2.txt y desplegar un true o false si es que las secuencias de chars
están contenidas o no. En caso de ser true, muestra true, seguido de exactamente
un espacio, seguido de la posición en el archivo de transmissiónX.txt donde
inicia el código de mcodeY.txt

Suponiendo que el código malicioso tiene siempre código "espejeado" (palíndromos
de chars), sería buena idea buscar este tipo de código en una transmisión. El
programa después debe buscar si hay código "espejeado" dentro de los archivos de
transmisión. (palíndromo a nivel chars, no meterse a nivel bits). El programa
muestra en una sola linea dos enteros separados por un espacio correspondientes
a la posición (iniciando en 1) en donde inicia y termina el código "espejeado"
más largo (palíndromo) para cada archivo de transmisión. Puede asumirse que
siempre se encontrará este tipo de código.

Finalmente el programa analiza que tan similares son los archivos de
transmisión, y debe mostrar la posición inicial y la posición final (iniciando
en 1) del primer archivo en donde se encuentra el substring más largo común
entre ambos archivos de transmisión

input
     nada, solamente deben existir los 5 archivos en la misma ruta donde se
ejecuta el programa

output
  parte 1
     (true | false) si es que el archivo transmission1.txt contiene el código
(secuencia de chars) contenido en el archivo mcode1.txt (true | false) si es que
el archivo transmission1.txt contiene el código (secuencia de chars) contenido
en el archivo mcode2.txt (true | false) si es que el archivo transmission1.txt
contiene el código (secuencia de chars) contenido en el archivo mcode3.txt (true
| false) si es que el archivo transmission2.txt contiene el código (secuencia de
chars) contenido en el archivo mcode1.txt (true | false) si es que el archivo
transmission2.txt contiene el código (secuencia de chars) contenido en el
archivo mcode2.txt (true | false) si es que el archivo transmission2.txt
contiene el código (secuencia de chars) contenido en el archivo mcode3.txt
  parte2
     posiciónInicial posiciónFinal (para archivo de transmisión1)
     posiciónInicial posiciónFinal (para archivo de transmisión2)
  parte3
      posiciónInicial posiciónFinal (de substring común más largo entre archivos
de transmisión)

Ejemplo:


Parte 1:
true 1276
false
false
false
true 1
true 1786
Parte 2:
850 856 dD242Dd
1785 1835 BDa92D09Ac7a63E1C1fECDcb2bcDCEf1C1E36a7cA90D29aDB
Parte 3:
657 661 1C1E3
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Funcion de lectura de archivos
std::string leerArchivo(const std::string &nombreArchivo) {
  std::ifstream file(nombreArchivo);
  // Verificar que se pueda abrir el archivo
  if (file.fail()) {
    std::cout << "No fue posible abrir el archivo";
    exit(1);
  }
  std::string contenido((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
  return contenido;
}

// Funciones Auxiliares
bool haySub(const std::string &cadena, const std::string &subcadena) {
  return cadena.find(subcadena) != std::string::npos;
}

std::string palindromoMaximo(const std::string &cadena) {
  if (cadena.empty())
    return "";

  int maxLongitud = 1, inicio = 0, len = cadena.length();
  std::vector<std::vector<int>> matriz(len, std::vector<int>(len, 0));

  for (int i = 0; i < len; ++i)
    matriz[i][i] = 1;

  for (int i = 0; i < len - 1; ++i)
    if (cadena[i] == cadena[i + 1]) {
      matriz[i][i + 1] = 1;
      inicio = i;
      maxLongitud = 2;
    }

  for (int k = 3; k <= len; ++k)
    for (int i = 0; i < len - k + 1; ++i) {
      int j = i + k - 1;
      if (matriz[i + 1][j - 1] && cadena[i] == cadena[j]) {
        matriz[i][j] = 1;
        if (k > maxLongitud) {
          inicio = i;
          maxLongitud = k;
        }
      }
    }

  return std::to_string(inicio + 1) + " " +
         std::to_string(inicio + maxLongitud) + " " +
         cadena.substr(inicio, maxLongitud);
}

std::string subComunMaximo(const std::string &cadena1,
                           const std::string &cadena2) {
  if (cadena1.empty() || cadena2.empty())
    return "";

  int m = cadena1.length(), n = cadena2.length(), maxLongitud = 0, fin = 0;
  std::vector<std::vector<int>> matriz(m + 1, std::vector<int>(n + 1, 0));

  for (int i = 0; i <= m; ++i)
    for (int j = 0; j <= n; ++j)
      if (i == 0 || j == 0)
        matriz[i][j] = 0;
      else if (cadena1[i - 1] == cadena2[j - 1]) {
        matriz[i][j] = matriz[i - 1][j - 1] + 1;
        if (matriz[i][j] > maxLongitud) {
          maxLongitud = matriz[i][j];
          fin = i - 1;
        }
      }

  return std::to_string(fin - maxLongitud + 2) + " " + std::to_string(fin + 1) +
         " " + cadena1.substr(fin - maxLongitud + 1, maxLongitud);
}

int main() {
  std::string texto1 = leerArchivo("mcode1.txt");
  std::string texto2 = leerArchivo("mcode2.txt");
  std::string texto3 = leerArchivo("mcode3.txt");

  std::string cadena1 = leerArchivo("transmission1.txt");
  std::string cadena2 = leerArchivo("transmission2.txt");

  std::cout << "Parte 1:" << std::endl;
  std::cout << (haySub(cadena1, texto1)
                    ? "true " + std::to_string(cadena1.find(texto1) + 1)
                    : "false")
            << std::endl;
  std::cout << (haySub(cadena1, texto2)
                    ? "true " + std::to_string(cadena1.find(texto2) + 1)
                    : "false")
            << std::endl;
  std::cout << (haySub(cadena1, texto3)
                    ? "true " + std::to_string(cadena1.find(texto3) + 1)
                    : "false")
            << std::endl;
  std::cout << (haySub(cadena2, texto1)
                    ? "true " + std::to_string(cadena2.find(texto1) + 1)
                    : "false")
            << std::endl;
  std::cout << (haySub(cadena2, texto2)
                    ? "true " + std::to_string(cadena2.find(texto2) + 1)
                    : "false")
            << std::endl;
  std::cout << (haySub(cadena2, texto3)
                    ? "true " + std::to_string(cadena2.find(texto3) + 1)
                    : "false")
            << std::endl;

  std::cout << "Parte 2:" << std::endl;
  std::cout << palindromoMaximo(cadena1) << std::endl;
  std::cout << palindromoMaximo(cadena2) << std::endl;

  std::cout << "Parte 3:" << std::endl;
  std::cout << subComunMaximo(cadena1, cadena2) << std::endl;

  return 0;
}