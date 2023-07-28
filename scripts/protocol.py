import argparse
import socket
from struct import pack


def encrypt(string):
    key = 171
    result = pack(">I", len(string))
    for i in string:
        a = key ^ ord(i)
        key = a
        result += bytes([a])
    return result


def decrypt(string):
    key = 171
    result = ""
    for i in string:
        a = key ^ i
        key = i
        result += chr(a)
    return result


HOST = "10.0.100.109"
PORT = 9999
# COMMAND = """{"smartlife.iot.smartbulb.lightingservice":{"transition_light_state":{"ignore_default":1,"transition_period":500,"mode":"normal","hue":0,"on_off":1,"saturation":100,"color_temp":0,"brightness":100}}}"""

COMMAND = """{"system":{"reset":{"delay":1}}}"""

TIMEOUT = 10


try:
    sock_tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock_tcp.settimeout(TIMEOUT)
    sock_tcp.connect((HOST, PORT))
    sock_tcp.settimeout(None)
    sock_tcp.send(encrypt(COMMAND))
    data = sock_tcp.recv(2048)
    sock_tcp.close()

    decrypted = decrypt(data[4:])

    print(decrypted)

except socket.error:
    quit(f"Could not connect to host {HOST}:{PORT}")
