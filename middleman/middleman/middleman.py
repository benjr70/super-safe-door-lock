import serial
import serial.tools.list_ports
import mySQLdb
fob = 00000000
keypad = '0000'
ports = list(serial.tools.list_ports.comports())
db = MySQLdb.connect("localhost","testuser","test123","TESTDB" )
sql = "INSERT INTO TABLE(FOB, KEYPAD) VALUES (%d ,%s)" % (fob, keypad)
print ports[0].device
ser = serial.Serial(ports[0].device,9600)
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