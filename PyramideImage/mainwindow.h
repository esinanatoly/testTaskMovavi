#pragma once
#include <QMainWindow>

class QMenu;
class QLabel;
class QScrollArea;
class QImage;
class QComboBox;
class PyramidWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	bool loadFile(const QString&);
private slots:
	void open();

private:
	void createMenu();
	void updateLayersCombox();
	void updateImageResLabel(int layerNumber);
	void updateLayer(int layerNumber);
	PyramidWidget *pyramidWidget;
	QComboBox *layersCombo;
	QLabel *resLabel;
};

