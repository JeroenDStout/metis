#include "metis_qt/window.h"
#include "repo_version/git_version.h"


#include <iostream>


using namespace metis::qt;


main_window::main_window()
{
    ui_window.setupUi(this);
}


void main_window::uii_about()
{
    QDialog *about = new QDialog();

    ui_version.setupUi(about);
    ui_version.version_main->setText(QString("Metis\n") + metis::version::get_git_essential_version());
    ui_version.version_compile->setText(metis::version::get_compile_stamp());
    ui_version.version_git->setText(metis::version::get_git_history());

    about->setWindowModality(Qt::WindowModality::ApplicationModal);
    about->show();
}