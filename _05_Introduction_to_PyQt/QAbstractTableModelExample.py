from PyQt5.QtWidgets import (QMainWindow,
                             QWidget,
                             QTreeView,
                             QMessageBox,
                             QFileDialog,
                             QLabel,
                             QSlider,
                             QCheckBox,
                             QLineEdit,
                             QVBoxLayout,
                             QApplication,
                             QPushButton,
                             QTableWidget,
                             QTableView,
                             QTableWidgetItem,
                             QScrollArea,
                             QAbstractScrollArea,
                             QAbstractItemView,
                             QSizePolicy,
                             QGridLayout,
                             QGroupBox,
                             QComboBox,
                             QAction,
                             QDockWidget,
                             QDialog,
                             QFrame,
                             QDialogButtonBox,
                             QInputDialog,
                             QProgressDialog,
                             QTabWidget)
from PyQt5.QtCore import Qt, QTimer, QAbstractTableModel, QCoreApplication, QSize
from PyQt5.QtGui import QIcon,QBrush
import sys

service_identifier = { 0x7F: "Negative Response", 
                       0x10: "Diagnostic Session Control", 
                       0x11: "ECU Reset", 
                       0x27: "Security Access", 
                       0x22: "Read Data By Identifier", 
                       0x28: "Communication Control",
                       0x3E: "Tester Present", 
                       0x83: "Access Timing Parameter",
                       0x84: "Secure Data Transmission", 
                       0x85: "Control DTC Setting", 
                       0x31: "Routine Control", 
                       0x86: "Response On Event",
                       0x87: "Link Control",
                       0x23: "Read Memory By Address",
                       0x24: "Read Scaling Data By Identifier",
                       0x2A: "Read Data By Periodic Identifier",
                       0x2C: "Dynamically Define Data Identifier",
                       0x2E: "Write Data By Identifier",
                       0x3D: "Write Memory By Address",
                       0x14: "Clear Diagnostic Information",
                       0x19: "Read DTC Information",
                       0x2F: "Input Output Control By Identifier",
                       0x34: "Request Download",
                       0x35: "Request Upload",
                       0x36: "Transfer Data",
                       0x37: "Request Transfer Exit",
                       0x38: "Request File Transfer"
    }

keys = []
values = []
colors = ['red', 'green', 'yellow', 'red', 'green', 'green', 'green', 'green', 'yellow', 'yellow', 'green',
 'green', 'yellow', 'green', 'green', 'green', 'green', 'red', 'red', 'red', 'yellow', 'yellow', 'green', 
 'green', 'yellow', 'green', 'green']

length = len(service_identifier)

for k,v in service_identifier.items():
    #print(k, 'corresponds to', v)
    keys.append(k)
    values.append(v)

#print(values)
#print(keys)

table_values = []

for i in range(length):
    table_values.append([keys[i],values[i]])

print(table_values)

class Model(QAbstractTableModel):
    def __init__(self, parent=None): 
        super(Model, self).__init__(parent)

        self._data = table_values

    def rowCount(self, parent):
        return len(self._data)

    def columnCount(self, parent):
        return len(self._data[0])

    def data(self, index, role):
        if index.isValid():
            data = self._data[index.row()][index.column()]

            if role in [Qt.DisplayRole]:
                return data

            if role == Qt.BackgroundRole:

                y = index.row()
                
                if colors[y] == 'red':
                    return QBrush(Qt.red)
                elif colors[y] == 'yellow':
                    return QBrush(Qt.yellow)
                else:
                    return QBrush(Qt.green)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    t = QTableView()
    m = Model(t)
    t.setModel(m)
    t.show()

    sys.exit(app.exec_())