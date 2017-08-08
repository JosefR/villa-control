set(VILLA_CONTROL_SRC
    "main.cpp"
    "eventmanager.cpp"
    "connection.cpp"
    "serverconnection.cpp"
    "clientconnection.cpp"
    "internalconnection.cpp"
    "ttyconnection.cpp"
    "udsconnection.cpp"
    "udsserverconnection.cpp"
    "tcpconnection.cpp"
    "tcpclientconnection.cpp"
    "serialport.cpp"
    "actuator.cpp"
    "sensor.cpp"
    "device.cpp"
    "devicewde1.cpp"
    "program.cpp"
)

set(VILLA_CONTROL_LIBS
    jansson
)

add_executable(${PROJECT_NAME} ${VILLA_CONTROL_SRC})
target_link_libraries(${PROJECT_NAME} ${VILLA_CONTROL_LIBS})
