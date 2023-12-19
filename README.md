# ImageHandlerNetworkSystem
UNN study project with ZMQ and Bitsery

# APPs:
1) **WebCamServer** (wcs-app)
* Занимается получением изображений с камеры и отправкой их на **ImageHandler**.
2) **ImageHandler** (ih-app)
* Получает изображения из приложения **WebCamServer** и обрабатывает их. После обработки отправляет исходное изображение и обработанное в приложение **ImageCollectorServer**.
3) **ImageCollectorServer** (ics-app)
* Собирает обработанные изображения, сортирует их по времени и сохраняет их в видео \ выводит на экран. В зависимости от реализации, которая будет осуществлена.

# After clone:
Открыть терминал в корне проекта и выполнить следующие команды:
* **git submodule update --init --recursive**

# Current opencv-lib problem:
Поскольку с проектной opencv-lib есть проблемы, для работы проекта необходимы некоторые манипуляции по гайду:
* https://www.youtube.com/watch?v=aMXQshF7zdo

# *.exe can't run:
Необходимо переместить opencv dll файлы в папку с выходным .exe файлом. Также, из папки build/libs/libzmq/bin/Debug/ можно достать необходимую dll для работы zmq. Имя dll на текущий момент можно уточнить во время возникновения ошибки.
