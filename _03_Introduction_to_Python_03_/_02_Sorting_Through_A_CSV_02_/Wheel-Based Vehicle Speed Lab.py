"""
In this lab we will be using the knowledge that you gained following the code academy tutorial to sort through a csv filled with CAN data.
To begin, open the csv inside of this document. it should be labelled KENWORTH_DRIVE AROUND. This was recorded at MHC Kenworth in Sapulpa.
We are trying to parse through this data using the J1939 csv. It is quicker to have someone explain to you how to use this document.

Within the cs1939 csv file, located in this same folder, determine the PGN where "Wheel-based Vehicle Speed" is contained. The csv is
already set up for filtering therefore it should be as quick as a copy and paste to find this information.

You will also need to note the position of the bytes that hold the wheel-based vehicle speed information. Verify that the pos. value is 2-3.

You can then use the PGN to determine which messages hold the vehicle speed. -- 0x18FEF100 (If you were not able to come up with this, please
revisit the CAN Bus basics powerpoint, or ask for help from a friend.)

So, what are we actually trying to do? We are trying to read through the csv and output a graph that shows the vehicle speed vs. time.

Now we know that the vehicle speed is located in the 2-3 byte of the message ID'd 0x18FEF100. We can extract the vehicle data from here. We also
need the time associated with these speed points. Conveniently this information is located in each line of the csv file as well. 

It is also important to note the resolution of the bits (1/256 kph/bit) and that the speed is read in kph not mph by default. This will be needed
to help translate from the binary/hex values to the speed values. 

Have fun, 

-Maintenance

--------------------------------------------------------------------------------------------------------------------------------------------------
"""


# -*- coding: utf-8 -*-
"""
Wheel-Based Vehicle Speed Parser

This file parses through Kewworth bus traffic
and sorts out Wheel-Based Vehicle Speed
and then graphs it vs time.

Originally written by: Ben Ettlinger
Modified by: Hayden Allen
"""

#The values that we are pulling are in Hexadecimal

#need to import the library that will allow us to develop a plot. 
import matplotlib.pyplot as plt

#these are lists where we will store the data as its read
t_abs=[]                                                                        #These are the Absolute Time Values
t_rel=[]                                                                        #These are the Relative Time Values
wbv_speed_hex=[]
wbv_speed_int=[]                                                                #This list contains Wheel-Based Vehicle Speed in Hex
wbv_speed_kmh=[]                                                                #This list contains Wheel-Based Vehicle Speed in kilometers per hour
wbv_speed_mph=[]                                                                #This list contains Wheel-Based Vehicle Speed in miles per hour


#import the file
with open(                                                                      #The "with open" command opens the Kenworth Data file to be parsed through and names it CAN_data
'filename here', 'r'                                                            #file name needs to be input here. (the 'r' means you are opening it with read-only permissions)
) as CAN_data:                                                                  #This creates the CAN_data variable, which is much easier to type.For every line in the CAN_data .csv file, we want to generate a list of the values for the speed and time. Two separate lists that have common indicies can be graphed against eachother
                                                                                
    for line in CAN_data:                                                       #This for loop goes through every line in the imported .csv file
        sp_line = line.split('delimiter')                                       #change the delimiter for the delimiter of a .csv file. This step splits the line at every comma, creating a list instead of a very long string (because it is a csv file. sometime the delimiter will be '/t' for a .tsv file or tab seperated value since commas can be used as part of a string number
        if sp_line[9]=='ID':                                                    #input the ID you think you should be looking for here. This if statement is true if the 10th column (9 in python since it starts at zero) contains '18FEF100'. 'FEF1' is the Wheel-Based Speed Identifier and '00' is the engine transmitter code, so its coming from the engine
            t_abs.append(float(sp_line[1]))                                     #t_abs is a list of the absolute times at every instance where the if statement is true. In other words, this logs the time at every point that the engine communicates Wheel-Based Speed
            t_rel.append(float(sp_line[2]))                                     #t_rel is the same as t_abs except it logs relative times
            byte_2=sp_line[13]                                                  #grabbing the hex value for byte 2
            byte_3=sp_line[14]                                                  #grabbing the hex value for byte 3
            if len(byte_2)==1:                                                  #because the values are intrepretted as strings, there are no leading zeroes, therefore you need to add a zero before numbers that are only half a byte. 
                byte_2 = '0'+byte                                               #adding of the leading zero
            if len(byte_3)==1:                                                  #same thing
                byte_3='0'+byte_3                                               #leading zero
            hex_speed = (byte_3+byte_2)                                         #Column 15 and 14 in the .csv document correspond to the 3rd and 2nd bytes, respectively. Because this data is communicated in reverse byte order, we have to create a combined string of the 3rd and the 2nd bytes
            wbv_speed_hex.append(hex_speed)                                     #then you need to store this value in a list. 
    count = 0                                                                   #This counter is important for the following for loop, as it makes the indicies common between speed and time
    for speed in wbv_speed_hex:                                                 #This for loop goes through teh wbv_speed list created in the previous for loop. The previous for loop is in hex, and we need an output in distance vs time
        wbv_speed_int.append(int(speed, 16))                                    #For every value of wbv_speed, this line converts it from hex into integers
        wbv_speed_kmh.append(wbv_speed_int[count]/256.)                         #Every bit equals 1/256 kilometers per hour. This line converts the integer amount of bits into kilometers per hour
        wbv_speed_mph.append(wbv_speed_kmh[count]/1.60934)                      #This is America, and we use Freedom Units, so we need to convert into Miles per Hour by the conversion ration of 1 mile to every 1.60934 km
        count +=1                                                               #We need to advance the count to have the for loop continue
#output the graph (consult online documention for the plt.plot function
