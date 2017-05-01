#include <QCoreApplication>

#include "qtnetcore.h"
#include "pal.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    pal::string_t sdf;
    pal::to_lower(sdf);

    return a.exec();
}
