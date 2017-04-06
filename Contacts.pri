INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/contacts.h \
    $$PWD/contactmodel.h

ios{
    LIBS += -framework Foundation -framework Contacts
    OBJECTIVE_SOURCES += $$PWD/ios/contacts.mm
}else:android{
    QT += androidextras
    SOURCES +=  \
        $$PWD/android/contacts.cpp

    QCALENDAR_JAVASRC.path = /src/net/reea
    QCALENDAR_JAVASRC.files += $$files($$PWD/android/src/net/reea/*)
    INSTALLS += QCALENDAR_JAVASRC

    DISTFILES += $$PWD/android/Java/ContactsManager.java

}else:winrt{
    SOURCES += $$PWD/winrt/contacts.cpp
}else{
    SOURCES += $$PWD/desktop/contacts.cpp
}
OTHER_FILES += \
        $$PWD/README.md \
        $$files($$PWD/android/src/net/reea/*)

SOURCES += \
    $$PWD/contactmodel.cpp \

