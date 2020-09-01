#include "loadedimage.h"

LoadedImage::LoadedImage(QString fileName, QImage image) : m_fileName(fileName), m_image(image)
{
	if (!image.isNull()) {
		m_diag = image.width() * image.width() + image.height() * image.height();
	}
	else {
		m_diag = 0;
	}
}

QImage LoadedImage::getImage()
{
	return m_image;
}

QString LoadedImage::getFileName()
{
	return m_fileName;
}

int LoadedImage::getDiag()
{
	return m_diag;
}

bool operator< (const LoadedImage &im1, const LoadedImage &im2)
{
	return im1.m_fileName < im2.m_fileName;
}

bool operator> (const LoadedImage &im1, const LoadedImage &im2)
{
	return im1.m_fileName > im2.m_fileName;
}

bool operator== (const LoadedImage &im1, const LoadedImage &im2)
{
	return im1.m_fileName == im2.m_fileName;
}

bool compareByDiag(const LoadedImage &im1, const LoadedImage &im2)
{
	return im1.m_diag < im2.m_diag;
}
