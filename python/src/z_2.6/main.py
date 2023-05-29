import numpy as np
from PyQt6 import uic, QtWidgets
from PyQt6.QtGui import QStandardItem, QStandardItemModel
from PyQt6.QtWidgets import QApplication, QFileDialog, QInputDialog, QCheckBox, QWidget
import sys
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from function.read_data import read_html, read_excel
from datetime import datetime


class NewWindow(QWidget):
    def __init__(self, x, y, column1, column2, data, parent, dateTo, dateFrom):
        super().__init__()

        self.data = data
        self.parent = parent
        self.setWindowTitle("PlotWindow")
        self.setGeometry(200, 200, 800, 600)

        self.figure = plt.figure()
        self.canvas = FigureCanvas(self.figure)

        layout = QtWidgets.QHBoxLayout(self)
        layout.addWidget(self.canvas)
        self.tableView = QtWidgets.QTableView(self)
        layout.addWidget(self.tableView)
        self.dateTo = dateTo
        self.dateFrom = dateFrom
        self.haveDate = False

        self.plot_data(x, y, column1, column2)
        self.set_table_data(data)
        if self.haveDate:
            if self.data[column2].dtype == 'datetime64[ns]':
                self.plot_bar_chart(column1)
            else:
                self.plot_bar_chart(column2)

    def is_valid_date(self, date_string):
        try:
            datetime.strptime(date_string, "%Y-%m-%d %H:%M:%S")
            return True
        except ValueError:
            return False

    def plot_data(self, x, y, column1, column2):
        ax = self.figure.add_subplot(211)
        ax.scatter(x, y)
        ax.set_xlabel(column1)
        ax.set_ylabel(column2)
        ax.set_title("Scatter Plot")
        self.canvas.draw()

    def plot_bar_chart(self, column):
        temp = self.data.copy()
        for_diagram = temp.groupby(temp['InvoiceDate'].dt.weekday)[column].sum()
        self.figure.subplots_adjust(hspace=1)
        ax = self.figure.add_subplot(212)
        for_diagram.index = for_diagram.index.map({0: 'Monday', 1: 'Tuesday', 2: 'Wednesday', 3: 'Thursday', 4: 'Friday', 5: 'Saturday', 6: 'Sunday'})
        ax.bar(for_diagram.index, for_diagram.values)
        ax.set_xlabel('Day Name')
        ax.set_ylabel(column)
        ax.set_title('Bar Chart')
        self.canvas.show()

    def set_table_data(self, data):
        selected_columns = self.get_selected_columns()
        model = QStandardItemModel()
        model_data = data[selected_columns].values.tolist()
        df = pd.DataFrame(model_data)
        if any(df.dtypes == "datetime64[ns]"):
            self.haveDate = True

        model.setHorizontalHeaderLabels(selected_columns)
        for row in model_data:
            row_items = [QStandardItem(str(item)) for item in row]
            model.appendRow(row_items)
        self.tableView.setModel(model)

    def get_selected_columns(self):
        selected_columns = []
        for i in range(self.parent.groupLayoutFilter.count()):
            widget = self.parent.groupLayoutFilter.itemAt(i).widget()
            if isinstance(widget, QCheckBox) and widget.isChecked():
                selected_columns.append(widget.text())
        return selected_columns


class Ui(QtWidgets.QMainWindow):
    tables = []
    pathTableFile = []
    countOfActivatedCheckbox = 0
    data = pd.DataFrame()

    def __init__(self):
        super(Ui, self).__init__()
        uic.loadUi('mainDialog.ui', self)
        self.show()

        self.okPushButton.clicked.connect(self.buttonOk)
        self.dataFromFile.triggered.connect(self.fromFile)
        self.dataFromSite.triggered.connect(self.fromSite)

        self.groupLayout = QtWidgets.QVBoxLayout(self.groupCheckBox)
        self.groupLayoutFilter = QtWidgets.QVBoxLayout(self.groupCheckBoxFilter)
        self.layout().addWidget(self.groupCheckBox)

    def fromFile(self):
        file_path, _ = QFileDialog.getOpenFileName(self, "Выбрать файл", "")
        if not file_path:
            return
        self.pathTableFile.append(file_path)
        checkbox = QCheckBox(file_path)
        self.groupLayout.addWidget(checkbox)

    def fromSite(self):
        text, ok = QInputDialog.getText(self, 'URL Input', 'URL:')
        if not text:
            return
        web_df = read_html(text)
        if web_df:
            for table in web_df:
                self.tables.append(table)
                checkbox = QCheckBox(str(table.head(1)))
                self.groupLayout.addWidget(checkbox)

    def buttonOk(self):
        self.countOfActivatedCheckbox = 0
        selected_tables = []
        for i in range(self.groupLayout.count()):
            widget = self.groupLayout.itemAt(i).widget()
            if isinstance(widget, QCheckBox) and widget.isChecked():
                index = i
                if index < len(self.tables):
                    selected_tables.append(self.tables[index])
                else:
                    file_path = self.pathTableFile[index - len(self.tables)]
                    table = read_excel(file_path)
                    selected_tables.append(table)

        self.toTableView(selected_tables)
        self.data = selected_tables[0]

    def addColumnsTableToCheckbox(self, columns):
        while self.groupLayoutFilter.count():
            item = self.groupLayoutFilter.takeAt(0)
            widget = item.widget()
            if widget:
                widget.deleteLater()
        for column in columns:
            checkbox = QCheckBox(str(column))
            checkbox.stateChanged.connect(self.handle_checkbox_state_change)
            self.groupLayoutFilter.addWidget(checkbox)

    def toTableView(self, selected_tables):
        model = QStandardItemModel()
        for i, table in enumerate(selected_tables):
            if i > 0:
                model.appendRow([QStandardItem("")])
            if i == 0:
                self.addColumnsTableToCheckbox(table.columns)
            model.appendRow([QStandardItem(str(col)) for col in table.columns])
            model_data = table.values.tolist()
            for row in model_data:
                row_items = [QStandardItem(str(item)) for item in row]
                model.appendRow(row_items)
        self.tableView.setModel(model)

    def handle_checkbox_state_change(self):
        checkbox = self.sender()
        if checkbox.isChecked():
            self.countOfActivatedCheckbox += 1
            print(self.countOfActivatedCheckbox)
        else:
            self.countOfActivatedCheckbox -= 1
            print(self.countOfActivatedCheckbox)
        if self.countOfActivatedCheckbox == 2:
            self.plotGraphics()

    def plotGraphics(self):
        selected_columns = []
        for i in range(self.groupLayoutFilter.count()):
            widget = self.groupLayoutFilter.itemAt(i).widget()
            if isinstance(widget, QCheckBox) and widget.isChecked():
                selected_columns.append(widget.text())
        try:
            data = self.data[(self.data['InvoiceDate'] >= pd.to_datetime(str(self.dateFrom.date().toPyDate()))) & (
                    self.data['InvoiceDate'] <= pd.to_datetime(str(self.dateTo.date().toPyDate())))]
            x = pd.to_numeric(data[selected_columns[0]], errors='coerce')
            y = pd.to_numeric(data[selected_columns[1]], errors='coerce')
            mask = ~np.isnan(x) & ~np.isnan(y)
            x = x[mask]
            y = y[mask]
            self.new_window = NewWindow(x, y, selected_columns[0], selected_columns[1], data, self,
                                        self.dateTo.date(), self.dateFrom.date())
            self.new_window.show()
        except Exception as e:
            print("Error occurred during plotting:")
            print(e)



app = QApplication(sys.argv)
window = Ui()
app.exec()
