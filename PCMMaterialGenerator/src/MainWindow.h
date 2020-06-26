#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();


private slots:
	void on_pushButton_M6File_clicked();

	void on_pushButton_Create_clicked();

	void on_pushButton_AddRow_clicked();

	void on_pushButton_DeleteRow_clicked();

private:
	Ui::MainWindow *m_ui;

};

#endif // MAINWINDOW_H
