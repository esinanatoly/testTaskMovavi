#pragma once
#include <QWidget>

class QImage;
class QScrollArea;
class QLabel;

class PyramidWidget : public QWidget
{
	Q_OBJECT

public:
	PyramidWidget(QWidget *parent = nullptr);
	int getLayerWidth(int layerNumber);
	int getLayerHeight(int layerNumber);
	int getLayersNumber();
	void initImage(const QImage &newImage);
	void updateDisplayedLayer(int layerNumber);

private:
	void createWidgets();
	void countLayersNumber();
	void makeLayers();
	void setDisplayedImage(const QImage &newImage);

	int layersNumber;
	double scaleFactor = 2.0;
	QVector<QImage> layers;
	QLabel *imageLabel;
	QScrollArea *scrollArea;
};
