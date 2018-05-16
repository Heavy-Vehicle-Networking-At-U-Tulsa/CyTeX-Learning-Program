# -*- coding: utf-8 -*-
"""
Wheel-Based Vehicle Speed Parser

This file parses through Kewworth bus traffic
and sorts out Wheel-Based Vehicle Speed
and then graphs it vs time.
"""
#The values that we are pulling are in Hexadecimal 
import matplotlib.pyplot as plt
t_abs=[]                                                                    #These are the Absolute Time Values
t_rel=[]                                                                    #These are the Relative Time Values
wbv_speed_hex=[]
wbv_speed_int=[]                                                                #This list contains Wheel-Based Vehicle Speed in Hex
wbv_speed_kmh=[]                                                            #This list contains Wheel-Based Vehicle Speed in kilometers per hour
wbv_speed_mph=[]
with open(                                                                      #The "with open" command opens the Kenworth Data file to be parsed through and names it CAN_data
'Bus Traffic_KENWORTH_DRIVE AROUND 12-09-2015 12-09-2015 4-26-05 pm.csv', 'r'
) as CAN_data:                                                                  #This creates the CAN_data variable, which is much easier to type.For every line in the CAN_data .csv file, we want to generate a list of the values for the speed and time. Two separate lists that have common indicies can be graphed against eachother
                                                                #This list contains Wheel-Based Vehicle SPeed in miles per hour
    for line in CAN_data:                                                       #This for loop goes through every line in the imported .csv file
        sp_line = line.split(',')                                               #This step splits the line at every comma, creating a list instead of a very long string
        if sp_line[9]=='18FEF100':                                              #This if statement is true if the 10th column (9 in python since it starts at zero) contains '18FEF100'. 'FEF1' is the Wheel-Based Speed Identifier and '00' is the engine transmitter code, so its coming from the engine
            t_abs.append(float(sp_line[1]))                                     #t_abs is a list of the absolute times at every instance where the if statement is true. In other words, this logs the time at every point that the engine communicates Wheel-Based Speed
            t_rel.append(float(sp_line[2]))                                     #t_rel is the same as t_abs except it logs relative times
            byte_2=sp_line[13]
            byte_3=sp_line[14]
            if len(byte_2)==1:
                byte_2 = '0'+byte_2
            if len(byte_3)==1:
                byte_3='0'+byte_3
            hex_speed = (byte_3+byte_2)
            wbv_speed_hex.append(hex_speed)                                         #Column 15 and 14 in the .csv document correspond to the 3rd and 2nd bytes, respectively. Because this data is communicated in reverse byte order, we have to create a combined string of the 3rd and the 2nd bytes
    count = 0                                                                   #This counter is important for the following for loop, as it makes the indicies common between speed and time
    for speed in wbv_speed_hex:                                                     #This for loop goes through teh wbv_speed list created in the previous for loop. The previous for loop is in hex, and we need an output in distance vs time
        wbv_speed_int.append(int(speed, 16))                                         #For every value of wbv_speed, this line converts it from hex into integers
        wbv_speed_kmh.append(wbv_speed_int[count]/256.)                             #Every bit equals 1/256 kilometers per hour. This line converts the integer amount of bits into kilometers per hour
        wbv_speed_mph.append(wbv_speed_kmh[count]/1.60934)                      #This is America, and we use Freedom Units, so we need to convert into Miles per Hour by the conversion ration of 1 mile to every 1.60934 km
        count +=1                                                               #We need to advance the count to have the for loop continue
plt.plot(t_abs, wbv_speed_kmh)                                                  #Generates a plot of the two lists, compared via indicies
plt.xlabel("Absolute Time "+"(Seconds)")
plt.ylabel("Wheel-Based Vehicle Speed "+"(Kilometers Per Hour)")
plt.show()                                                                      #Prints the graph

#Here on down is the gui code
import tkinter import *
class optionWindow(object):
    top=self.top=TopLevel(master)
    self.l=Label('File:')
    self.l
    