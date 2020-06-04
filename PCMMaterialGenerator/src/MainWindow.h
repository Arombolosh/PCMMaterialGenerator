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

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
