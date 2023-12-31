import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CPP 1.0
import QtQml
ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Action Test")
    property double standartScale: 640.0
    property double standartScaleY: 480.0
    property string jopka: "black";
    color: jopka

    Image
    {
        id:back
        source: "qrc:/resources/GameAssets/back.jpg";
        sourceSize.height: parent.height
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit

        GridView
        {
            id:mapRoot

            property int jopaX: 0
            property int jopaY: 0

            onWidthChanged: {mapRoot.model.updateParentScalw(mapRoot.width,mapRoot.height)}
            onHeightChanged: {mapRoot.model.updateParentScalw(mapRoot.width,mapRoot.height)}

            anchors.fill: parent

            model: MyGameMap{}

            cellHeight: parent.height/8
            cellWidth: parent.width/11

            //onJopaXChanged: {mapRoot.model.targetCell(jopaX*mapRoot.width/standartScale - mapRoot.height/22,jopaY*mapRoot.height/standartScaleY - mapRoot.height/16)}
            //onJopaYChanged: {mapRoot.model.targetCell(jopaX*mapRoot.width/standartScale - mapRoot.height/22,jopaY*mapRoot.height/standartScaleY - mapRoot.height/16)}

            flickableDirection: Flickable.AutoFlickIfNeeded
            delegate:Rectangle
            {

                width: mapRoot.cellWidth;
                height: mapRoot.cellHeight;
                color: "transparent";
                border{
                    color:"yellow"
                    width: 3
                }
                Text {
                    text: display
                    color: "yellow"
                    anchors.centerIn: parent
                }
                Image {
                    source: back_sprite
                    sourceSize.height: parent.height
                    fillMode: Image.PreserveAspectFit
                }

            }
        }
        GridView
        {
            id:actorRoot
            anchors.fill: parent

            model: ActorModel{}

            property double xRelative: 0
            property double yRelative: 0

            cellHeight: parent.height
            cellWidth: parent.width

            property int xScaled : xRelative*actorRoot.width/standartScale
            property int yScaled : yRelative*actorRoot.height/standartScaleY

            property bool moveYFlag: false
            property bool moveXFlag: false

            flickableDirection: Flickable.AutoFlickIfNeeded

            //onXRelativeChanged: {mapRoot.jopaX = xScaled}
            //onYRelativeChanged: {mapRoot.jopaY = yScaled}

            focus: true
            Keys.onPressed:  {
                if(event.key === Qt.Key_W)
                {
                    if(mapRoot.model.checkColision(xScaled, yScaled,1))
                    {
                        actorRoot.model.setRelativePositon(3);
                        moveYFlag = true
                    }
                    else
                    {
                        moveYFlag = false;
                    }
                }
                if(event.key === Qt.Key_S)
                {
                    if(mapRoot.model.checkColision(xScaled,yScaled,3))
                    {
                        actorRoot.model.setRelativePositon(4);
                        moveYFlag = true
                    }
                    else
                    {
                        moveYFlag = false;
                    }
                }
                if(event.key === Qt.Key_D)
                {
                    if(mapRoot.model.checkColision(xScaled,yScaled,4))
                    {
                        actorRoot.model.setRelativePositon(1);
                        moveXFlag = true
                    }
                }
                if(event.key === Qt.Key_A)
                {
                    if(mapRoot.model.checkColision(xScaled,yScaled,2))
                    {
                        actorRoot.model.setRelativePositon(2);
                        moveXFlag = true
                    }
                    else
                    {
                        moveXFlag = false;
                    }
                }
            }
            Keys.onReleased: {if(event.key === Qt.Key_W){moveYFlag = false;actorRoot.model.updateRelativePosition(actorRoot.xRelative,actorRoot.yRelative) }
                              if(event.key === Qt.Key_S){moveYFlag = false;actorRoot.model.updateRelativePosition(actorRoot.xRelative,actorRoot.yRelative) }
                              if(event.key === Qt.Key_D){moveXFlag = false;actorRoot.model.updateRelativePosition(actorRoot.xRelative,actorRoot.yRelative) }
                              if(event.key === Qt.Key_A){moveXFlag = false;actorRoot.model.updateRelativePosition(actorRoot.xRelative,actorRoot.yRelative) }}

            delegate:
            RowLayout
            {
                id:actorArea

                width: actorRoot.width
                height: actorRoot.height
                Component.onCompleted:
                {
                    regNewPosition();
                }
                function regNewPosition()
                {
                    actorRoot.xRelative = actor_x
                    actorRoot.yRelative = actor_y
                }
                Rectangle
                {
                    id:actor

                    Layout.minimumWidth: actorArea.width/11
                    Layout.minimumHeight: actorArea.height/8

                    Layout.alignment: Qt.AlignTop

                    Layout.leftMargin:  actorRoot.xScaled
                    Layout.topMargin: actorRoot.yScaled

                    color: "transparent"

                    border{
                        color:"red"
                        width: 3
                    }

                    Image {
                        id: actorSprite
                        source: actor_frame

                        sourceSize.width: actor.width*actor_;
                        anchors.centerIn: parent
                        fillMode: Image.PreserveAspectFit
                    }
                }
                SequentialAnimation
                {
                    id:movement
                    NumberAnimation {
                        target: actorRoot
                        property: "yRelative"
                        from: actorRoot.yRelative
                        to: actor_y;
                        duration: 1000
                    }
                    loops: Animation.Infinite
                    running: actorRoot.moveYFlag
                }
                SequentialAnimation
                {
                    id:movement2
                    NumberAnimation {
                        target: actorRoot
                        property: "xRelative"
                        from: actorRoot.xRelative
                        to: actor_x;
                        duration: 1000
                    }
                    loops: Animation.Infinite
                    running: actorRoot.moveXFlag
                }
            }
        }
    }
}
