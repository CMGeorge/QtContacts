import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import net.reea 0.1
ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    ListView{
        anchors.fill: parent
        model: ContactsModel{
        }

        delegate: ItemDelegate{
            width: parent.width
//            height: cell.height
            contentItem: ColumnLayout{
                id: cell
               width: parent.width
               Label{
                   text:name
               }
               Label{
                   text:phone
               }
               Rectangle{
                   height: 1
                   Layout.fillWidth: true
                   color:"#D3D3D3"
               }
            }
        }
    }
}
