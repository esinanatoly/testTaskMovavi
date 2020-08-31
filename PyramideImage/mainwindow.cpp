#include "mainwindow.h"

#include <QApplication>
#include <QScrollArea>
#include <QImage>
#include <QLabel>
#include <QStandardPaths>
#include <QFileDialog>
#include <QAction>
#include <QMenuBar>
#include <QImageReader>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	createMenu();
	createWidgets();
	setCentralWidget(scrollArea);
	setWindowTitle("Image Viewer");
	setFixedSize(500, 400);
}


bool MainWindow::loadFile(const QString &fileName)
{
	QImageReader reader(fileName);
	reader.setAutoTransform(true);
	const QImage newImage = reader.read();
	if (newImage.isNull()) {
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
		                         tr("Cannot load %1: %2").arg(QDir::toNativeSeparators(fileName),
		                         reader.errorString()));
		return false;
	}
	setDisplayedImage(newImage);
	return true;
}

void MainWindow::setDisplayedImage(const QImage &newImage)
{
	image = newImage;
	imageLabel->setPixmap(QPixmap::fromImage(image));
	imageLabel->adjustSize();
}

static void initializeImageFileDialog(QFileDialog &dialog)
{
	static bool firstDialog = true;

	if (firstDialog) {
		firstDialog = false;
		const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
		dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
	}

	QStringList mimeTypeFilters({"image/jpeg","image/png"});
	mimeTypeFilters.sort();
	dialog.setMimeTypeFilters(mimeTypeFilters);
	dialog.selectMimeTypeFilter("image/jpeg");
}

void MainWindow::open()
{
	QFileDialog dialog(this, tr("Open File"));
	initializeImageFileDialog(dialog);

	while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first()));
}

void MainWindow::createMenu()
{
	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

	QAction *openAct = fileMenu->addAction(tr("&Open..."), this, &MainWindow::open);
	openAct->setShortcut(QKeySequence::Open);

	fileMenu->addSeparator();

	QAction *exitAct = fileMenu->addAction(tr("&Exit"), this, &QWidget::close);
	exitAct->setShortcut(tr("Ctrl+Q"));

}

void MainWindow::createWidgets()
{
	imageLabel = new QLabel;
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	scrollArea = new QScrollArea;
	scrollArea->setBackgroundRole(QPalette::Base);
	scrollArea->setWidget(imageLabel);
}

