/**
 * @author Cailean Sorce
 * @date 2021-09-11
 * The tlp-stat, tlp bat, and tlp ac commands must be executable without pswd for this program to work.
 */

#include "QDropDown.h"
#include <QApplication>
#include <QtWidgets>
#include <qboxlayout.h>
#include <qcalendar.h>
#include <qcalendarwidget.h>
#include <qcombobox.h>
#include <qpalette.h>
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
   //  private slots:
   //    void handleTLPModeChange(int);
};

MainWindow::MainWindow(int argc, char *argv[]) : QDropDown(argc, argv){
   QCalendarWidget *calendar = new QCalendarWidget;
   // calendar ->backgroundRole(QPalette::Background);
   calendar->setStyleSheet((this->_qss).c_str());
   // std::string stri = this->_qss;
   QVBoxLayout *layout_main = new QVBoxLayout;
   layout_main->addWidget(calendar);
   // layout_main->addLayout(layout_TLP);
   // layout_main->addLayout(layout_sleepTime);

   // QTextCharFormat fmt;
   // fmt.setForeground(QBrush(Qt::blue));
   // calendar->calendarWidget()->setWeekdayTextFormat(Qt::Saturday, fmt);
   // calendar->calendarWidget()->setWeekdayTextFormat(Qt::Sunday, fmt);

   this->addContent(layout_main);

   //  connect(combo_TLPMode, SIGNAL(currentIndexChanged(int)), this, SLOT(handleTLPModeChange(int)));
   // QDropDown window(argc, argv, &layout_main);
}

// void MainWindow::handleTLPModeChange(int i){
//    std::cout << i;
// }

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   // char *argn[] = {"", "300", "300", "50", "2", "background-color:#000000;color:#ffffff; alternate-background-color: #000000;", "#000050", "3", "#505050", "1"};
   MainWindow window(argc,argv);


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



#include "CalendarDropDown.moc"