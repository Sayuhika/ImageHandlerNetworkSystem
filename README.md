# ImageHandlerNetworkSystem
UNN study project with ZMQ and Bitsery

# APPs:
1) **WebCamServer** (wcs-app)
* Занимается получением изображений с камеры и отправкой их на **ImageHandler**.
2) **ImageHandler** (ih-app)
* Получает изображения из приложения **WebCamServer** и обрабатывает их. После обработки отправляет исходное изображение и обработанное в приложение **ImageCollectorServer**.
3) **ImageCollectorServer** (ics-app)
* Собирает обработанные изображения и сохраняет их в видео \ выводит на экран. В зависимости от реализации, которая будет осуществлена.

# After clone:
Открыть терминал в корне проекта и выполнить следующие команды:
* **git submodule update --init --recursive**