Survey on March

��� ������ ��������� � survey ������ ��� Nanomsg. �� ����������� ��� ZeroMQ ��������� � ������ Readme.

Nanomsg:

��������� ��� ������ ���������� � ����� C:\Users\SG\Downloads\nanomsg-master
��� ���������: ..\build\nanomsq.sln(�������� ��� VS15)
������� survey.exe ���� ����� � ..\build\Debug

���� ���������: ���� �������� � 3 �������.  �������� �������� ������ ABC ���� �������� � ���������� ����������� deadline(��������� ����� ��� ������), � ������� �������� ���������� ��������� ��� ������(��������� ��� ABC, � ���������� DEF). ����� ����������� ������� ������, ��� 1 � 2 ������� ������ ���� �����, � 3 ������ ���.

ZeroMQ:

������ ���������� �� ������������ survey, ������ ����� ���� ������ ��� ���� PUBSUB.

��� ������� ���������� ����� python, � ���������� ��� ���� zmq(������ � ������� pip install pyzmq)

������

import zmq
context = zmq.Context()
socket = context.socket(zmq.SUB)
socket.connect('tcp://127.0.0.1:2000')
socket.setsockopt_string(zmq.SUBSCRIBE, '')
message = socket.recv_pyobj()
print(message.get(1)[0])

��������

import time
import zmq
context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind('tcp://127.0.0.1:2000')
time.sleep(1)
socket.send_pyobj({1:[7,12,0]})

����� ��������� ��� ���� python: ������ � ��������. ������� �������� ������ � ������ ����(�� "message = socket.recv_pyobj()" ��������� ����� � ����� ��������), ����� �������� �� ������ ��������, ������� �������� ������ �������. � ����� ������ ������� ������ ������� ����������� �������(� ������ ������ 7). ����� ������� ��������� ��������, ��� ��� ������� ���� � ��� �� ������ ������.
