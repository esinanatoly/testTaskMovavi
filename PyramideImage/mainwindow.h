#pragma once
#include <QMainWindow>
#include "loadedimage.h"

class QMenu;
class QLabel;
class QScrollArea;
class QImage;
class QComboBox;
class QDoubleSpinBox;
class PyramidWidget;
class LoadedImage;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	bool loadFile(const QString&);

private slots:
	void open();
	void updateLayer(QString layerNumberStr);
	void updateFile(QString fileName);
	void updateScaleFactor();

private:
	void createMenu();
	void updateLayersCombox();
	void updateFilesCombox();
	void updateImageResLabel();

	PyramidWidget *pyramidWidget;
	QComboBox *filesCombo;
	QComboBox *layersCombo;
	QDoubleSpinBox *scaleFactorSpinBox;
	QLabel *resLabel;
	QVector<LoadedImage> loadedImages;
};

