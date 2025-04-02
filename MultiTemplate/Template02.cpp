#include "MultiExtend.h"

#include "Math/Matrix.h"

class Entity
{
public:
	Entity(Entity&) = delete;

	static void Init(std::string _Path) 
	{
		Get().m_fileA = new MULTIEXTEND_FILE(_Path);
		Get().m_fileA->Open(true);
	};

	static void write(std::string message)
	{
		if (Get().m_fileA != nullptr)
		{
			Get().m_fileA->Write(message);
		}
	};

	static void print() 
	{
		if (Get().m_fileA != nullptr)
		{
			Get().m_fileA->Print();
		}
	};

private:
	Entity():m_fileA(nullptr) {};

	virtual ~Entity() 
	{
		if (m_fileA != nullptr)
		{
			m_fileA->Close();

			delete m_fileA;
			m_fileA = nullptr;
		}
	};

	static Entity& Get() 
	{
		static Entity instance;
		return instance;
	};

private:
	MULTIEXTEND_FILE* m_fileA;
};

int main(int argc, char** argv)
{
	MultiExtend::Message::Init();

	MultiExtend::MsgLog("MsgLogTestCritical",MultiExtend::Critical);
	MultiExtend::MsgLog("MsgLogTestWarning",MultiExtend::Warning);
	
	Entity::Init("./Template02/Template02");

	Entity::write("Template02 test line.");
	Entity::print();

	Vector3 v{1,1,1};
	Matrix4x4 m{1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1};

	auto a = m * v;

	std::cin.get();

	return 0;
}