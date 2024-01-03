import qbs

CppApplication {
    Depends { name: "Qt.quick" }

    install: true

    // Additional import path used to resolve QML modules in Qt Creator's code model
    property pathList qmlImportPaths: []

    files: [
        "GameAssets/f1.png",
        "GameAssets/f2.png",
        "Models/actormodel.cpp",
        "Models/actormodel.h",
        "Models/mygamemap.cpp",
        "Models/mygamemap.h",
        "main.cpp",
        "questmodel.cpp",
        "questmodel.h",
        "resource.qrc",
    ]
    Group {
        files: [
            "main.qml",
        ]
        Qt.core.resourcePrefix: "ActionSceneTest/"
        fileTags: ["qt.qml.qml", "qt.core.resource_data"]
    }
}
