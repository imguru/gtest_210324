
#include <stdio.h>

struct Packet {};
struct PacketStream {
	virtual ~PacketStream() {}

	virtual void AppendPacket(Packet* new_packet) = 0;
	virtual const Packet* GetPacket(size_t packet_number) const = 0;
};

class ConcreatePacketStream : public PacketStream {
public:
	void AppendPacket(Packet* new_packet) override {
		printf("ConcreatePacketStream - AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const override {
		printf("ConcreatePacketStream - GetPacket\n");
		return nullptr;
	}
};

class PacketReader {
public:
	void ReadPacket(PacketStream* stream, size_t packet_num) {
		stream->AppendPacket(nullptr);
		stream->GetPacket(packet_num);
	}
};

#include <gmock/gmock.h>

class MockPacketStream : public PacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet), (override));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const, override));
};

TEST(PacketReaderTest, ReadPacket) {
	PacketReader reader;
	MockPacketStream stream;

	EXPECT_CALL(stream, AppendPacket(nullptr));
	EXPECT_CALL(stream, GetPacket(100));

	reader.ReadPacket(&stream, 100);
}

#if 0
int main() {
	PacketReader reader;
	ConcreatePacketStream stream;

	reader.ReadPacket(&stream, 42);
}
#endif




