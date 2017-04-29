set(VILLA_CONTROL_SRC
    "main.cpp"
    "eventmanager.cpp"
    "connection.cpp"
    "ttyconnection.cpp"
    "serialport.cpp"
    "actuator.cpp"
    "sensor.cpp"
    "device.cpp"
    "devicewde1.cpp"
)

add_executable(${PROJECT_NAME} ${VILLA_CONTROL_SRC})

target_link_libraries(${PROJECT_NAME} jansson)

