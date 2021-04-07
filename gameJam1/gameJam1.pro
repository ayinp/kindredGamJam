QT += widgets
QT += multimedia

CONFIG += gui
CONFIG += c++14

HEADERS    = \
    animation.h \
    button.h \
    card.h \
    continuous.h \
    sprites.h \
    window.h \
    graphics.h \
    vec2d.h \
    plugin.h \
    world.h

SOURCES     = \
    animation.cpp \
    button.cpp \
    card.cpp \
    continuous.cpp \
    main.cpp \
    graphics.cpp \
    sprites.cpp \
    vec2d.cpp \
    plugin.cpp \
    world.cpp

DISTFILES += \
    notes.txt

ASSET_SOURCE_PATH = $$shell_path($$clean_path("$$PWD\\Data\\"))

windows {
    specified_configs=$$find(CONFIG, "\b(debug|release)\b")
    build_subdir=$$last(specified_configs)
    ASSET_DESTINATION = $$shell_path($$clean_path("$$OUT_PWD\\$$build_subdir\\Data\\"))

    copydata.commands = $(COPY_DIR) \"$$ASSET_SOURCE_PATH\" \"$$ASSET_DESTINATION\"
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}

macos {
    assetFiles.files = $$files($$ASSET_SOURCE_PATH/*)
    assetFiles.path = Contents\MacOs\Data
    QMAKE_BUNDLE_DATA += assetFiles
}



