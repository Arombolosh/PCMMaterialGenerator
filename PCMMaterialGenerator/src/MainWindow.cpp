#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <MM_Material.h>

#include <vector>
#include <iostream>

#include <QFileDialog>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    //m_ui->tableWidget->setRowCount(1);
    //m_ui->tableWidget->setColumnCount(2);



    //Set Table Header
    QStringList headerLabels{tr("Temperature") + "[K]",tr("Enthalpy") + "[kJ]"};
    m_ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    m_ui->tableWidget->horizontalHeader()->setSectionsClickable(false);

//    QTableWidgetItem *itema = new QTableWidgetItem();
//    QTableWidgetItem *itemb = new QTableWidgetItem();
//    itema->setText(tr("Temperature") + "[K]");
//    m_ui->tableWidget->setHorizontalHeaderItem(0,itema);
//    itemb->setText(tr("Enthalpy") + "[J/m³]");
//    m_ui->tableWidget->setHorizontalHeaderItem(1,itemb);


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
    m_ui->lineEdit_M6File->setText(fpath);

}

void MainWindow::on_pushButton_Create_clicked()
{

    MM::Material pcm;

    //Read Value Input
    pcm.m_paraTransport[MM::Material::MP_LAMBDA].set("LAMBDA",m_ui->doubleSpinBox_Lambda->value(), IBK::Unit("W/mK"));
    pcm.m_paraStorage[MM::Material::MP_RHO].set("RHO",m_ui->doubleSpinBox_Rho->value(),IBK::Unit("kg/m3"));
    pcm.m_identification.m_name.setString(m_ui->lineEdit_Filename->text().toStdString(), "de");
    pcm.m_identification.m_producer.setString(m_ui->lineEdit_Producer->text().toStdString(), "de");
    IBK::Path filename(m_ui->lineEdit_M6File->text().toStdString() + "/" + m_ui->lineEdit_Filename->text().toStdString() + ".m6");

    //Set general Material Parameters
    pcm.m_identification.m_flags =
            MM::MaterialIdentification::AIR_TIGHT &
            MM::MaterialIdentification::WATER_TIGHT &
            MM::MaterialIdentification::VAPOR_TIGHT;
    pcm.m_identification.m_cat = MM::MaterialCategory::Miscellaneous;
    pcm.m_id = 1001001;


    std::vector<double> temperature;
    std::vector<double> enthalpy;
    std::vector<double> uenergy;
    double rho = pcm.m_paraStorage[MM::Material::MP_RHO].get_value(IBK::Unit("kg/m3"));
    double lambda = pcm.m_paraTransport[MM::Material::MP_LAMBDA].get_value(IBK::Unit("W/mK"));

    //populate vectors for enthalpy and temperature from user inputs
    for (size_t i=0; i<m_ui->tableWidget->rowCount();++i) {
        temperature.push_back(m_ui->tableWidget->item(i,0)->text().toDouble());
        enthalpy.push_back(m_ui->tableWidget->item(i,1)->text().toDouble());
    }
    //Calculate internal energy and populate energy vector
    for(size_t i=0;i<temperature.size();++i){
        if (uenergy.empty()) uenergy[i]=rho*lambda*temperature[i];
        else uenergy[i]=rho* (temperature[i] - temperature[i-1]) * enthalpy[i]/1000 + uenergy[i-1];
    }
    IBK::LinearSpline m_linSpl;
    m_linSpl.setValues(temperature, uenergy);
    pcm.m_thermalStorage.m_spline[MM::ThermalStorage::F_u_T] = m_linSpl;


    //ToDo Rausschreiben


    /*
D6MARLZ! 006.001

[IDENTIFICATION]
  NAME                     = DE: SP31 |EN: SP31 |IT: SP31
  AQUISITION_ID            = -1
  PRODUCT_ID               = DE: SP31 |EN: SP31 |IT: SP31
  PRODUCER                 = DE: Rubitherm |EN: Rubitherm |IT: Rubitherm
  LABORATORY               = DE: MASEA |EN: MASEA |IT: MASEA |RU: MASEA
  DATE                     = 10.12.19
  COLOUR                   = #ff404060
  FLAGS                    = AIR_TIGHT
  CATEGORY                 = MISC
  COMMENTS                 = DE: Materialparameter für c_p;Temp...
  DBTYPE                   = 1,7
  HATCHING            is     = 13
*/
    std::stringstream ss;
    QString x=QDateTime::currentDateTime().toString();
    QString y=QDateTime::currentDateTimeUtc().toString();


    ss << "D6MARLZ! 006.001" << std::endl << std::endl;
    ss << "[IDENTIFICATION]" << std::endl;
    ss << "NAME                     = EN: " << m_ui->lineEdit_Filename->text().toStdString() << std::endl;
    ss << "AQUISITION_ID            = -1" << std::endl;
    ss << "PRODUCER                 = DE: " << m_ui->lineEdit_Producer->text().toStdString() << std::endl;
    ss << "DATE                     = " << x.toStdString() << std::endl;




    pcm.write(filename);

}


