# SO-processor

Implementacion de procesador V1

Revisar instrucciones posibles para la implementacion y falta la implementacion de la memoria
Hacer explicacion de como utilizar esta implementación.

Pendiente:

Hacer que funcione con todas las variantes del add, y en la funcionalidad SHW: cuando se hace esta funcion con estos parametros, no funciona: SHW UC NULL NULL NULL. Error: terminate called after throwing an instance of 'std::invalid_argument'
what(): stoi. Ademas, cuando hace esto: SHW MAR NULL NULL NULL, el resultado es vacio entonces, esto no estaria bien, deberia devolver el valor del pc que fue la que le paso al MAR para poder traer la instruccion anterior.



### Ejecución del programa  (explicación)

Manera corta de ejecución:

Nota: programaX.txt indica X el programa que se quiere probar. Ej: programa1.txt

```
mkdir build
cd build
cmake ..
cmake --build .
.\Debug\Procesador.exe ..\programaX.txt
```
Para ejecutar el programa es necesario compilar primero el proyecto utilizando **CMake**. Los pasos son los siguientes:

1. Abrir una terminal en la carpeta raíz del proyecto.

2. Crear una carpeta para la compilación:

```
mkdir build
cd build
```

3. Generar los archivos de compilación con CMake:

```
cmake ..
```

4. Compilar el proyecto:

```
cmake --build .
```

5. Una vez finalizada la compilación, se generará el ejecutable `Procesador.exe` dentro de la carpeta `build/Debug`.

6. Para ejecutar el programa se utiliza el siguiente comando:

```
.\Debug\Procesador.exe
```

Si el programa requiere un archivo de entrada (por ejemplo `programa.txt`), se puede ejecutar de la siguiente manera:

```
.\Debug\Procesador.exe ..\programa.txt
```

Esto ejecutará el simulador del procesador utilizando el archivo de instrucciones proporcionado.
