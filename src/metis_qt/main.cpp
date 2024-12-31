#include "metis_qt/window.h"
#include "repo_version/git_version.h"

#include <QtWidgets/QApplication>

#include <iostream>


int main(int argc, char *argv[])
{
    std::cout
      << std::endl
      << "          * * * * * * * * " << std::endl
      << "         * * * Metis * * * " << std::endl
      << "          * * * * * * * * " << std::endl
      << std::endl
      << metis::version::get_git_essential_version() << std::endl
      << metis::version::get_compile_stamp() << std::endl
      << std::endl
      << metis::version::get_git_history() << std::endl
      << std::endl;

    QApplication a(argc, argv);
    metis::qt::main_window w;
    w.show();
    return a.exec();
}
