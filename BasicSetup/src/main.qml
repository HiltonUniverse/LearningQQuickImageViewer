import QtQuick

Window
{
    objectName: "mainWindow"

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle
    {
        objectName: "backgroundRectangle"

        anchors.fill: parent
        color: "Pink"

        Image
        {
            anchors.fill: parent
            source: "image://cpp_image_provider/testId"
            fillMode: Image.PreserveAspectFit
        }
    }
}
