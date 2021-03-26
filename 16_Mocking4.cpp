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
template <typename PacketStream>
class PacketReader {
public:
	void ReadPacket(PacketStream* stream, size_t packet_num) {
		stream->AppendPacket(nullptr);
		stream->GetPacket(packet_num);
	}
};

int main() {
	PacketReader<ConcreatePacketStream> reader;  // !!!
	ConcreatePacketStream stream;

	reader.ReadPacket(&stream, 42);
}
