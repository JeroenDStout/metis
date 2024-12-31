#pragma once

#include "metis_qt/ui_window.h"
#include "metis_qt/ui_version.h"

#include <QtWidgets/QMainWindow>


namespace metis::qt {

    // Empty window
    class main_window : public QMainWindow
    {
        Q_OBJECT

      public:
        main_window();
        
      public slots:
        void uii_about();

      private:
        Ui::metis_main_window ui_window;
        Ui::version           ui_version;
    };

}