cmake_minimum_required(VERSION 3.5)

#add_subdirectory(src)
#add_subdirectory(core)
#add_subdirectory(infrastructure)
#add_subdirectory(presentation)

add_executable(wch-desktop
  app/main.cpp
  utils.cpp
  ../test.qrc
  presentation/main/mainwindow.cpp
  presentation/main/mainwindow.h
  presentation/main/mainwindow.ui
  presentation/auth/logindialog.cpp
  presentation/auth/logindialog.h
  presentation/auth/logindialog.ui
  core/domain/user.cpp
  core/domain/message.h
  core/domain/chat.h
  core/domain/sendmessageresult.h
  core/usecases/loginusecase.cpp
  core/usecases/sendmessageusecase.cpp
  core/ports/authservice.h
  core/ports/msgservice.h
  infrastructure/network/qtauthservice.cpp
  infrastructure/network/qtmessageservice.cpp
  presentation/chat/chatlistmodel.cpp
  presentation/chat/chatdelegate.cpp
  presentation/chat/chatslistwgt.cpp
  presentation/sidebar/sidebarwidget.ui
  presentation/sidebar/sidebarwidget.cpp
  presentation/chatwindow/chathistorymodel.cpp
  presentation/chatwindow/messagedelegate.cpp
  presentation/chatwindow/chatswitcherdialog.cpp
  presentation/chatwindow/chatwgt.cpp
  presentation/chatwindow/chatwgt.ui
  presentation/chatwindow/messageitem.h
  mock/mockchatfactory.cpp
  core/usecases/sendmessageusecase.h
)

target_include_directories(wch-desktop PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(wch-desktop PRIVATE Qt6::Widgets Qt6::Network)

