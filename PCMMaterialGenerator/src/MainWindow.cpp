#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <vector>
#include <iostream>

#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);
	//m_ui->tableWidget->setRowCount(1);
	//m_ui->tableWidget->setColumnCount(2);



	//Set Table Header
	QStringList headerLabels{tr("Temperature ") + "[C]",tr("Enthalpy ") + "[kJ/kgK]"};
	m_ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
	m_ui->tableWidget->horizontalHeader()->setSectionsClickable(false);
	m_ui->tableWidget->insertRow(0);
	//m_ui->tableWidget->setItem(0,0,new QTableWidgetItem("0"));
	//m_ui->tableWidget->setItem(0,1,new QTableWidgetItem("0",new QDoubleSpinBox()));

	//QTableWidgetItem * item = new QTableWidgetItem();
	QDoubleSpinBox* dblSpinTemp = new QDoubleSpinBox();
	dblSpinTemp->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
	dblSpinTemp->setMinimum(-273.15);
	dblSpinTemp->setMaximum(200);
	dblSpinTemp->setDecimals(1);
	QDoubleSpinBox* dblSpinEnt = new QDoubleSpinBox();
	dblSpinEnt->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
	dblSpinEnt->setMinimum(0);
	dblSpinEnt->setMaximum(2000);
	dblSpinEnt->setDecimals(1);

	m_ui->tableWidget->setCellWidget(0,0,dblSpinTemp);
	m_ui->tableWidget->setCellWidget(0,1,dblSpinEnt);

	m_ui->lineEdit_M6Path->setText("c:/temp/");
	m_ui->lineEdit_Filename->setText("SP26");
	m_ui->lineEdit_Producer->setText("Producer name");

}

MainWindow::~MainWindow()
{
	delete m_ui;
}


// *** slots

void MainWindow::on_pushButton_M6File_clicked()
{
	//Initalisierung des Speicherpfades durch Nutzereingabe
	QString fpath = QFileDialog::getExistingDirectory(this, tr("Setze Ablageordner für Materialdatei"), QString());
	if(fpath.isEmpty())
		return;
	m_ui->lineEdit_M6Path->setText(fpath);

}

