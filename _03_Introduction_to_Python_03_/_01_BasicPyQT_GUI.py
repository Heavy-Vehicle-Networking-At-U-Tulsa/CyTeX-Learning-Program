#Import the necessary libraries
from PyQt5.QtWidgets import (QApplication,
                             QMainWindow,
                             QWidget,
                             QMessageBox,
                             QPushButton,
                             QGridLayout
                             )
from PyQt5.QtCore import Qt, QCoreApplication

import serial
import serial.tools.list_ports
import queue
import threading
import time

class SerialRead(threading.Thread):
    def __init__(self, rx_queue, serial_port):
        threading.Thread.__init__(self)
        self.runSignal = True
        self.ser = serial.Serial(port=serial_port, baudrate=4800)

    def run(self):
        while self.runSignal:
            print(self.ser.read())
        print("Done with Serial Run Thread.")    

class MainWindow(QMainWindow):
    def __init__(self):
        #The super command makes sure the inhereted class is also initiated. 
        super().__init__()
        self.setWindowTitle('Serial Port Viewer');
        
        #Define a main widget that will contain all the other widgets and set
        #it as the central widget. 
        main_widget = QWidget(self)
        self.setCentralWidget(main_widget)

        window_layout = QGridLayout(main_widget)
        serial_button =  QPushButton("Connect Serial")
        serial_button.clicked.connect(self.connect_serial)
        #assign the label to the grid.
        window_layout.addWidget(serial_button,0,0,1,1)
        
        
        self.show()

    def connect_serial(self,serial_port):
        self.rx_queue = queue.Queue(10000)
        self.serial_thread = SerialRead(self.rx_queue,"COM6")       
        self.serial_thread.setDaemon(True) #needed to close the thread when the application closes.
        self.serial_thread.start()
    
    def closeEvent(self, event):
        result = QMessageBox.question(self, "Confirm Exit",
            "Are you sure you want to quit the program?",
            QMessageBox.Yes | QMessageBox.No,
            QMessageBox.Yes)
        if result == QMessageBox.Yes:
            self.serial_thread.runSignal = False
            event.accept()
        else:
            event.ignore()



# This line is run when the to get everything started.      
if __name__ == '__main__':
    app = QApplication([]) #The empty list ([]) is passed inplace of system arguments.
    execute = MainWindow() #Calls the main window class we defined earlier.
    app.exec_() #this starts the event handling loop to accept interaction.