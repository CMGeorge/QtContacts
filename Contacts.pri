INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/contacts.h \
    $$PWD/contactmodel.h

ios{
}else:android{
    QT += androidextras
    SOURCES +=  \
        $$PWD/android/contacts.cpp

    QCALENDAR_JAVASRC.path = /src/net/reea
    QCALENDAR_JAVASRC.files += $$files($$PWD/android/src/net/reea/*)
    INSTALLS += QCALENDAR_JAVASRC

    DISTFILES += $$PWD/android/Java/ContactsManager.java

}else:winrt{
}
OTHER_FILES += \
        $$PWD/README.md \
        $$files($$PWD/android/src/net/reea/*)
warning($$QCALENDAR_JAVASRC.files);

SOURCES += \
    $$PWD/contactmodel.cpp \
    $$PWD/desktop/contacts.cpp
