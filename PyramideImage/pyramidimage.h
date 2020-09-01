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
	int getLayerWidth();
	int getLayerHeight();
	int getLayersNumber();
	void initImage(const QImage &newImage);
	void updateDisplayedLayer();
	void makeLayer(int layerNumber);

private:
	void createWidgets();
	void countLayersNumber();
	void setDisplayedImage(const QImage &newImage);

	int layersNumber;
	double scaleFactor = 2.0;
	QImage image;
	QImage currentLayer;
	QLabel *imageLabel;
	QScrollArea *scrollArea;
};
