#Import the necessary libraries
from PyQt5.QtWidgets import (QApplication,
                             QMainWindow,
                             QWidget,
                             QMessageBox,
                             QPushButton,
                             QGridLayout,
                             QSizePolicy
                             )
from PyQt5.QtCore import Qt, QCoreApplication, QTimer

import pyqtgraph as pg

import random

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
        serial_button =  QPushButton("Generate")
        serial_button.clicked.connect(self.update_graph)
        #assign the label to the grid.
        window_layout.addWidget(serial_button,0,0,1,1)
        
        self.graph_data = []

        self.graph = pg.PlotWidget(title="Updating Graph")
        self.graph.setWindowTitle("Updating Graph Title")
        #self.graph.setYRange(9, 15)
        self.graph.setScale(1)
        labelStyle = {'color': '#FFF', 'font-size': '14pt'}
        self.graph.setLabel('bottom','Samples',**labelStyle)
        self.graph.setLabel('left','Voltage','V',**labelStyle)
        self.graph.showGrid(True, True, alpha=.5)
        self.graph.addLegend()
        self.data_plot = self.graph.plot(self.graph_data, 
                        symbol =  's',
                        name = "Random Data")
        self.show()
        self.graph.show()

        self.timer = QTimer()
        self.timer.timeout.connect(self.update_graph)
        self.timer.start(100) #milliseconds

    def update_graph(self):
        self.graph_data.append(random.random())
        if len(self.graph_data) > 100:
            self.graph_data.pop(0)
        self.data_plot.setData(self.graph_data)
        self.graph.show()
        
    

# This line is run when the to get everything started.      
if __name__ == '__main__':
    app = QApplication([]) #The empty list ([]) is passed inplace of system arguments.
    execute = MainWindow() #Calls the main window class we defined earlier.
    app.exec_() #this starts the event handling loop to accept interaction.