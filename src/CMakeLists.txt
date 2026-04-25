cmake_minimum_required(VERSION 3.5)

#add_subdirectory(src)
#add_subdirectory(core)
#add_subdirectory(infrastructure)
#add_subdirectory(presentation)


add_executable(wch-desktop
  app/main.cpp
  ../test.qrc
  presentation/main/mainwindow.cpp
  presentation/main/mainwindow.h
  presentation/main/mainwindow.ui
  presentation/auth/logindialog.cpp
  presentation/auth/logindialog.h
  presentation/auth/logindialog.ui
  core/domain/user.cpp
  core/usecases/loginusecase.cpp
  core/ports/authservice.h
  infrastructure/network/qtauthservice.h
  infrastructure/network/qtauthservice.cpp
  presentation/chat/chatlistmodel.cpp
  presentation/chat/chatdelegate.cpp
)

target_include_directories(wch-desktop PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(wch-desktop PRIVATE Qt5::Widgets)
