/**
 * @author Cailean Sorce
 * @date 2021-09-11
 * The tlp-stat, tlp bat, and tlp ac commands must be executable without pswd for this program to work.
 */

#include "QDropDown.h"
#include <QApplication>
#include <QtWidgets>
#include <qboxlayout.h>
#include <qcombobox.h>
#include <string>
// #include <cstring>
#include <iostream>
#include <stdio.h>

std::string exec(std::string);

class MainWindow : public QDropDown
{
    Q_OBJECT
    public:
      MainWindow(int, char *[]);
    private slots:
      void handleTLPModeChange(int);
};

MainWindow::MainWindow(int argc, char *argv[]) : QDropDown(argc, argv){
    std::string tlpInfo = ::exec("sudo tlp-stat -s | grep -E 'Mode|State'");
    int firstLEnd = tlpInfo.find('\n');
    std::string tlpState = tlpInfo.substr(tlpInfo.find('=') + 1, firstLEnd - tlpInfo.find('=') - 1); //((strstr(tlpInfo, "enabled") == nullptr) ? "enabled" : "disabled");
    std::string tlpMode = tlpInfo.substr(tlpInfo.find('=', firstLEnd) + 1, tlpInfo.find('\n', firstLEnd) - tlpInfo.find('=', firstLEnd) - 1);
    // tlpInfo.l

    QHBoxLayout *layout_TLP = new QHBoxLayout;
    QComboBox *combo_TLPMode = new QComboBox;
    // connect()
    combo_TLPMode->addItems({"BAT (power)", "AC (performance)"});
    combo_TLPMode->setCurrentIndex(tlpMode.find("battery") != -1 ? 0 : 1);
    // std::string tlpLabel = "TLP " + tlpState + ": ";
    layout_TLP->addWidget(new QLabel(("TLP " + tlpState).c_str())); //stlpLabel.c_str()));
    // layout_TLP->addWidget(new QLabel("TLP "));
    layout_TLP->addWidget(combo_TLPMode);
    layout_TLP->addStretch();

   //  QHBoxLayout *layout_sleepTime = new QHBoxLayout;
   //  layout_sleepTime->addWidget(new QLabel("SleepTime"));
   //  layout_sleepTime->addStretch();

    QVBoxLayout *layout_main = new QVBoxLayout;
    layout_main->addLayout(layout_TLP);
   //  layout_main->addLayout(layout_sleepTime);

    this->addContent(layout_main);

    connect(combo_TLPMode, SIGNAL(currentIndexChanged(int)), this, SLOT(handleTLPModeChange(int)));
    // QDropDown window(argc, argv, &layout_main);
}

void MainWindow::handleTLPModeChange(int i){
   std::cout << i;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   //  char *argn[] = {"", "300", "300", "50", "2", "background-color:#000000; color:#ffffff", "#000050", "3", "#505050", "1"};
    MainWindow window(argc, argv);

    window.show();
    return window.exec(); 
}


std::string exec(std::string command) {
   char buffer[128];
   std::string result = "";

   // Open pipe to file
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   return result;
}



#include "PowerDropDown.moc"