import QtQuick 2.11
import CustomControls 1.0

Item {


    property int innerMargin: 30
    property real timeVal: 25
    property real tempVal: 25

    property color timeProgressMinColor: "#222222"
    property color timeProgressMidColor: "#aaaaaa"
    property color timeProgressMaxColor: "#ffffff"
    property real timeMinVal: 0
    property real timeMaxVal: 100
    property alias timeFillType: time.fillType

    property color tempProgressMinColor: "blue"
    property color tempProgressMidColor: "white"
    property color tempProgressMaxColor: "red"
    property real tempMinVal: 0
    property real tempMaxVal: 100
    property alias dialType: temp.dialType
    property alias tempFillType: temp.fillType

    RadialBarMax {
        id: time
        width: parent.width
        height: parent.height

        penStyle: Qt.RoundCap
        //backgroundColor: "#111111"
        progressMinColor: timeProgressMinColor
        progressMidColor: timeProgressMidColor
        progressMaxColor: timeProgressMaxColor
        fillType: RadialBarMax.RotateGradient

        foregroundColor: "#111111"//"#191a2f"
        dialWidth: 8
        minValue: timeMinVal
        maxValue: timeMaxVal
        value: timeVal
        format: "%ETIME%"
        textVertOffset: -20
        //suffixText: ""
        //showText: false
        textFont {
            family: "Halvetica"
            italic: false
            pointSize: 14
        }
        textColor: "#3db82d"

        RadialBarMax {
            id: temp

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - innerMargin
            height: parent.height - innerMargin

            penStyle: Qt.RoundCap
            progressMinColor: tempProgressMinColor
            progressMidColor: tempProgressMidColor
            progressMaxColor: tempProgressMaxColor
            fillType: RadialBarMax.Gradient
            foregroundColor: "#191a2f"
            dialWidth: 8
            dialType: dialType
            minValue: tempMinVal
            maxValue: tempMaxVal
            value: tempVal
            format: "%0.2f°"
            textVertOffset: 20
            //suffixText: "°"
            textFont {
                family: "Halvetica"
                italic: false
                pointSize: 14
            }
            textColor: "#3db82d"
        }
    }
}
