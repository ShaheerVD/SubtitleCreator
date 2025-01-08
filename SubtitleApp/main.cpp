#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget mainWindow;
    mainWindow.setWindowTitle("Subtitle Creator App");
    mainWindow.resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(&mainWindow);

    // App title label
    QLabel *titleLabel = new QLabel("Subtitle Creator App");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; color: blue;");
    layout->addWidget(titleLabel);

    // Instruction label
    QLabel *instructionLabel = new QLabel("Select any Video file to create subtitle");
    instructionLabel->setAlignment(Qt::AlignCenter);
    instructionLabel->setStyleSheet("font-size: 18px; color: red;");
    layout->addWidget(instructionLabel);

    // Select button
    QPushButton *selectButton = new QPushButton("Select");
    selectButton->setStyleSheet("font-size: 18px; color: white; background-color: gray;");
    layout->addWidget(selectButton);

    // Label to show the selected file name
    QLabel *fileNameLabel = new QLabel("");
    fileNameLabel->setAlignment(Qt::AlignCenter);
    fileNameLabel->setStyleSheet("font-size: 16px; color: black;");
    layout->addWidget(fileNameLabel);

    // Create Subtitle button (initially hidden)
    QPushButton *createButton = new QPushButton("Create Subtitle");
    createButton->setStyleSheet("font-size: 18px; color: white; background-color: green;");
    createButton->hide();
    layout->addWidget(createButton);

    // Status label
    QLabel *statusLabel = new QLabel("");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("font-size: 16px; color: orange;");
    layout->addWidget(statusLabel);

    // Handle file selection
    QObject::connect(selectButton, &QPushButton::clicked, [&]() {
        QString filePath = QFileDialog::getOpenFileName(&mainWindow, "Choose Video File", "", "Video Files (*.mp4 *.avi *.mkv)");
        if (!filePath.isEmpty()) {
            fileNameLabel->setText(filePath);
            createButton->show(); // Show the create button after a file is selected
            statusLabel->show();
        }
    });

    //Create Button Action
    QObject::connect(createButton, &QPushButton::clicked, [&]() {
       QString videoFile = fileNameLabel->text();
       QFileInfo fileInfo(videoFile);

       QString subtitleFile = fileInfo.absolutePath()+"/"+fileInfo.completeBaseName()+".srt";

       QProcess process;
      QString pythonScript="C:/Qt/Qt5.3.0/Tools/QtCreator/bin/SubtitleApp/SubtitlesServer.py";
      QString command = "C:\\Python312\\python.exe";

      QStringList arguments;
      arguments<<pythonScript<<videoFile<<subtitleFile;
      process.start(command,arguments);

      if(!process.waitForFinished(-1)){
          std::cout<<"Error executing the Script";
      }else{
          std::cout<<"Script executed Successfully";
      }

      QFile file(subtitleFile);
      if(file.exists()){
          statusLabel->setText("Created Successfully");
      }else{
          statusLabel->setText("Problem Creating Subtitles. Try Again");
      }


    });



    mainWindow.setLayout(layout);
    mainWindow.show();

    return app.exec();
}
