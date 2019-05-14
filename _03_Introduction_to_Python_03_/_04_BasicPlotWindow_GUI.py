#Import the necessary libraries
from PyQt5.QtWidgets import (QApplication,
                             QMainWindow,
                             QWidget,
                             QMessageBox,
                             QPushButton,
                             QGridLayout,
                             QSizePolicy
                             )
from PyQt5.QtCore import Qt, QCoreApplication

import random
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import matplotlib.pyplot as plt

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
        
        self.plot_area = PlotCanvas(self, width=5, height=4)
        window_layout.addWidget(self.plot_area,1,0,1,1)
        
        self.show()
        self.update_graph()

    def update_graph(self):
        self.plot_area.axes.clear()
        self.plot_area.data = self.generate_data()
        self.plot_area.plot()


    def generate_data(self,N=25):
        return [random.random() for i in range(N)]

class PlotCanvas(FigureCanvas):

    def __init__(self, parent=None, width=5, height=4, dpi=100):
        fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = fig.add_subplot(111)
        self.axes.set_title('PyQt Matplotlib Example')
        
        FigureCanvas.__init__(self, fig)
        self.setParent(parent)

        FigureCanvas.setSizePolicy(self,
                QSizePolicy.Expanding,
                QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)
        self.data = []


    def plot(self):
        #ax = self.figure.add_subplot(111)
        self.axes.plot(self.data, 'r-')
        self.draw()


# This line is run when the to get everything started.      
if __name__ == '__main__':
    app = QApplication([]) #The empty list ([]) is passed inplace of system arguments.
    execute = MainWindow() #Calls the main window class we defined earlier.
    app.exec_() #this starts the event handling loop to accept interaction.