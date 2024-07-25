#ifndef E3D_2_H
#define E3D_2_H

#include <vector>
#include <cmath>
#include <math.h>
#include <windows.h>

using namespace std;

namespace e3d {

	float _M_PI = 3.1415926f;
	float MPI = _M_PI / 180.0f;

	float AspectRadio, NearPlace, FarPlace;

	struct Vertex3D {
		float x, y, z;
	};
	struct Point2D {
		float x, y;
	};

	struct ModeStructure {
		vector<Vertex3D> Vertex;
		vector<Point2D> Point;

		float u, v;
	};

	class Mode {
	    public:
			ModeStructure m;

			int VertexAmount;
			float Fov;

			void Map(vector<Vertex3D>& M) { //投影映射计算坐标
				float m11, m22, m32, m33;

				m11 = 1 / tan((Fov * MPI) / 2);
				m22 = m11 / AspectRadio;

				m32 = -((2 * NearPlace * FarPlace) / (FarPlace - NearPlace));
				m33 = -(1 / (NearPlace - FarPlace)) * (NearPlace - FarPlace);

				for (int i = 0; i < VertexAmount; i++) {
					M[i].x = m11 * m.Vertex[i].x;
					M[i].y = m22 * m.Vertex[i].y;
			        M[i].z = m33 * m.Vertex[i].z + m32;
				}
			}
	};


	void zoom(const Vertex3D v,float size,float& x,float& y,float& z) { //放大与缩小模型

		x = static_cast<float>(v.x * size);
		y = static_cast<float>(v.y * size);
		z = static_cast<float>(v.z * size);
	}

	
	
	void Radian(float input, float& out) { //将角度转化为弧度
		out = input * MPI;
	}

	float radian(float input) { 
		return input * MPI;
	}


	void rotateX(ModeStructuer& v, float angle) { //模型绕X轴旋转
		float rad = angle * (M_PI / 180.0f);
		float cosA = cos(rad);
		float sinA = sin(rad);
		float newY = v.y * cosA - v.z * sinA;
		float newZ = v.y * sinA + v.z * cosA;
		v.y = newY;
		v.z = newZ;
	}

	void rotateY(Vertex3D& v,float angle) {
		float ratate = angle * MPI;
		float CosA = cos(ratate);
		float SinA = sin(ratate);

		v.x = v.x * CosA + v.z * SinA;
		v.z = -v.x * SinA + v.z * CosA;
	}

	void rotateZ(ModeStructuer& v, float angle) {
		float rad = angle * (M_PI / 180.0f);
		float cosA = cos(rad);
		float sinA = sin(rad);
		float newX = v.x * cosA - v.y * sinA;
		float newY = v.x * sinA + v.y * cosA;
		v.x = newX;
		v.y = newY;
	}

}




namespace window {
	void Cursor(bool i) {//设置光标闪烁
		HANDLE hs = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO ci;
		GetConsoleCursorInfo(hs, &ci);

		ci.bVisible = i;

		SetConsoleCursorInfo(hs, &ci);
	}


	class Paint {//画笔
	    public:
			HDC hdc;
			int size;
			int r{ 0 }, g{ 0 }, b{ 0 };
			int frequency;//顶点次数

			vector<e3d::Vertex3D> vertex;

			const HPEN pen = CreatePen(PS_SOLID, size, RGB(r, g, b));
			const HPEN hpen = (HPEN)SelectObject(hdc, pen);

			void Painting(float x = 0,float y = 0) {//绘制坐标并使其在特定位子绘制

				for (int i = 0; i < frequency; ++i) for (int o = i; o < frequency; ++o) {
					MoveToEx(hdc, vertex[i].x + x, vertex[i].y + y, NULL);
					LineTo(hdc, vertex[o].x + x, vertex[o].y + y);
				}
			}

			void Pixel(float x,float y) {
				SetPixel(hdc, x, y, RGB(r, g, b));
			}

	};
}

#endif