import os
import serial

PORT = "COM5"
RESET_BAUD = 38400
PROGRAM_BAUD = 9600
RESET_FRAME = [0x04, 0x01, 0x00, 0x02, 0x02, 0x01, 0x02, 0x08, 0x05]

ser = serial.Serial(PORT, RESET_BAUD)
ser.write(RESET_FRAME)
ser.close()
os.system(f"avrdude -p atmega8 -b {PROGRAM_BAUD} -P {PORT} -c arduino -U flash:w:.pio\\build\ATmega328\\firmware.hex:i")