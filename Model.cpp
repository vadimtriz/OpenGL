#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include "Model.h"

Model::Model(VerticesTypePtr vertices,
			 FacesTypePtr faces,
			 NormalsTypePtr normals,
			 TexCoordsTypePtr tex_coords)
:_vertices(vertices),
 _faces(faces),
 _normals(normals),
 _texcoords(tex_coords)
{
	assert(vertices != nullptr && "�������� 'vertices' ������������ Model �� ����� ����� �������� nullptr!");
	assert(faces != nullptr && "�������� 'faces' ������������ Model �� ����� ����� �������� nullptr!");
	assert(normals != nullptr && "�������� 'normals' ������������ Model �� ����� ����� �������� nullptr!");
	assert(tex_coords != nullptr && "�������� 'tex_coords' ������������ Model �� ����� ����� �������� nullptr!");
}

void Model::draw()
{
	FacesType &faces = *_faces;
	VerticesType &vertices = *_vertices;
	NormalsType &normals = *_normals;
	TexCoordsType &texcoords = *_texcoords;

	unsigned face_count = faces.size();
	for(unsigned face = 0; face < face_count; ++face){
		unsigned vertex_count = faces[face].size();
		switch(vertex_count){
		case 3: glBegin(GL_TRIANGLES); break;
		case 4: glBegin(GL_QUADS); break;
		default: glBegin(GL_POLYGON); break;
		}

		glNormal3fv( &normals[face][0]);
		for(unsigned vertex = 0; vertex < vertex_count; ++vertex){
			glTexCoord2fv(&texcoords[face][vertex][0]);
			glVertex3fv(&vertices[faces[face][vertex]][0]);
		}

		glEnd();
	}
}

void Model::read_model_line(std::ifstream &file, std::string &buffer) {
	do {
		std::getline(file, buffer);
	} while (buffer[0] == '#' || buffer.length() == 0);
}

Model::Model(const char *filename)
{
	_vertices  = std::make_shared<VerticesType>();
	_faces     = std::make_shared<FacesType>();
	_normals   = std::make_shared<NormalsType>();
	_texcoords = std::make_shared<TexCoordsType>();

	FacesType &faces = *_faces;
	VerticesType &vertices = *_vertices;
	NormalsType &normals = *_normals;
	TexCoordsType &texcoords = *_texcoords;

	unsigned vertex_count;
	unsigned face_count;

	std::ifstream file;
	std::string buffer;

	file.open(filename);
	if (not file)
		throw std::runtime_error("�� ���� ������� ���� ������!");


	read_model_line(file, buffer);
	std::stringstream (buffer) >> vertex_count;
	vertices.resize(vertex_count);
	for(unsigned i = 0; i < vertex_count; ++i){
		read_model_line(file, buffer);
		std::stringstream(buffer) >> vertices[i].x >> vertices[i].y >> vertices[i].z;
	}

	read_model_line(file, buffer);
	std::stringstream (buffer) >> face_count;
	faces.resize(face_count);
	for(unsigned face = 0; face < face_count; ++face){
			read_model_line(file, buffer);
			auto ss = std::stringstream(buffer);
			unsigned vc;
			ss >> vc;
			faces[face].resize(vc);
			for(unsigned v = 0; v < vc; ++v)
				ss >> faces[face][v];
		}

	normals.resize(face_count);
	for (unsigned face = 0; face < face_count; ++face){
		read_model_line(file, buffer);
		std::stringstream(buffer) >> normals[face].x >> normals[face].y >> normals[face].z;
	}

	texcoords.resize(face_count);
	for (unsigned face = 0; face < face_count; ++face){
		texcoords[face].resize(faces[face].size());
		read_model_line(file, buffer);
		auto ss = std::stringstream(buffer);
		for(unsigned v = 0; v <texcoords[face].size(); ++v)
			ss >> texcoords[face][v].s >> texcoords[face][v].t;
		}
}
