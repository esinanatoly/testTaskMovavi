#pragma once

#include <QImage>
#include <QString>

class LoadedImage
{
	QString m_fileName;
	int m_diag;
	QImage m_image;

public:
	LoadedImage(QString fileName, QImage image = QImage());

	QImage getImage();
	QString getFileName();
	int getDiag();

	friend bool operator< (const LoadedImage &im1, const LoadedImage &im2);
	friend bool operator> (const LoadedImage &im1, const LoadedImage &im2);
	friend bool operator== (const LoadedImage &im1, const LoadedImage &im2);
	friend bool compareByDiag(const LoadedImage &im1, const LoadedImage &im2);
};

bool compareByDiag(const LoadedImage &im1, const LoadedImage &im2);
