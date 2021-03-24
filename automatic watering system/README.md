- Automatic watering system
written with micropython


moisture_lvl = the max dry limit in the soil
newMoisture_lvl = the min wet limit before the pump stops.
In this program example the water pump stops at 47000 moisture lvl and
returns.



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







