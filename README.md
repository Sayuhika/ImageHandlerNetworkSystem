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
## Установка необходимых пакетов:
### Вариант 1. Из пакетов

CMake:
* > $ sudo apt install cmake

ZMQ:
* > $ apt install libzmq3-dev

Protobuf:
* > $ sudo apt-get install libprotobuf-dev protobuf-compiler
* > $ protoc --version

### Вариант 2. Из исходников

ZMQ:
* > $ wget https://github.com/zeromq/libzmq/releases/download/v4.3.4/zeromq-4.3.4.tar.gz
* > $ tar -xvf zeromq-4.3.4.tar.gz
* > $ cd zeromq-4.3.4
* > $ ./autogen.sh
* > $ ./configure
* > $ make
* > $ sudo make install

Protobuf:
* > $ wget https://github.com/protocolbuffers/protobuf/releases/download/v3.15.8/protobuf-all-3.15.8.tar.gz
* > $ tar -xvf protobuf-all-3.15.8.tar.gz
* > $ cd protobuf-3.15.8
* > $ ./configure
* > $ make
* > $ sudo make install