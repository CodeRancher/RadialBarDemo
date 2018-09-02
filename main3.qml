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
    width: 1400
    height: 700
    title: qsTr("Hello World")

    property int columns : 3
    property int rows : 2

    property real targetTemp: 110
    property real tempColdToHotActVal: 45
    property real tempHotToColdActVal: 110 - 45
    property real tempMinVal: 25
    property real tempMaxVal: 110

    property real timeActVal: 0
    property real timeMinVal: 0
    property real timeMaxVal: 60 * 2

    property int innerMargin: 100

    property var startTime: new Date()
    property int currentTimeMS: 0

    property real pointTempVal: 50


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

    Rectangle {
        id: rectLeft
        width: 700
        color: "#000000"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        RadialBarMax {
            id: outer
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            width: parent.width
            height: parent.height
            penStyle: Qt.RoundCap
            //backgroundColor: "#111111"

            progressMinColor: "#222222"
            progressMidColor: "#888888"
            progressMaxColor: "#ffffff"
            fillType: RadialBarMax.Gradient

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
                fillType: RadialBarMax.RotateGradient

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
                    fillType: RadialBarMax.Gradient

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
                        progressMinColor: "blue"
                        progressMidColor: "white"
                        progressMaxColor: "red"
                        fillType: RadialBarMax.Gradient
                        foregroundColor: "#191a2f"
                        dialWidth: 12
                        minValue: tempMinVal
                        maxValue: tempMaxVal
                        value: tempHotToColdActVal
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
    }

    Rectangle {
        id: rectRight
        color: "#000000"
        anchors.left: rectLeft.right
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        TimeTempGauge {
            id: ttGauge
            //x: 700
            //y: 0
            anchors.right: parent.right
            //anchors.bottom: parent.bottom
            anchors.top: parent.top
            width: 150
            height: 150

            timeMinVal: appwnd.timeMinVal
            timeMaxVal: appwnd.timeMaxVal
            tempMinVal: appwnd.tempMinVal
            tempMaxVal: appwnd.tempMaxVal

            dialType: RadialBarMax.MinToMax
            timeFillType: RadialBarMax.RotateGradient
            tempFillType: RadialBarMax.Gradient
        }

        TimeTempGauge {
            id: ttGauge2
            //x: 700
            //y: 0
            anchors.right: parent.right
            //anchors.bottom: parent.bottom
            anchors.top: ttGauge.bottom
            width: 150
            height: 150

            timeMinVal: appwnd.timeMinVal
            timeMaxVal: appwnd.timeMaxVal
            tempMinVal: 49
            tempMaxVal: 51
            tempVal: 50

            dialType: RadialBarMax.MinToMax
            timeFillType: RadialBarMax.RotateGradient
            tempFillType: RadialBarMax.Point


        }

        TimeTempGauge {
            id: ttGauge3
            //x: 700
            //y: 0
            anchors.right: parent.right
            //anchors.bottom: parent.bottom
            anchors.top: ttGauge2.bottom
            width: 150
            height: 150

            timeMinVal: appwnd.timeMinVal
            timeMaxVal: appwnd.timeMaxVal
            tempMinVal: appwnd.tempMinVal
            tempMaxVal: appwnd.tempMaxVal

            dialType: RadialBarMax.MaxToMin
            timeFillType: RadialBarMax.RotateGradient
            tempFillType: RadialBarMax.Gradient


        }

        TimeTempGauge {
            id: ttGauge4
            //x: 700
            //y: 0
            anchors.right: parent.right
            //anchors.bottom: parent.bottom
            anchors.top: ttGauge3.bottom
            width: 150
            height: 150

            timeMinVal: appwnd.timeMinVal
            timeMaxVal: appwnd.timeMaxVal
            tempMinVal: appwnd.tempMinVal
            tempMaxVal: appwnd.tempMaxVal

            dialType: RadialBarMax.MinToMax
            timeFillType: RadialBarMax.RotateGradient
            tempFillType: RadialBarMax.Point


        }
    }

    Timer {
        id: updateDataTimer
        interval: 100
        running: true
        repeat: true
        onTriggered: {
            tempColdToHotActVal = adjustVal(tempColdToHotActVal, targetTemp, tempMinVal, tempMaxVal)

            tempHotToColdActVal = tempMaxVal - (tempColdToHotActVal - tempMinVal)
            targetTemp = adjustTarget(tempColdToHotActVal, targetTemp, tempMinVal, tempMaxVal)
            var endTime = new Date()
            currentTimeMS = endTime - startTime
            timeActVal = Math.floor(currentTimeMS / 1000)

            ttGauge.tempVal = tempColdToHotActVal
            ttGauge.timeVal = timeActVal
            ttGauge2.tempVal = 50 + (0.05 - (Math.random() / 10))
            ttGauge2.timeVal = timeActVal
            ttGauge3.tempVal = tempHotToColdActVal
            ttGauge3.timeVal = timeActVal
            ttGauge4.tempVal = tempColdToHotActVal
            ttGauge4.timeVal = timeActVal
        }
    }


}