/*
#include "PCM_Material.h"

#include <MM_Material.h>

void PCM_Material::createM6File(const IBK::Path &path)
{
	readInputs();

	MM::Material mat, insulation;

	mat.m_identification.m_name.setString(m_name, "de");
	mat.m_identification.m_productId.setString("PVTool", "de");
	mat.m_identification.m_producer.setString("Rubitherm", "de");
	mat.m_identification.m_flags =
			MM::MaterialIdentification::AIR_TIGHT &
			MM::MaterialIdentification::WATER_TIGHT &
			MM::MaterialIdentification::VAPOR_TIGHT;
	mat.m_identification.m_cat = MM::MaterialCategory::Miscellaneous;

	mat.m_id = 1001001;

	IBK::Path filename(path / (m_name+"_"+IBK::val2string(mat.m_id)+".m6"));

	mat.m_paraTransport[MM::Material::MP_LAMBDA].set("LAMBDA",m_para[P_Conductivity].get_value(IBK::Unit("W/mK")), IBK::Unit("W/mK"));
	mat.m_paraStorage[MM::Material::MP_RHO].set("RHO",m_para[P_Density].get_value(IBK::Unit("kg/m3")),IBK::Unit("kg/m3"));
	//mat.m_paraStorage[MM::Material::MP_CE].set(m_para[P_SpecHeat].get_value(IBK::Unit("J/kgK")), IBK::Unit("J/kgK"));

	mat.m_thermalStorage.m_spline[MM::ThermalStorage::F_u_T] = m_linSpl;

	mat.write(filename);

	insulation.m_identification.m_name.setString("Insulation", "de");
	insulation.m_identification.m_productId.setString("PVTool", "de");
	insulation.m_identification.m_producer.setString("PVTool", "de");
	insulation.m_identification.m_flags =
			MM::MaterialIdentification::AIR_TIGHT &
			MM::MaterialIdentification::WATER_TIGHT &
			MM::MaterialIdentification::VAPOR_TIGHT;

	insulation.m_identification.m_cat = MM::MaterialCategory::Insulations;
	insulation.m_id = 1001002;
	insulation.m_paraTransport[MM::Material::MP_LAMBDA] = IBK::Parameter("LAMBDA", 0.035, IBK::Unit("W/mK"));
	insulation.m_paraStorage[MM::Material::MP_RHO] = IBK::Parameter("RHO", 35, IBK::Unit("kg/m3"));
	insulation.m_paraStorage[MM::Material::MP_CE] = IBK::Parameter("CE", 1500, IBK::Unit("J/kgK"));

	IBK::Path insuFilename (path / ("Insulation_" + IBK::val2string(insulation.m_id) + ".m6"));

	insulation.write(insuFilename);
}

void PCM_Material::readInputs()
{
	m_specCapacityCurve[IBK::Parameter("Temperature",16,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 4, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",17,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 3, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",18,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 3, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",19,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 4, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",20,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 5, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",21,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 6, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",22,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 12, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",23,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 22, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",24,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 27, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",25,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 50, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",26,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 25, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",27,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 7, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",28,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 4, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",29,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 4, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",30,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 4, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",31,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 5, IBK::Unit("kJ"));

	m_specCapacityCurve[IBK::Parameter("Temperature",-273.15,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 0, IBK::Unit("kJ"));
	m_specCapacityCurve[IBK::Parameter("Temperature",100,IBK::Unit("C"))] = IBK::Parameter("Enthalpy", 4, IBK::Unit("kJ"));

	std::vector<double> temp;
	std::vector<double> ent;

	for (auto &specObj : m_specCapacityCurve) {
		if(temp.size()==0){
			temp.push_back(specObj.first.get_value(IBK::Unit("K")));
			ent.push_back(specObj.second.get_value(IBK::Unit("J")));
		}
		else {
			bool isInsert = false;
			for(size_t i=0; i< temp.size(); ++i){
				double absTemp = specObj.first.get_value(IBK::Unit("K"));
				if(absTemp<temp[i]){
					temp.insert(temp.begin()+i, absTemp);
					ent.insert(ent.begin()+i, specObj.second.get_value(IBK::Unit("J")));
					isInsert = true;
					break;
				}
			}
			if(!isInsert){
				temp.push_back(specObj.first.get_value(IBK::Unit("K")));
				ent.push_back(specObj.second.get_value(IBK::Unit("J")));
			}
		}
	}

	//read name of pcm
	m_name = "SP26";

	//read parameters
	m_para[P_Density] = IBK::Parameter("Density", 1500, IBK::Unit("kg/m3"));
	m_para[P_Conductivity] = IBK::Parameter("Conductivity", 0.5, IBK::Unit("W/mK"));

	for (unsigned int i=1;i<temp.size();++i)
		ent[i] = m_para[P_Density].get_value(IBK::Unit("kg/m3")) * (temp[i] - temp[i-1]) * ent[i] + ent[i-1];

	m_linSpl.setValues(temp, ent);

}



*/

//void MainWindow::on_tableWidget_cellChanged(int row, int column)
//{

//   QTableWidgetItem *itemRow0 = m_ui->tableWidget->item(row, 0);
//   QTableWidgetItem *itemRow1 = m_ui->tableWidget->item(row, 1);

//   if ( !(!itemRow0 || itemRow0->text().isNull()) &&
//         !(!itemRow1 || itemRow1->text().isNull())){
//      m_ui->tableWidget->insertRow(row+1);
//  // }
//   //else return;
//   //else m_ui->tableWidget->removeRow(row);

//    //Wenn Zelleninhalt verändert
//    //Ist Zelleninhalt leer? nichts passiert
//    //wurde Zelle beschrieben, neue Zeile einfügen
//}

void MainWindow::on_pushButton_AddRow_clicked()
{
    m_ui->tableWidget->insertRow(m_ui->tableWidget->rowCount());
}

void MainWindow::on_pushButton_DeleteRow_clicked()
{
    m_ui->tableWidget->removeRow(m_ui->tableWidget->rowCount()-1);
}
