#pragma once
#include <QMainWindow>

class QMenu;
class QLabel;
class QScrollArea;
class QImage;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	bool loadFile(const QString &);

private slots:
	void open();

private:
	void createWidgets();
	void createMenu();
	void setDisplayedImage(const QImage &newImage);

	QImage image;
	QLabel * imageLabel;
	QScrollArea *scrollArea;
};

