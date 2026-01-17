import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import EncodedImageHashQT

Window {
    width: 640
    height: 480
    visible: true
    //color: "black"
    title: qsTr("Hello World")


        Rectangle {
            anchors.centerIn: parent
            Text {
                id:fileSelectText
            }

            Button {
                id: fileSelectBtn
                text: "Select file"
                onClicked: selectDialog.open()
            }

            FileDialog {
                id: selectDialog
                title: "Select an Image"
                nameFilters: ["All files(*), Images (*.png, *.jpg)"]
                onAccepted: {
                    cimage.loadImage(selectedFile)
                    fileSelectText.text = "Selected " + selectedFile
                    console.log("Do something")
                }
            }
    }
        Text {
            id: shaderText
            color: "black"
            text: "Hello"
            font.pixelSize:64
            font.bold: true
            visible: false
        }
        CImage {
           id: cimage
        }

}
