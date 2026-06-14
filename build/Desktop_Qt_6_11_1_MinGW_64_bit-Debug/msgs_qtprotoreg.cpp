
#include "msgs.qpb.h"

#include <QtProtobuf/qprotobufregistration.h>

namespace msgs::v1 {
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarMessage(qRegisterProtobufType<Message>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarSendMessageRequest(qRegisterProtobufType<SendMessageRequest>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarMessageResponse(qRegisterProtobufType<MessageResponse>);
static bool RegisterMsgsProtobufTypes = [](){ qRegisterProtobufTypes(); return true; }();
} // namespace msgs::v1