void MainWindow::on_pushButton_Create_clicked()
{
	if(m_ui->lineEdit_Filename->text().isEmpty()){
		QMessageBox::critical(this, tr("Empty File name."), QMessageBox::tr("Empty File name."));
		return;
	}
	if(m_ui->lineEdit_M6Path->text().isEmpty()){
		QMessageBox::critical(this, tr("Empty path name."), QMessageBox::tr("Empty path name."));
		return;
	}


	QDir dir(m_ui->lineEdit_M6Path->text());
	if(!dir.exists()){
		QMessageBox::critical(this, tr("Invalid m6-file path."), QMessageBox::tr("Invalid m6-file path. Only path no filename."));
		return;
	}

	std::vector<double> temperature;		///< temperature in °C
	std::vector<double> enthalpy;

	double rho = m_ui->doubleSpinBox_Rho->value();
	double lambda = m_ui->doubleSpinBox_Lambda->value();

	//populate vectors for enthalpy and temperature from user inputs
	for (size_t i=0; i<m_ui->tableWidget->rowCount();++i) {
		//dynamic_cast testet ob das obj in das zielobj gewandelt werden kann.
		temperature.push_back(static_cast<QDoubleSpinBox*>(m_ui->tableWidget->cellWidget(i,0))->value()+273.15);
		enthalpy.push_back(static_cast<QDoubleSpinBox*>(m_ui->tableWidget->cellWidget(i,1))->value());
	}

	if(temperature.empty()){
		QMessageBox::critical(this, tr("Input Values invalid."), QMessageBox::tr("Please insert more table values."));
		return;
	}

	//check if first temperature is 0 K
	if(temperature[0] != 0){
		temperature.insert(temperature.begin(), 0);
		enthalpy.insert(enthalpy.begin(), 0);
	}
	//check if last min temperature is 100°C
	if(temperature.back() < 100+273.15){
		temperature.push_back(100+273.15);
		enthalpy.push_back(enthalpy.back());
	}


	std::vector<double> uEnergy(temperature.size(),0);
	//Calculate internal energy and populate energy vector
	for(size_t i=0;i<temperature.size();++i){
		if (i == 0)
			uEnergy[i] = (rho*lambda*temperature[i]);
		else{
			if(temperature[i-1]>=temperature[i]){
				QMessageBox::critical(this, tr("Input Values invalid."), QMessageBox::tr("Temperature values must be entered in ascending order."));
				return;
			}
			uEnergy[i] = rho* (temperature[i] - temperature[i-1]) * enthalpy[i]*1000 + uEnergy[i-1];
		}
	}

	/*
[THERMAL_STORAGE]
  FUNCTION =              u(T)
	  0                289.15           290.15           291.15           292.15           293.15           294.15           295.15           296.15           297.15           298.15           299.15           300.15           301.15           302.15           303.15           304.15           373.15
	  0                1734900000       1739400000       1743900000       1749900000       1757400000       1766400000       1784400000       1817400000       1857900000       1932900000       1970400000       1980900000       1986900000       1992900000       1998900000       2006400000       2420400000
*/
	QStringList ss;
	ss << "D6MARLZ! 006.001";
	ss << "";
	ss << "[IDENTIFICATION]";
	ss << "NAME                     = EN: " + m_ui->lineEdit_Filename->text();
	ss << "AQUISITION_ID            = -1";
	ss << "PRODUCER                 = DE: ";
	ss << "DATE                     = " + QDateTime::currentDateTime().date().toString("dd.MM.yyyy");
	ss << "COLOUR                   = #ff409020";
	ss << "CATEGORY                 = MISC";
	ss << "";
	ss << "";
	ss << "[STORAGE_BASE_PARAMETERS]";
	ss << "RHO                      = " + QString("%1").arg(m_ui->doubleSpinBox_Rho->value(),0,'f',2);
	ss << "";
	ss << "[TRANSPORT_BASE_PARAMETERS]";
	ss << "LAMBDA                   = " + QString("%1").arg(m_ui->doubleSpinBox_Lambda->value(),0,'f',3);
	ss << "";
	ss << "[THERMAL_STORAGE]";
	ss << "FUNCTION = u(T)";

	QString sTemp, sU;
	for(size_t i=0; i<temperature.size(); ++i){
		sTemp += QString("%1").arg(temperature[i],0,'f', 1);
		sU += QString("%1").arg(uEnergy[i],0,'f', 1);
		if(i!=temperature.size()-1){
			sTemp += "\t";
			sU += "\t";
		}
	}
	ss << sTemp;
	ss << sU;

	QFile outFile(m_ui->lineEdit_M6Path->text() + m_ui->lineEdit_Filename->text() + ".m6");
	outFile.open(QIODevice::WriteOnly);
	outFile.write(ss.join("\n").toUtf8());

	QMessageBox::information(this, tr("Finished."), QMessageBox::tr("Process finished."));
}


void MainWindow::on_pushButton_AddRow_clicked()
{

	int rowCount = m_ui->tableWidget->rowCount();
	m_ui->tableWidget->insertRow(rowCount);

	QDoubleSpinBox* dblSpinTemp = new QDoubleSpinBox();
	dblSpinTemp->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
	dblSpinTemp->setMinimum(-273.15);
	dblSpinTemp->setMaximum(200);
	dblSpinTemp->setDecimals(1);

	QDoubleSpinBox* dblSpinEnt = new QDoubleSpinBox();
	dblSpinEnt->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
	dblSpinEnt->setMinimum(0);
	dblSpinEnt->setMaximum(2000);
	dblSpinEnt->setDecimals(1);

	m_ui->tableWidget->setCellWidget(rowCount,0,dblSpinTemp);
	m_ui->tableWidget->setCellWidget(rowCount,1,dblSpinEnt);



}

void MainWindow::on_pushButton_DeleteRow_clicked()
{
	m_ui->tableWidget->removeRow(m_ui->tableWidget->rowCount()-1);
}
