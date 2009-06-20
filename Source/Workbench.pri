CONFIG += debug
LIBS += -L../../../Static
INCLUDEPATH += ../../Libs
QMAKE_CXXFLAGS += -Werror -Wextra -Wpointer-arith -Wcast-qual -W

unix {
    debug:OBJECTS_DIR = $${OUT_PWD}/.obj/debug-shared
    release:OBJECTS_DIR = $${OUT_PWD}/.obj/release-shared

    debug:MOC_DIR = $${OUT_PWD}/.moc/debug-shared
    release:MOC_DIR = $${OUT_PWD}/.moc/release-shared

    RCC_DIR = $${OUT_PWD}/.rcc
    UI_DIR = $${OUT_PWD}/.uic
}

