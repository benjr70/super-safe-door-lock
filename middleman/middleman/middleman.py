import serial
import serial.tools.list_ports
import mysql.connector
fob = 00000000
keypad = '0000'
ports = list(serial.tools.list_ports.comports())
db = mysql.connector.connect(user = "Datatest",password = "THANh123",host = "datatest.cmuftxtjbxoj.us-east-1.rds.amazonaws.com",database = "datatest" )
sql = "INSERT INTO TABLE(FOB, KEYPAD) VALUES (%d ,%s)" % (fob, keypad)
print ports[0].device
ser = serial.Serial(ports[0].device,9600)
print 'test'
while(True):
    line = ser.readline() #read from arduino
    if len(line) == 4:
        keypad = line
    else:
        fob = line;
    try:
        # Execute the SQL command
        cursor.execute(sql)
        # Commit your changes in the database
        db.commit()
    except:
        # Rollback in case there is any error
        db.rollback()

    #ser.write() //write that to arduino
    print line