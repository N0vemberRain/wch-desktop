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
    core/usecases/updateprofileusecase.h core/usecases/updateprofileusecase.cpp
    infrastructure/utils/avatarprovider.h infrastructure/utils/avatarprovider.cpp
    core/ports/chats_service.h
    infrastructure/network/qtchatsservice.h infrastructure/network/qtchatsservice.cpp
    core/usecases/loadchatsforcurrentuserusecase.h core/usecases/loadchatsforcurrentuserusecase.cpp
    presentation/chatinfo/chatinfodialog.h presentation/chatinfo/chatinfodialog.cpp presentation/chatinfo/chatinfodialog.ui
    core/usecases/updatechatusecase.h core/usecases/updatechatusecase.cpp
    core/usecases/createchatusecase.h core/usecases/createchatusecase.cpp
    presentation/chatinfo/createchatdialog.h presentation/chatinfo/createchatdialog.cpp presentation/chatinfo/createchatdialog.ui
    core/usecases/searchusersusecase.h core/usecases/searchusersusecase.cpp
    presentation/chat/chatsfiltermodel.h presentation/chat/chatsfiltermodel.cpp

    presentation/createchat/chattypedialog.h presentation/createchat/chattypedialog.cpp presentation/createchat/chattypedialog.ui
    presentation/createchat/searchuserdialog.h presentation/createchat/searchuserdialog.cpp presentation/createchat/searchuserdialog.ui
    core/domain/users_search_filter.h
    core/domain/user_summary.h
    presentation/createchat/searchusersmodel.h presentation/createchat/searchusersmodel.cpp
    presentation/createchat/usersummarydelegate.h presentation/createchat/usersummarydelegate.cpp
    app/appcontroller.h app/appcontroller.cpp
    core/usecases/logoutusecase.h core/usecases/logoutusecase.cpp
    presentation/chatinfo/chatparticipantsmodel.h presentation/chatinfo/chatparticipantsmodel.cpp
    presentation/chatinfo/participantdelegate.h presentation/chatinfo/participantdelegate.cpp
    core/usecases/loadparticipantsusecase.h core/usecases/loadparticipantsusecase.cpp
    core/domain/chat_participant.h
    core/usecases/addparticipantusecase.h core/usecases/addparticipantusecase.cpp



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