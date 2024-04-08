import time
from machine import Pin, UART
#La primirea caracterului curent pe UART, se afiseaza ledul corespunzător. Daca se apasa de doua ori acelasi buton, se opreste ledul curent.
led_life=Pin(25, Pin.OUT)
led_life.value(1)
led = Pin(19, Pin.OUT)
led1 = Pin(20, Pin.OUT)
led2 = Pin(21, Pin.OUT)
led.value(0)
led1.value(0)
led2.value(0)
uart = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1))
uart.init(9600, bits=8, parity=None, stop=1)
while True:
    data = uart.read()
    if data == b'R':
        led.value(not led.value())
    elif data == b'G':
        led1.value(not led1.value())
    elif data == b'B':
        led2.value(not led2.value())

