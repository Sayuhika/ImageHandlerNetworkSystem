# **Linux**

# ImageHandlerNetworkSystem
UNN study project with ZMQ and Protobuf

# APPs:
1) **WebCamServer** (wcs-app)
* Занимается получением изображений с камеры и отправкой их на **ImageHandler**.
2) **ImageHandler** (ih-app)
* Получает изображения из приложения **WebCamServer** и обрабатывает их. После обработки отправляет исходное изображение и обработанное в приложение **ImageCollectorServer**.
3) **ImageCollectorServer** (ics-app)
* Собирает обработанные изображения и сохраняет их в видео \ выводит на экран. В зависимости от реализации, которая будет осуществлена.

# After clone:
## Установка необходимых инструментов:

CMake:
* ```$ sudo apt install cmake```

## Установка необходимых зависимостей:
### **Вариант 1 - Из пакетов**

ZMQ:
* ```$ apt install libzmq3-dev```

Protobuf:
* ```$ sudo apt-get install libprotobuf-dev protobuf-compiler```
* ```$ protoc --version```

### **Вариант 2 - Из исходников**

ZMQ:
* ```$ wget https://github.com/zeromq/libzmq/releases/download/v4.3.5/zeromq-4.3.5.tar.gz```
* ```$ tar -xvf zeromq-4.3.5.tar.gz```
* ```$ cd zeromq-4.3.5```
* ```$ ./autogen.sh```
* ```$ ./configure```
* ```$ make```
* ```$ sudo make install```

Protobuf:
* ```$ wget https://github.com/protocolbuffers/protobuf/releases/download/v24.4/protobuf-24.4.tar.gz```
* ```$ tar -xvf protobuf-24.4.tar.gz```
* ```$ cd protobuf-24.4```
* ```$ ./configure```
* ```$ make```
* ```$ sudo make install```
