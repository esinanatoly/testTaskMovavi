#include "pyramidimage.h"

#include <QScrollArea>
#include <QImage>
#include <QLabel>
#include <QHBoxLayout>

PyramidWidget::PyramidWidget(QWidget *parent) : QWidget(parent)
{
	createWidgets();
	QHBoxLayout *centralLayout = new QHBoxLayout;
	centralLayout->addWidget(scrollArea);
	setLayout(centralLayout);
}

void PyramidWidget::createWidgets()
{
	imageLabel = new QLabel;
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	scrollArea = new QScrollArea;
	scrollArea->setBackgroundRole(QPalette::Base);
	scrollArea->setWidget(imageLabel);
}
void PyramidWidget::initImage(const QImage &newImage)
{
	if (layers.size() > 0) {
		layers.clear();
	}
	layers.push_back(newImage);
	countLayersNumber();
	makeLayers();
	setDisplayedImage(layers[0]);
}

void PyramidWidget::setDisplayedImage(const QImage &newImage)
{
	imageLabel->setPixmap(QPixmap::fromImage(newImage));
	imageLabel->adjustSize();
}

int PyramidWidget::getLayerWidth(int layersNumber)
{
	return layers[layersNumber].width();
}

int PyramidWidget::getLayerHeight(int layersNumber)
{
	return layers[layersNumber].height();
}

int PyramidWidget::getLayersNumber()
{
	return layersNumber;
}

void PyramidWidget::countLayersNumber() {
	int imageHeight = layers[0].height();
	int imageWidth = layers[0].width();

	int layerCounter = 0;
	while (1) {
		imageHeight = static_cast<double>(imageHeight) / scaleFactor;
		imageWidth = static_cast<double>(imageWidth) / scaleFactor;
		if (imageHeight >= 1 && imageWidth >= 1) {
			layerCounter++;
		}
		else {
			layersNumber = layerCounter;
			break;
		}
	}
}

void PyramidWidget::makeLayers() {
	for(int i = 0; i < layersNumber; i++ ) {
		QImage tmpImage = layers[i].scaled(static_cast<double>(layers[i].width())/scaleFactor,
		                                   static_cast<double>(layers[i].height())/scaleFactor,
		                                   Qt::KeepAspectRatio, Qt::SmoothTransformation);
		layers.push_back(tmpImage);
	}
}

void PyramidWidget::updateDisplayedLayer(int layerNumber)
{
	QImage tmpImage = layers[layerNumber].scaled(layers[0].width(), layers[0].height(),
	                                             Qt::KeepAspectRatio, Qt::SmoothTransformation);
	setDisplayedImage(tmpImage);
}
