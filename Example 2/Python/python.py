import serial     #Importing necessary libraries
import python_pb2 as data  
from cobs import cobs
import keyboard
  
      #Initializing logs count number
iflag = 0
rflag = 0
cflag = 0
count = 0

while True:
  ser = serial.Serial('/dev/ttyACM0', 9600)

  def DATA():
       
    try:
      
      data_obj = data.Data()                   # Create an object for the class Data
      commandack_obj = data.commandAck()
      byte_string = ser.read_until(expected = b'\x00', size = 80)    # Read until zero-byte (de-limiting)
      cobs_decoded = cobs.decode(byte_string[:-1])           # Decode the cobs encoded byte string
      commandack_obj.ParseFromString(cobs_decoded)       # Decode cobs decoded byte string using Protobufs 
      print(commandack_obj)
    #  print(byte_string)
      byte_string = ser.read_until(expected = b'\x00', size = 80)    # Read until zero-byte (de-limiting)
      cobs_decoded = cobs.decode(byte_string[:-1])           # Decode the cobs encoded byte string
      data_obj.ParseFromString(cobs_decoded)       # Decode cobs decoded byte string using Protobufs 
      print(data_obj)   # Print the data log on to the screen
     # print(byte_string)
      
            
    except:     
       
      byte_string = ser.read_until(expected = b'\x00', size = 80)    # Read until zero-byte (de-limiting)
      cobs_decoded = cobs.decode(byte_string[:-1])           # Decode the cobs encoded byte string
      commandack_obj.ParseFromString(cobs_decoded)       # Decode cobs decoded byte string using Protobufs 
      print(commandack_obj)
   #   print(byte_string)
            	   
      byte_string = ser.read_until(expected = b'\x00', size = 80)    # Read until zero-byte (de-limiting)
      cobs_decoded = cobs.decode(byte_string[:-1])           # Decode the cobs encoded byte string
      data_obj.ParseFromString(cobs_decoded)       # Decode cobs decoded byte string using Protobufs 
      print(data_obj) 
    #  print(byte_string)
      

  def command_encode(i):
 
    command_obj = data.command()
    if (i == 1):
      command_obj.commandtype = 1
      command_obj.datas = "i"
      command_byte = command_obj.SerializeToString()
      ser.write(command_byte)

    if (i == 2):
      command_obj.commandtype = 2
      command_obj.datas = "r"
      command_byte = command_obj.SerializeToString()
      ser.write(command_byte)
     
    if (i == 3):
      command_obj.commandtype = 3
      command_obj.datas = "c"
      command_byte = command_obj.SerializeToString()
      ser.write(command_byte)
    

  count = count + 1
  print(count)
  DATA()

  if iflag == 0 and keyboard.is_pressed('i'):
      command_encode(1)
      iflag = 1
      rflag = 0
      cflag = 0
      
  if rflag == 0 and keyboard.is_pressed('r'):
      command_encode(2)
      iflag = 0
      rflag = 1
      cflag = 0  
      
  if cflag == 0 and keyboard.is_pressed('c'):
      command_encode(3)
      iflag = 0
      rflag = 0
      cflag = 1

