/****************************************************************************
** Meta object code from reading C++ file 'msgs.qpb.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../msgs.qpb.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'msgs.qpb.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN4msgs2v17MessageE_t {};
} // unnamed namespace

template <> constexpr inline auto msgs::v1::Message::qt_create_metaobjectdata<qt_meta_tag_ZN4msgs2v17MessageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "msgs::v1::Message",
        "id_proto",
        "chatId",
        "senderId",
        "content"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'id_proto'
        QtMocHelpers::PropertyData<QString>(1, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'chatId'
        QtMocHelpers::PropertyData<QString>(2, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'senderId'
        QtMocHelpers::PropertyData<QString>(3, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'content'
        QtMocHelpers::PropertyData<QString>(4, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Message, qt_meta_tag_ZN4msgs2v17MessageE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject msgs::v1::Message::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QProtobufMessage>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4msgs2v17MessageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4msgs2v17MessageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN4msgs2v17MessageE_t>.metaTypes,
    nullptr
} };

void msgs::v1::Message::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Message *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->id_proto(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->chatId(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->senderId(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->content(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setId_proto(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setChatId(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setSenderId(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setContent(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN4msgs2v118SendMessageRequestE_t {};
} // unnamed namespace

template <> constexpr inline auto msgs::v1::SendMessageRequest::qt_create_metaobjectdata<qt_meta_tag_ZN4msgs2v118SendMessageRequestE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "msgs::v1::SendMessageRequest",
        "chatId",
        "senderId",
        "content"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'chatId'
        QtMocHelpers::PropertyData<QString>(1, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'senderId'
        QtMocHelpers::PropertyData<QString>(2, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'content'
        QtMocHelpers::PropertyData<QString>(3, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SendMessageRequest, qt_meta_tag_ZN4msgs2v118SendMessageRequestE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject msgs::v1::SendMessageRequest::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QProtobufMessage>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4msgs2v118SendMessageRequestE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4msgs2v118SendMessageRequestE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN4msgs2v118SendMessageRequestE_t>.metaTypes,
    nullptr
} };

void msgs::v1::SendMessageRequest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<SendMessageRequest *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->chatId(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->senderId(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->content(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setChatId(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setSenderId(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setContent(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN4msgs2v115MessageResponseE_t {};
} // unnamed namespace

template <> constexpr inline auto msgs::v1::MessageResponse::qt_create_metaobjectdata<qt_meta_tag_ZN4msgs2v115MessageResponseE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "msgs::v1::MessageResponse",
        "msg_p",
        "msgs::v1::Message*",
        "hasMsg"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'msg_p'
        QtMocHelpers::PropertyData<msgs::v1::Message*>(1, 0x80000000 | 2, QMC::Readable | QMC::Writable | QMC::Designable | QMC::Stored | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'hasMsg'
        QtMocHelpers::PropertyData<bool>(3, QMetaType::Bool, QMC::DefaultPropertyFlags),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MessageResponse, qt_meta_tag_ZN4msgs2v115MessageResponseE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject msgs::v1::MessageResponse::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QProtobufMessage>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4msgs2v115MessageResponseE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4msgs2v115MessageResponseE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN4msgs2v115MessageResponseE_t>.metaTypes,
    nullptr
} };

void msgs::v1::MessageResponse::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<MessageResponse *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<msgs::v1::Message**>(_v) = _t->msg_p(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->hasMsg(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMsg_p(*reinterpret_cast<msgs::v1::Message**>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN4msgs2v124Message_QtProtobufNestedE_t {};
} // unnamed namespace

template <> constexpr inline auto msgs::v1::Message_QtProtobufNested::qt_create_metaobjectdata<qt_meta_tag_ZN4msgs2v124Message_QtProtobufNestedE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "msgs::v1::Message_QtProtobufNested",
        "QtProtobufFieldEnum",
        "Id_protoProtoFieldNumber",
        "ChatIdProtoFieldNumber",
        "SenderIdProtoFieldNumber",
        "ContentProtoFieldNumber"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'QtProtobufFieldEnum'
        QtMocHelpers::EnumData<QtProtobufFieldEnum>(1, 1, QMC::EnumIsScoped).add({
            {    2, QtProtobufFieldEnum::Id_protoProtoFieldNumber },
            {    3, QtProtobufFieldEnum::ChatIdProtoFieldNumber },
            {    4, QtProtobufFieldEnum::SenderIdProtoFieldNumber },
            {    5, QtProtobufFieldEnum::ContentProtoFieldNumber },
        }),
    };
    return QtMocHelpers::metaObjectData<void, qt_meta_tag_ZN4msgs2v124Message_QtProtobufNestedE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}

static constexpr auto qt_staticMetaObjectContent_ZN4msgs2v124Message_QtProtobufNestedE =
    msgs::v1::Message_QtProtobufNested::qt_create_metaobjectdata<qt_meta_tag_ZN4msgs2v124Message_QtProtobufNestedE_t>();
static constexpr auto qt_staticMetaObjectStaticContent_ZN4msgs2v124Message_QtProtobufNestedE =
    qt_staticMetaObjectContent_ZN4msgs2v124Message_QtProtobufNestedE.staticData;
static constexpr auto qt_staticMetaObjectRelocatingContent_ZN4msgs2v124Message_QtProtobufNestedE =
    qt_staticMetaObjectContent_ZN4msgs2v124Message_QtProtobufNestedE.relocatingData;

Q_CONSTINIT const QMetaObject msgs::v1::Message_QtProtobufNested::staticMetaObject = { {
    nullptr,
    qt_staticMetaObjectStaticContent_ZN4msgs2v124Message_QtProtobufNestedE.stringdata,
    qt_staticMetaObjectStaticContent_ZN4msgs2v124Message_QtProtobufNestedE.data,
    nullptr,
    nullptr,
    qt_staticMetaObjectRelocatingContent_ZN4msgs2v124Message_QtProtobufNestedE.metaTypes,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN4msgs2v135SendMessageRequest_QtProtobufNestedE_t {};
} // unnamed namespace

template <> constexpr inline auto msgs::v1::SendMessageRequest_QtProtobufNested::qt_create_metaobjectdata<qt_meta_tag_ZN4msgs2v135SendMessageRequest_QtProtobufNestedE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "msgs::v1::SendMessageRequest_QtProtobufNested",
        "QtProtobufFieldEnum",
        "ChatIdProtoFieldNumber",
        "SenderIdProtoFieldNumber",
        "ContentProtoFieldNumber"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'QtProtobufFieldEnum'
        QtMocHelpers::EnumData<QtProtobufFieldEnum>(1, 1, QMC::EnumIsScoped).add({
            {    2, QtProtobufFieldEnum::ChatIdProtoFieldNumber },
            {    3, QtProtobufFieldEnum::SenderIdProtoFieldNumber },
            {    4, QtProtobufFieldEnum::ContentProtoFieldNumber },
        }),
    };
    return QtMocHelpers::metaObjectData<void, qt_meta_tag_ZN4msgs2v135SendMessageRequest_QtProtobufNestedE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}

static constexpr auto qt_staticMetaObjectContent_ZN4msgs2v135SendMessageRequest_QtProtobufNestedE =
    msgs::v1::SendMessageRequest_QtProtobufNested::qt_create_metaobjectdata<qt_meta_tag_ZN4msgs2v135SendMessageRequest_QtProtobufNestedE_t>();
static constexpr auto qt_staticMetaObjectStaticContent_ZN4msgs2v135SendMessageRequest_QtProtobufNestedE =
    qt_staticMetaObjectContent_ZN4msgs2v135SendMessageRequest_QtProtobufNestedE.staticData;
static constexpr auto qt_staticMetaObjectRelocatingContent_ZN4msgs2v135SendMessageRequest_QtProtobufNestedE =
    qt_staticMetaObjectContent_ZN4msgs2v135SendMessageRequest_QtProtobufNestedE.relocatingData;

Q_CONSTINIT const QMetaObject msgs::v1::SendMessageRequest_QtProtobufNested::staticMetaObject = { {
    nullptr,
    qt_staticMetaObjectStaticContent_ZN4msgs2v135SendMessageRequest_QtProtobufNestedE.stringdata,
    qt_staticMetaObjectStaticContent_ZN4msgs2v135SendMessageRequest_QtProtobufNestedE.data,
    nullptr,
    nullptr,
    qt_staticMetaObjectRelocatingContent_ZN4msgs2v135SendMessageRequest_QtProtobufNestedE.metaTypes,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN4msgs2v132MessageResponse_QtProtobufNestedE_t {};
} // unnamed namespace

template <> constexpr inline auto msgs::v1::MessageResponse_QtProtobufNested::qt_create_metaobjectdata<qt_meta_tag_ZN4msgs2v132MessageResponse_QtProtobufNestedE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "msgs::v1::MessageResponse_QtProtobufNested",
        "QtProtobufFieldEnum",
        "MsgProtoFieldNumber"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'QtProtobufFieldEnum'
        QtMocHelpers::EnumData<QtProtobufFieldEnum>(1, 1, QMC::EnumIsScoped).add({
            {    2, QtProtobufFieldEnum::MsgProtoFieldNumber },
        }),
    };
    return QtMocHelpers::metaObjectData<void, qt_meta_tag_ZN4msgs2v132MessageResponse_QtProtobufNestedE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}

static constexpr auto qt_staticMetaObjectContent_ZN4msgs2v132MessageResponse_QtProtobufNestedE =
    msgs::v1::MessageResponse_QtProtobufNested::qt_create_metaobjectdata<qt_meta_tag_ZN4msgs2v132MessageResponse_QtProtobufNestedE_t>();
static constexpr auto qt_staticMetaObjectStaticContent_ZN4msgs2v132MessageResponse_QtProtobufNestedE =
    qt_staticMetaObjectContent_ZN4msgs2v132MessageResponse_QtProtobufNestedE.staticData;
static constexpr auto qt_staticMetaObjectRelocatingContent_ZN4msgs2v132MessageResponse_QtProtobufNestedE =
    qt_staticMetaObjectContent_ZN4msgs2v132MessageResponse_QtProtobufNestedE.relocatingData;

Q_CONSTINIT const QMetaObject msgs::v1::MessageResponse_QtProtobufNested::staticMetaObject = { {
    nullptr,
    qt_staticMetaObjectStaticContent_ZN4msgs2v132MessageResponse_QtProtobufNestedE.stringdata,
    qt_staticMetaObjectStaticContent_ZN4msgs2v132MessageResponse_QtProtobufNestedE.data,
    nullptr,
    nullptr,
    qt_staticMetaObjectRelocatingContent_ZN4msgs2v132MessageResponse_QtProtobufNestedE.metaTypes,
    nullptr
} };

QT_WARNING_POP
