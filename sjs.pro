VERSION = 	0.0.1
TEMPLATE = 	app
HEADERS = 	sessionjs.h \
		mainwindow.h \
                dbustypes.h \
                managerproxy.h \
                sessionproxy.h \
                $$DBUS_INTERFACE_HEADERS \
                $$DBUS_ADAPTOR_HEADERS

SOURCES = 	sessionjs.cpp \
		main.cpp \
		mainwindow.cpp \
                dbustypes.cpp \
                managerproxy.cpp \
                sessionproxy.cpp

MOC_DIR = .moc
OBJECTS_DIR = .obj
MGEN_OUTDIR = .gen

DBUS_ADAPTORS = dbus/net.connman.notification.xml

DBUS_INTERFACES = 	dbus/net.connman.manager.xml \
			dbus/net.connman.service.xml \
			dbus/net.connman.session.xml

system(qdbusxml2cpp -i dbustypes.h -p manager_interface.h: dbus/net.connman.manager.xml)
system(qdbusxml2cpp -i dbustypes.h -p service_interface.h: dbus/net.connman.service.xml)
system(qdbusxml2cpp -i dbustypes.h -p session_interface.h: dbus/net.connman.session.xml)

QT += webkit dbus

RESOURCES = resources/sjs.qrc

DISTFILES = resources/index.html

MAKE_CLEAN += $$OBJECTS_DIR/*.o
MAKE_DISTCLEAN += \
    $$MOC_DIR/* $$MOC_DIR \
    $$OBJECTS_DIR/* $$OBJECTS_DIR \
    $$MGEN_OUTDIR/* $$MGEN_OUTDIR

