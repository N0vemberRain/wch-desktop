add_executable(wch-desktop
    app/main.cpp

    utils.cpp

    presentation/main/mainwindow.cpp
    presentation/main/mainwindow.h
    presentation/main/mainwindow.ui

    presentation/auth/logindialog.cpp
    presentation/auth/logindialog.h
    presentation/auth/logindialog.ui

    presentation/chat/chatlistmodel.cpp
    presentation/chat/chatdelegate.cpp
    presentation/chat/chatslistwgt.cpp

    presentation/sidebar/sidebarwidget.cpp
    presentation/sidebar/sidebarwidget.ui

    presentation/chatwindow/chathistorymodel.cpp
    presentation/chatwindow/messagedelegate.cpp
    presentation/chatwindow/chatswitcherdialog.cpp
    presentation/chatwindow/chatwgt.cpp
    presentation/chatwindow/chatwgt.ui
    presentation/chatwindow/messageitem.h

    core/domain/user.cpp
    core/domain/message.h
    core/domain/chat.h
    core/domain/sendmessageresult.h

    core/usecases/loginusecase.cpp
    core/usecases/loginusecase.h

    core/usecases/sendmessageusecase.cpp
    core/usecases/sendmessageusecase.h

    core/ports/authservice.h
    core/ports/msgservice.h

    infrastructure/network/qtauthservice.cpp
    infrastructure/network/qtmessageservice.cpp

    mock/mockchatfactory.cpp

    ../test.qrc
    core/domain/session.h core/domain/session.cpp
    core/domain/messagestatus.h
    core/ports/auth_error.h
    core/usecases/login_error.h
    presentation/auth/login_error_text.h
    core/domain/token.h
    core/ports/session_storage.h
    app/sessionmanager.h app/sessionmanager.cpp
    infrastructure/utils/qtsessionstorage.h infrastructure/utils/qtsessionstorage.cpp
    core/usecases/loadcurrentuserusecase.h core/usecases/loadcurrentuserusecase.cpp
    core/domain/types.h
    core/ports/users_service.h
    core/domain/errors.h
    infrastructure/network/qtusersservice.h infrastructure/network/qtusersservice.cpp
    app/appcontext.h app/appcontext.cpp
    presentation/navigation/navigationwgt.h presentation/navigation/navigationwgt.cpp
    presentation/navigation/userheaderwgt.h presentation/navigation/userheaderwgt.cpp presentation/navigation/userheaderwgt.ui
    presentation/profile/profiledialog.h presentation/profile/profiledialog.cpp presentation/profile/profiledialog.ui
    presentation/profile/avatarwgt.h presentation/profile/avatarwgt.cpp

)

target_include_directories(wch-desktop PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(wch-desktop PRIVATE
    Qt6::Widgets
    Qt6::Protobuf
    Qt6::Grpc

    wch_proto
    wch_grpc
)