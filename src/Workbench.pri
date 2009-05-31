CONFIG -= release
LIBS += -L../../../static
INCLUDEPATH += ../../libs \
    ../../../inc
QMAKE_CXXFLAGS += -Werror -Wextra -Wpointer-arith -Wcast-qual

include(../inc/Viewer/Viewer.pro)

unix {
    debug:OBJECTS_DIR = $${OUT_PWD}/.obj/debug-shared
    release:OBJECTS_DIR = $${OUT_PWD}/.obj/release-shared

    debug:MOC_DIR = $${OUT_PWD}/.moc/debug-shared
    release:MOC_DIR = $${OUT_PWD}/.moc/release-shared

    RCC_DIR = $${OUT_PWD}/.rcc
    UI_DIR = $${OUT_PWD}/.uic
}

