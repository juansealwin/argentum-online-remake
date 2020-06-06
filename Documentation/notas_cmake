cmake_minimum_required(VERSION 2.8)

project(cmake-demo)

add_executable(ej0 main.cpp)            // Nombre del ejecutable que quiero armar y archivos fuente q lo componen

// CON ESTAS 3 LINEAS GENERO UN MAKE PARA COMPILAR EL PROGRAMA
// EL MAKEFILE SE CREA COMO "cmake <ruta al cmake>"
// el cmake se tiene que llamar CMakeLists.txt
// Lo mas limpio es crear una carpeta "build" y separar el directorio de compilacion del de las fuentes
// Luego con "make" en el directorio donde esta el Makefile se buildea y se crea el ejecutable


// En el siguiente ejemplo se buildea un proyecto con varios .cpp
cmake_minimum_required(VERSION 2.8)

project(cmake-demo)

FILE(GLOB MyFiles "*.cpp")              // Busca los archivos .cpp que esten en el directorio de este cmake

message (STATUS "Cargué ${myFiles}")

add_executable(ej4 ${myFiles} main.cpp)

// Por qué cmake y no makefile? porque para el tp queremos trabajar con bibliotecas (box2d, gtkmm, cxxtest, etc)
// Ejemplo:

// en un fuente tenemos #include <zip.h> // trabajamos con la libreria de zip... con makefile seria un bardo

cmake_minimum_required(C)

project(cmake-demo)

add_executable(ej-zip main.cpp)

target_link_libraries(ej-zip zip)  // ej-zip es el nombre del aplicativo y las bibliotecas contra las 
                                      que quiero linkear (pueden ser 1 o pueden ser varias)