import QtQuick 2.0

import QtQuick 2.7
import QtQuick.Window 2.2
import CustomControls 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: appwnd
    visible: true
    width: 700
    height: 700
    title: qsTr("Hello World")

    property int columns : 3
    property int rows : 2

    property real targetTemp: 110
    property real tempColdToHotActVal: 45
    property real tempHotToColeActVal: 110 - 45
    property real tempMinVal: 25
    property real tempMaxVal: 110

    property real timeActVal: 0
    property real timeMinVal: 0
    property real timeMaxVal: 60 * 2

    property int innerMargin: 100

    property var startTime: new Date()
    property int currentTimeMS: 0

    Rectangle {
        anchors.fill: parent
        color: "#000000"
    }

    RadialBarMax {
        id: outer
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height
        penStyle: Qt.RoundCap
        //backgroundColor: "#111111"

        progressMinColor: "green"
        progressMidColor: "orange"
        progressMaxColor: "yellow"

        foregroundColor: "#111111"//"#191a2f"
        dialWidth: 12
        minValue: timeMinVal
        maxValue: timeMaxVal
        value: timeActVal
        format: "%TIME%"
        textVertOffset: -60
        //suffixText: ""
        //showText: false
        textFont {
            family: "Halvetica"
            italic: false
            pointSize: 40
        }
        textColor: "#3db82d"

        RadialBarMax {
            id: middle
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - innerMargin
            height: parent.height - innerMargin

            penStyle: Qt.RoundCap
            //backgroundColor: "#111111"
            progressMinColor: "#222222"
            progressMidColor: "#888888"
            progressMaxColor: "#ffffff"
            rotateGradient: true

            foregroundColor: "#111111"//"#191a2f"
            dialWidth: 12
            minValue: timeMinVal
            maxValue: timeMaxVal
            value: timeActVal
            format: "%ETIME%"
            textVertOffset: -20
            //suffixText: ""
            //showText: false
            textFont {
                family: "Halvetica"
                italic: false
                pointSize: 40
            }
            textColor: "#3db82d"

            RadialBarMax {
                id: inner
                //anchors.left: parent.left - innerMargin
                //anchors.right: parent.right - innerMargin
                //anchors.top: parent.top - innerMargin
                //anchors.bottom: parent.bottom - innerMargin
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - innerMargin
                height: parent.height - innerMargin

                penStyle: Qt.RoundCap
                progressMinColor: "blue"
                progressMidColor: "white"
                progressMaxColor: "red"
                foregroundColor: "#191a2f"
                dialWidth: 12
                minValue: tempMinVal
                maxValue: tempMaxVal
                value: tempColdToHotActVal
                format: "%0.2f°"
                textVertOffset: 20
                //suffixText: "°"
                textFont {
                    family: "Halvetica"
                    italic: false
                    pointSize: 40
                }
                textColor: "#3db82d"

                RadialBarMax {
                    id: inner2
                    dialType: RadialBarMax.MaxToMin
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width - innerMargin
                    height: parent.height - innerMargin

                    penStyle: Qt.RoundCap
                    progressMinColor: "red"
                    progressMidColor: "white"
                    progressMaxColor: "blue"
                    foregroundColor: "#191a2f"
                    dialWidth: 12
                    minValue: tempMinVal
                    maxValue: tempMaxVal
                    value: tempHotToColeActVal
                    format: "%0.2f°"
                    textVertOffset: 60
                    //suffixText: "°"
                    textFont {
                        family: "Halvetica"
                        italic: false
                        pointSize: 40
                    }
                    textColor: "#3db82d"
                }
            }
        }
    }

    Component.onCompleted: {
        console.log("Completed Running!")
        startTime.setSeconds((startTime.getSeconds() + 10))
    }

    function adjustVal(actual, target, min, max) {
        if (actual < target) {
            actual = actual + (Math.random() * ((max - min) / 100.0))
        } else {
            actual = actual - (Math.random() * ((max - min) / 100.0))
        }
        return actual
    }

    function adjustTarget(actual, target, min, max) {
        if (actual <= min) {
            target = max
        } else if (actual >= max) {
            target = min
        }
        return target
    }

    Timer {
        id: updateDataTimer
        interval: 100
        running: true
        repeat: true
        onTriggered: {
            tempColdToHotActVal = adjustVal(tempColdToHotActVal, targetTemp, tempMinVal, tempMaxVal)
            tempHotToColeActVal = tempMaxVal - (tempColdToHotActVal - tempMinVal)
            targetTemp = adjustTarget(tempColdToHotActVal, targetTemp, tempMinVal, tempMaxVal)
            var endTime = new Date()
            currentTimeMS = endTime - startTime
            timeActVal = Math.floor(currentTimeMS / 1000)
        }
    }
}
