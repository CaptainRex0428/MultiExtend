#include "MultiExtend.h"

#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Math/Color.h"

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
	Entity() :m_fileA(nullptr) {};

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

	MultiExtend::MsgLog("MsgLogTestCritical", MultiExtend::Critical);
	MultiExtend::MsgLog("MsgLogTestWarning", MultiExtend::Warning);

	Entity::Init("./Template02/Template02");

	Entity::write("Template02 test line.");
	Entity::print();

	Vector3 vector(2);

	float len = vector.Length();
	Vector3 NVector = vector.Normalize();

	Vector3 scaleNVector = NVector * 5.f;

	auto tMTX = MultiExtend::MTXTranslation(5.f,1.f,2.f);
	auto tNVector = tMTX * scaleNVector;

	std::cout << vector << std::endl;
	std::cout << len << std::endl;
	std::cout << NVector << std::endl;
	std::cout << scaleNVector << std::endl;
	
	std::cout << tNVector[0] << "," << tNVector[1] << "," << tNVector[2] << std::endl;

	Color<float,8> color((int)0, 0, 0);

	std::cout << color.GetSaturation() << std::endl;

	std::cin.get();

	return 0;
}