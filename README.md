# Computación Gráfica
Implementación del algoritmo Liang-Barsky, con fines ilustrativos.

Algoritmo implementado en Python y C.

Forma de uso (Python):

    $ python3 line_clipping.py wx wy ancho alto
    
Los datos de entrada se toman de un archivo con nombre "input.txt" y los resultados son
almacenados en el archivo con nombre "output.txt".

Forma de uso (C):

    $ gcc -o line_clipping line_clipping.c
    $ ./line_clipping fileInput fileOutput wx wy ancho alto
    
donde:
fileInput: archivo que contiene los datos de entrada
fileOutput: archivo donde se guardarán los resultados


Para ambos casos:
* (wx, wy) representan el punto inicial de la ventana
* ancho: tamaño del ancho de la ventana, a partir del punto
* ancho: tamaño del largo de la ventana, a partir del punto

* Los datos de entrada en el archivo tienen el siguiente formato
    
    p1X p1Y
    
    p2X p2Y
    
      ...
      
    pnX pnY
    
donde cada par de valores en la misma fila representan un punto de la línea; cada línea debe estar
especificada por dos puntos.
