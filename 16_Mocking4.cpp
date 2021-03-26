#include <stdio.h>
struct Packet {};

class ConcreatePacketStream {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatePacketStream - AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const {
		printf("ConcreatePacketStream - GetPacket\n");
		return nullptr;
	}
};

// 컴파일 타임에 타입을 교체할 수 있다.
//  => Policy based Design
//     단위 전략
//      - 암묵적인 인터페이스의 약속
template <typename PacketStream>
class PacketReader {
public:
	void ReadPacket(PacketStream* stream, size_t packet_num) {
		stream->AppendPacket(nullptr);
		stream->GetPacket(packet_num);
	}
};
//-----
#include <gmock/gmock.h>

class MockPacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const));
};

TEST(PacketReaderTest, ReadPacket) {
	PacketReader<MockPacketStream> reader;
	MockPacketStream stream;

	EXPECT_CALL(stream, AppendPacket(nullptr));
	EXPECT_CALL(stream, GetPacket(100));

	reader.ReadPacket(&stream, 100);
}

#if 0
int main() {
	PacketReader<ConcreatePacketStream> reader;  // !!!
	ConcreatePacketStream stream;

	reader.ReadPacket(&stream, 42);
}
#endif




