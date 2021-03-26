// 12_Stub.cpp

#include <iostream>

class NetworkException : public std::exception {
public:
	const char* what() {
		return "Bad network state";
	}
};

struct IConnection {
	virtual ~IConnection() {}

	virtual void Move(int x, int y) = 0;
	virtual void Attack() = 0;

	// 기본 구현을 가지는 추상 메소드 - defender method의 개념
	virtual void foo() {}
	virtual void goo() {}
};

class TCPConnection : public IConnection {
	void Move(int x, int y) override {}
	void Attack() override {}
};

class Player {
	IConnection* connection;
public:
	Player(IConnection* p) : connection(p) {}

	void Move(int x, int y) {
		try {
			connection->Move(x, y);
			// ....
		} catch (NetworkException& e) {
			printf("NetworkException 동작....\n");
			throw e;
		}
	}
};

//-----------
#include <gmock/gmock.h>

class MockConnection : public IConnection {
public:
	MOCK_METHOD(void, Move, (int x, int y), (override));
	MOCK_METHOD(void, Attack, (), (override));
};

using testing::NiceMock;
using testing::Throw;

TEST(PlayerTest, Move) {
	NiceMock<MockConnection> conn;
	Player player(&conn);
	ON_CALL(conn, Move).WillByDefault(Throw(NetworkException()));

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}








