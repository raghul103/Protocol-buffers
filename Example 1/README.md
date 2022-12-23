## Problem Statement:
   ESP32 sends the data logs to client (python) using serial communication.
## Protobuf encoding-decoding:
   The data is encoded using nanopb in the server side (ESP32) and the data received by client is dedoded using google protobufs.  
## COBS encoding-decoding:
   Protocol buffers does not support de-limiting characters at the end of a data packet. So we again encode the protobuf encoded bitstream using COBS Algorithm. This is known as COBS encoding.
   Reference: https://blog.mbedded.ninja/programming/serialization-formats/consistent-overhead-byte-stuffing-cobs/
## Data Flow:
   Data in ESP32 ----> Protobuf encoding -----> COBS encoding -----> COBS decoding -----> Protobuf decoding 
                           (ESP32)                  (ESP32)            (client)               (client)
