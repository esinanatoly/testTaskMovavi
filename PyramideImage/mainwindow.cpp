#include "mainwindow.h"
#include "pyramidimage.h"

#include <algorithm>
#include <QApplication>
#include <QLabel>
#include <QStandardPaths>
#include <QFileDialog>
#include <QComboBox>
#include <QAction>
#include <QMenuBar>
#include <QImageReader>
#include <QMessageBox>
#include <QBoxLayout>
#include <QScreen>
#include <QDoubleSpinBox>
#include <QValidator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	createMenu();
	QWidget *centralWidget = new QWidget;
	pyramidWidget = new PyramidWidget;

	QLabel *filesLabel = new QLabel(tr("Files:"));
	filesCombo = new QComboBox;
	filesCombo->setEnabled(false);

	connect(filesCombo, QOverload<const QString&>::of(&QComboBox::textActivated),
	        this, &MainWindow::updateFile);

	QLabel *layersLabel = new QLabel(tr("Layers:"));
	layersCombo = new QComboBox;
	layersCombo->setEnabled(false);

	connect(layersCombo, QOverload<const QString&>::of(&QComboBox::textActivated),
	        this, &MainWindow::updateLayer);

	QLabel *scaleFactorLabel = new QLabel(tr("ScaleFactor:"));
	scaleFactorSpinBox = new QDoubleSpinBox;
	scaleFactorSpinBox->setSingleStep(0.1);
	scaleFactorSpinBox->setRange(1.1, 5.0);
	scaleFactorSpinBox->setEnabled(false);

	connect(scaleFactorSpinBox,  QOverload<double>::of(&QDoubleSpinBox::valueChanged),
	        this, &MainWindow::updateScaleFactor);

	resLabel = new QLabel(tr("Resolution:"));

	QHBoxLayout *controlsLayout = new QHBoxLayout;
	controlsLayout->addWidget(filesLabel);
	controlsLayout->addWidget(filesCombo, 1);
	controlsLayout->addWidget(layersLabel);
	controlsLayout->addWidget(layersCombo, 1);
	controlsLayout->addWidget(scaleFactorLabel);
	controlsLayout->addWidget(scaleFactorSpinBox, 1);
	controlsLayout->addWidget(resLabel);
	controlsLayout->addStretch(1);

	QVBoxLayout *centralLayout = new QVBoxLayout;
	centralLayout->addLayout(controlsLayout);
	centralLayout->addWidget(pyramidWidget, 1);
	centralWidget->setLayout(centralLayout);

	setCentralWidget(centralWidget);
	setWindowTitle("Pyramid Viewer");
	resize(QGuiApplication::primaryScreen()->availableSize() * 1 / 4);
}


bool MainWindow::loadFile(const QString &filePath)
{

	QStringList filePathParts = filePath.split("/");
	QString fileName = filePathParts.at(filePathParts.size()-1);

	QImageReader reader(filePath);
	reader.setAutoTransform(true);
	QImage newImage = reader.read();
	if (newImage.isNull()) {
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
					 tr("Cannot load %1: %2").arg(filePath,reader.errorString()));
		return false;
	}

	auto resLoadedImage = std::find(loadedImages.begin(), loadedImages.end(), LoadedImage(fileName));
	if (resLoadedImage != loadedImages.end()) {
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
		                         tr("File %1 already loaded.").arg(fileName));
		newImage = resLoadedImage->getImage();
	}
	else {
		loadedImages.push_back(LoadedImage(fileName, newImage));
		updateFilesCombox();
	}
	static bool firstTime = true;
	if (firstTime) {
		firstTime = false;
		filesCombo->setEnabled(true);
		layersCombo->setEnabled(true);
		scaleFactorSpinBox->setEnabled(true);
	}
	pyramidWidget->initImage(newImage);
	updateImageResLabel();
	updateLayersCombox();
	return true;
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
void MainWindow::updateLayer(QString layerNumberStr)
{
	pyramidWidget->makeLayer(layerNumberStr.toInt());
	updateImageResLabel();
	pyramidWidget->updateDisplayedLayer();
}

void MainWindow::updateFile(QString fileName)
{
	auto resLoadedImage = std::find(loadedImages.begin(), loadedImages.end(), LoadedImage(fileName));
	if (resLoadedImage == loadedImages.end()) {
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
		                         tr("File not found %1").arg(fileName));
	}
	else {
		pyramidWidget->initImage(resLoadedImage->getImage());
		updateImageResLabel();
		updateLayersCombox();
	}
}

void MainWindow::updateImageResLabel()
{
	resLabel->setText(QString("Resolution: %1 x %2").arg(pyramidWidget->getLayerWidth())
	                                                .arg(pyramidWidget->getLayerHeight()));
}

void MainWindow::updateLayersCombox()
{
	layersCombo->clear();
	int layerCnt = pyramidWidget->getLayersNumber();
	for (int i = 0; i <= layerCnt; i ++) {
		layersCombo->addItem(QString::number(i));
	}
}

void MainWindow::updateFilesCombox()
{
	filesCombo->clear();
	QString currentFileName = loadedImages.last().getFileName();
	std::sort(loadedImages.begin(), loadedImages.end(), compareByDiag);
	for (auto image: loadedImages) {
		filesCombo->addItem(QString("%1").arg(image.getFileName()));
	}
	filesCombo->setCurrentText(currentFileName);
}

void MainWindow::updateScaleFactor()
{
	pyramidWidget->setScaleFactor(scaleFactorSpinBox->value());
	updateLayer(QString::number(0));
	updateLayersCombox();
}
