#include "MultiExtend.h"

#include "Math/Vector.h"
#include "Math/Matrix.h"

int main(int argc, char* argv[])
{
	MultiExtend::Message::Init();

	MultiExtend::Matrix<float, 4, 4> matrixInstance{ 1,2,3,4,5,6,7,8 };
}