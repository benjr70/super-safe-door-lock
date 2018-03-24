import serial
import serial.tools.list_ports
import mysql.connector
import datetime
import time

fob ="00000000"
keypad = "0000"
count = 0;
ports = list(serial.tools.list_ports.comports())
db = mysql.connector.connect(user = "Datatest",password = "THANh123",host = "datatest.cmuftxtjbxoj.us-east-1.rds.amazonaws.com",database = "datatest" )
#sql = "INSERT INTO safedoortable (keypad, fob,phonekey,access, time) VALUES (%s ,%s, null, null, null);" % (keypad, fob)
print ports[0].device
x= db.cursor()
ser = serial.Serial(ports[0].device,9600)
phonecodetest = 'n'
while(True):
    line = ser.readline() #read from arduino
    if len(line) == 7 and phonecodetest == 'n':
        keypad = line
        print 'keypad' + keypad
        fob = ''
        phonecodetest = 'p'
    elif phonecodetest == 'n':
        fob = line;
        keypad = ''
        print 'fob' + fob
        phonecodetest = 'p'
    time.sleep(25)
    line = ser.readline() #read from arduino
    if phonecodetest == 'p':
        phonecode = line
        print 'phone code ' + phonecode
        phonecodetest = 'e'
    ts = datetime.datetime.now()
    print ts
    try:
        # Execute the SQL command
        if(phonecodetest == 'e'):
            x.execute("INSERT INTO safedoortable (keypad, fob,phonekey,access, time) VALUES (%s ,%s, %s, null, %s);",(keypad, fob, phonecode, ts))
            # Commit your changes in the database
            db.commit()
            print'sql executed'
            phonecodetest = 'n'
    except:
        # Rollback in case there is any error

        db.rollback()
        print 'sql failed'

    #ser.write() //write that to arduino
    print line