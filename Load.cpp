#include "Load.h"

using namespace Load;

void Obj::Read(const std::string obj_model_filepath)
{
	std::cout << "reading" << std::endl;
	using namespace std;
	ifstream file(obj_model_filepath);

	if (!file.is_open())
	{
		cout << "Error opening the file: " << obj_model_filepath << endl;
		return;
	}

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;

	string line;

	while (getline(file, line))
	{
		istringstream iss(line);
		string type;

		iss >> type;

		if (type == "v")
		{
			glm::vec3 position;
			iss >> position.x >> position.y >> position.z;
			positions.push_back(position);
		}
		else if (type == "vn")
		{
			glm::vec3 normal;
			iss >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		else if (type == "vt")
		{
			glm::vec2 texcoord;
			iss >> texcoord.x >> texcoord.y;
			texcoords.push_back(texcoord);
		}
		else if (type == "f")
		{
			for (int i = 0; i < 3; ++i)
			{
				string vertexData;
				iss >> vertexData;

				istringstream viss(vertexData);
				string index;

				getline(viss, index, '/');
				int positionIndex = stoi(index) - 1;

				getline(viss, index, '/');
				int texcoordIndex = stoi(index) - 1;

				getline(viss, index, '/');
				int normalIndex = stoi(index) - 1;
			}
		}

		else if (type == "mtlib")
		{
			std::string matFileName;
			iss >> matFileName;

			Obj::ReadMaterial(matFileName);
		}
	}
}

void Obj::ReadMaterial(const std::string mtl_fileName)
{
	using namespace std;
	ifstream file(mtl_fileName);

	if (!file.is_open())
	{
		cout << "Error opening the file: " << mtl_fileName << endl;
		return;
	}

	string line;

	while (getline(file, line))
	{
		istringstream iss(line);
		string type;

		iss >> type;

		if (type == "ka")
		{
			
		}
		else if (type == "kd")
		{
			
		}
		else if (type == "ks")
		{
			
		}
		else if (type == "ns")
		{
			
		}
		else if (type == "map_Kd")
		{
			string texFileName;
			iss >> texFileName;
			Obj::ReadTexture(texFileName);
		}
	}
}

void Obj::ReadTexture(const std::string tex_fileName)
{

}


void Obj::Send(void)
{

}

void Obj::Draw(glm::vec3 position, glm::vec3 orientation)
{

}