from machine import  ADC, Pin
from time import sleep
import time

moisture_adc = ADC(Pin(26))
pump_pin = Pin(16, Pin.OUT)
moisture_lvl = 53000; #set max moisture lvl level here



def loop():
    while True:

        if moisture_adc.read_u16() > moisture_lvl:
            #print (moisture_adc.read_u16(), "sad plant")
            water()
        elif moisture_adc.read_u16() < moisture_lvl:
            #print (moisture_adc.read_u16(), "happy plant")
            pump_pin.value(1)
            time.sleep(1800)
            

def water():

    newMoisture_lvl = moisture_lvl - 5000 #set min water moisture lvl here
    if moisture_adc.read_u16() >= newMoisture_lvl:
        #print(moisture_adc.read_u16(), "water flowing")
        pump_pin.value(0)
        time.sleep(5)
    elif moisture_adc.read_ucs16() <= newMoisture_lvl:
        #print(moisture_adc.read_u16(), "water flow halted")
        pump_pin.value(1)
        return

           
def destroy():
    pump_pin.value(1)


if __name__ == '__main__':
    try:
        loop()
    except KeyboardInterrupt:
        destroy()






