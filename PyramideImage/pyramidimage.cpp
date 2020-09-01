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

	image = newImage;
	currentLayer = image;
	countLayersNumber();
	setDisplayedImage(currentLayer);
}

void PyramidWidget::setDisplayedImage(const QImage &newImage)
{
	imageLabel->setPixmap(QPixmap::fromImage(newImage));
	imageLabel->adjustSize();
}

int PyramidWidget::getLayerWidth()
{
	return currentLayer.width();
}

int PyramidWidget::getLayerHeight()
{
	return currentLayer.height();
}

int PyramidWidget::getLayersNumber()
{
	return layersNumber;
}

void PyramidWidget::countLayersNumber()
{
	int imageHeight = image.height();
	int imageWidth = image.width();

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

void PyramidWidget::makeLayer(int layerNumber)
{
	currentLayer = image;
	for (int i = 0; i < layerNumber; i++) {
		currentLayer = currentLayer.scaled(static_cast<double>(currentLayer.width())/scaleFactor,
		                                   static_cast<double>(currentLayer.height())/scaleFactor,
		                                   Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}
}

void PyramidWidget::updateDisplayedLayer()
{
	QImage tmpImage = currentLayer.scaled(image.width(), image.height(),
	                                      Qt::KeepAspectRatio, Qt::SmoothTransformation);
	setDisplayedImage(tmpImage);
}

void PyramidWidget::setScaleFactor(double newScaleFactor)
{
	scaleFactor = newScaleFactor;
	countLayersNumber();
}