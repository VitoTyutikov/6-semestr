from PyQt6 import uic, QtWidgets
from PyQt6.QtGui import QStandardItem, QStandardItemModel
from PyQt6.QtWidgets import QApplication, QFileDialog, QInputDialog, QCheckBox, QDateEdit
import sys
from function.read_data import read_html, read_excel
import pandas as pd


class Ui(QtWidgets.QMainWindow):
    tables = []
    pathTableFile = []
    countOfActivatedCheckbox = 0
    data=pd.DataFrame
    def __init__(self):
        super(Ui, self).__init__()
        uic.loadUi('mainDialog.ui', self)
        self.show()

        self.okPushButton.clicked.connect(self.buttonOk)
        self.dataFromFile.triggered.connect(self.fromFile)
        self.dataFromSite.triggered.connect(self.fromSite)


        self.groupLayout = QtWidgets.QVBoxLayout(self.groupCheckBox)
        self.groupLayoutFilter = QtWidgets.QVBoxLayout(self.groupCheckBoxFilter)
        # self.groupLayoutFilter.setContentsMargins(0, 0, 0, 0)
        self.layout().addWidget(self.groupCheckBox)
        # self.layout().addWidget(self.groupLayoutFilter)

        self.dateFrom.dateChanged.connect(self.dateWasChanged)
        self.dateTo.dateChanged.connect(self.dateWasChanged)

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
        self.data=selected_tables[0]

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

    def toTableView(self,selected_tables):
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

    def dateWasChanged(self,date):
        print("date",date)

    def handle_checkbox_state_change(self):
        checkbox = self.sender()
        column_name = checkbox.text()
        if checkbox.isChecked():
            self.countOfActivatedCheckbox+=1
            print(self.countOfActivatedCheckbox)
        else:
            self.countOfActivatedCheckbox-=1
            print(self.countOfActivatedCheckbox)
        if self.countOfActivatedCheckbox == 2:
            self.plotGraphics()

    def plotGraphics(self):
        print("plot")


app = QApplication(sys.argv)
window = Ui()
app.exec()
