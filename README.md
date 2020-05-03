## Зависимости

* GTest 
* GLFW >= 3.3 (libglfw3)
* JsonCpp (libjsoncpp-dev)
* OpenGL Mathematics (GLM) >= 0.9.9.7 (libglm-dev)

## Сборка

```
mkdir build && cd build
cmake [-DRESOURCES_DIR] [-DLAUNCHER_DIR] [-DBINARY_DIR] [-DTESTING] ..
make
make install
```

Параметры:

`RESOURCES_DIR [= /usr/share]` - папка с ресурсами игры  
`LAUNCHER_DIR [= ~/Desktop]` - путь до лаунчера  
`BINARY_DIR [= CMAKE_INSTALL_PREFIX]` - путь до исполняемого файла  
`[TESTING = ON]` - если указан, будут собраны тесты 

Протестировано на `macOS 10.15` и `Ubuntu 18.04`

## Запуск

`./Fabryca.sh` - запуск игры (на данный момент игровой логики нет, поэтому можно только перемещаться по карте через WASD + Enter)
`./FabrycaTests.sh` - запуск тестов
