from ctypes import *
from ctypes.wintypes import HWND
import struct

BLOCKING_IO                =                    1  ## For Blocking calls to send/read.
NON_BLOCKING_IO            =                    0  ## For Non-Blocking calls to send/read.

RP1210_Set_All_Filters_States_to_Pass = 3

dll_name = 'DGDPA5MA.DLL'
RP1210DLL = windll.LoadLibrary(dll_name)

# Define windows prototype functions:
prototype = WINFUNCTYPE(c_short, HWND, c_short, c_char_p, c_long, c_long, c_short)
RP1210_ClientConnect = prototype(("RP1210_ClientConnect", RP1210DLL))

prototype = WINFUNCTYPE(c_short, c_short)
RP1210_ClientDisconnect = prototype(("RP1210_ClientDisconnect", RP1210DLL))

prototype = WINFUNCTYPE(c_short, c_short,  POINTER(c_char*2000), c_short, c_short, c_short)
RP1210_SendMessage = prototype(("RP1210_SendMessage", RP1210DLL))

prototype = WINFUNCTYPE(c_short, c_short, POINTER(c_char*2000), c_short, c_short)
RP1210_ReadMessage = prototype(("RP1210_ReadMessage", RP1210DLL))

prototype = WINFUNCTYPE(c_short, c_short, c_short, POINTER(c_char*2000), c_short)
RP1210_SendCommand = prototype(("RP1210_SendCommand", RP1210DLL))

prototype = WINFUNCTYPE(c_short, c_short, POINTER(c_char*17), POINTER(c_char*17), POINTER(c_char*17))
RP1210_ReadDetailedVersion = prototype(("RP1210_ReadDetailedVersion", RP1210DLL))

deviceID = 2
protocol_bytes = b'J1939:Baud=Auto'

nClientID = RP1210_ClientConnect(HWND(None), 
                                c_short(deviceID), 
                                protocol_bytes, 
                                0, 0, 0)         
print("Client ID is {}".format(nClientID))

chAPIVersionInfo    = (c_char*17)()
chDLLVersionInfo    = (c_char*17)()
chFWVersionInfo     = (c_char*17)()
return_value = RP1210_ReadDetailedVersion(c_short(nClientID),
                                        byref(chAPIVersionInfo),
                                        byref(chDLLVersionInfo),
                                        byref(chFWVersionInfo))
if return_value == 0 :
    message = 'The PC computer has successfully connected to the RP1210 Device.\nThere is no need to check your USB connection.\n'
    DLL = chDLLVersionInfo.value
    API = chAPIVersionInfo.value
    FW = chAPIVersionInfo.value
    message += "DLL = {}\n".format(DLL.decode('ascii','ignore'))
    message += "API = {}\n".format(API.decode('ascii','ignore'))
    message += "FW  = {}".format(FW.decode('ascii','ignore'))
else:
    message = "RP1210_ReadDetailedVersion failed with\na return value of  {}: {}".format(return_value,self.get_error_code(return_value))
print(message)

return_value = RP1210_SendCommand(c_short(RP1210_Set_All_Filters_States_to_Pass), 
                                       c_short(nClientID),
                                       None, 0)
if return_value == 0:
    print("RP1210_Set_All_Filters_States_to_Pass for {} is successful.".format(protocol_bytes))

ucTxRxBuffer = (c_char * 2000)()
for i in range(100):
    print(i)
    return_value = RP1210_ReadMessage(c_short(nClientID),
                                      byref(ucTxRxBuffer),
                                      c_short(2000),
                                      c_short(BLOCKING_IO))
    if return_value > 0:
        timestamp = struct.unpack("<L", ucTxRxBuffer[0:4])[0]
        # Echo command not used\
        pgn = struct.unpack("<L", ucTxRxBuffer[4:7] + b'\x00')[0]
        how_priority = struct.unpack("B",ucTxRxBuffer[7])[0]
        sa = struct.unpack("B",ucTxRxBuffer[8])[0]
        da = struct.unpack("B",ucTxRxBuffer[9])[0]
        data = ucTxRxBuffer[10:return_value]
        print("J1939 RX PGN: {} (0x{:04X}) from source {}".format(pgn,pgn,sa))
        print(data)

RP1210_ClientDisconnect(nClientID)