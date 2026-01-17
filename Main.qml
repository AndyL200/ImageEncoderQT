import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import EncodedImageHashQT

Window {
    width: 640
    height: 480
    visible: true
    color: "#2D3F45"
    title: qsTr("Hello World")
    CImage {
       id: cimage
       onImageLoaded: (dataUrl) => {
            displayImg.source = dataUrl
            encodeBtn.visible = true
            decodeBtn.visible = true
            inputMessage.visible = true
       }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 15

        Text {
            Layout.fillWidth: true
            id: decodedText
            text: ""
            color: "white"
            font.pixelSize: 24

        }

        Image {
            id: displayImg
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 300
            fillMode: Image.PreserveAspectFit
            cache: false
        }

        RowLayout {
            spacing: 5
            Layout.fillWidth: true


            Button {
                id: encodeBtn
                text: "Encode"
                visible: false
                Layout.fillWidth: true
                background:
                    Rectangle {
                        color: fileSelectBtn.down? "#7EB3C4" : "#7EB3C4"
                        radius: 5
                        border.color: "#7EB3C4"
                        border.width: 1
                    }
                onClicked: {
                    displayImg.source = cimage.encode(inputMessage.text)
                }
            }
            Button {
                id: decodeBtn
                text: "Decode Message"
                visible: false
                Layout.fillWidth: true
                background:
                    Rectangle {
                        color: fileSelectBtn.down? "#7EB3C4" : "#7EB3C4"
                        radius: 5
                        border.color: "#7EB3C4"
                        border.width: 1
                    }
                onClicked: {
                    decodedText.text = cimage.decode();
                }
            }


            Button {
                id: fileSelectBtn
                text: "Select file"
                Layout.fillWidth: true
                background:
                    Rectangle {
                        color: fileSelectBtn.down? "#7EB3C4" : "#7EB3C4"
                        radius: 5
                        border.color: "#7EB3C4"
                        border.width: 1
                    }

                onClicked: selectDialog.open()
            }
        }
        RowLayout {
            spacing: 5
            Layout.fillWidth: true

        Rectangle {
            color: "cyan"
            TextInput {
                id: inputMessage
                color: "#C4AC7E"
                text: "Put Message to Encode here"
                font.pixelSize:24
                font.bold: true
                visible: false
            }
            Layout.fillWidth: true
        }




        Text {
            id:fileSelectText
            text: ""
            Layout.fillWidth: true
        }




        Item {
            Layout.fillWidth: true
        }
    }
        Item {
            Layout.fillWidth: true
        }
    }
        FileDialog {
            id: selectDialog
            title: "Select an Image"
            nameFilters: ["All files(*), Images (*.png, *.jpg)"]
            onAccepted: {
                cimage.loadImage(selectedFile)
                fileSelectText.text = "Selected file"
            }
        }

}
