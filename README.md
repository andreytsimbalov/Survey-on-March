Survey on March

Все данные относятся к survey файлам для Nanomsg. Всё необходимое для ZeroMQ уместится в данном Readme.

Nanomsg:

Поместить все данные необходимо в папку C:\Users\SG\Downloads\nanomsg-master
Код программы: ..\build\nanomsq.sln(заточено под VS15)
Готовый survey.exe файл лежит в ..\build\Debug

Суть программы: есть Опросник и 3 клиента.  Опросник посылает запрос ABC всем клиентам и выставляет неодходимый deadline(возможное время для ответа), в который клиентам необходимо уложиться для ответа(принимают они ABC, а отправляют DEF). Здесь представлен частный случай, где 1 и 2 клиенты успели дать ответ, а 3 клиент нет.

ZeroMQ:

Данная библиотека не поддерживает survey, однако здесь есть схожий для него PUBSUB.

Для запуска необходимо иметь python, и установить для него zmq(ввести в консоли pip install pyzmq)

Клиент

import zmq
context = zmq.Context()
socket = context.socket(zmq.SUB)
socket.connect('tcp://127.0.0.1:2000')
socket.setsockopt_string(zmq.SUBSCRIBE, '')
message = socket.recv_pyobj()
print(message.get(1)[0])

Публишер

import time
import zmq
context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind('tcp://127.0.0.1:2000')
time.sleep(1)
socket.send_pyobj({1:[7,12,0]})

Далее открываем два окна python: клиент и паблишер. Сначала копируем клиент в первое окно(на "message = socket.recv_pyobj()" программа войдёт в режим ожидания), затем копируем во второе паблишер, который передаст данные клиенту. В итоге клиент выведет первый элемент полученного массива(в данном случае 7). Можно создать несколько клиентов, они все получат один и тот же массив данных.
