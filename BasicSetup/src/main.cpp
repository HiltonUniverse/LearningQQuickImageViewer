#include <QDebug>
#include <QQmlApplicationEngine>
#include <QApplication>

#include "include/ImageProvider.h"

#include <memory.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    auto image_provider = std::make_unique<ImageProvider>();

    QQmlApplicationEngine engine;
    engine.addImageProvider("cpp_image_provider", image_provider.release());

    engine.load(QUrl(QStringLiteral("qrc:/Basic/src/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
