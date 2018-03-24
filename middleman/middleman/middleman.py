import serial
import serial.tools.list_ports
import requests

ports = list(serial.tools.list_ports.comports())
url = ''

print ports[0].device
ser = serial.Serial(ports[0].device,115200)
while(True):
    line = ser.readline()
    r = requests.post(url, data=line)
    print line