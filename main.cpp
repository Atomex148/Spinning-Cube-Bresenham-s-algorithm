#include "headers.hpp"

struct POINT {
	float x = 0.0f, y = 0.0f, z = 0.0f;
	POINT() : x(0), y(0), z(0) {}
	POINT(float x, float y, float z) : x(x), y(y), z(z) {}

	void rotateByX(float angle) {
		float newY = y * cos(angle) - z * sin(angle);
		float newZ = y * sin(angle) + z * cos(angle);
		y = newY;
		z = newZ;
	}

	void rotateByY(float angle) {
		float newX = x * cos(angle) + z * sin(angle);
		float newZ = z * cos(angle) - x * sin(angle);
		x = newX;
		z = newZ;
	}

	void rotateByZ(float angle) {
		float newX = x * cos(angle) - y * sin(angle);
		float newY = x * sin(angle) + y * cos(angle);
		x = newX;
		y = newY;
	}

	void rotate(float by_X, float by_Y, float by_Z) {
		rotateByX(by_X);
		rotateByY(by_Y);
		rotateByZ(by_Z);
	}

	POINT operator+(int other) const {
		return POINT(this->x + other, this->y + other, this->z + other);
	}
};

void drawCube(const POINT points[8]) {
	const int screen_size = 40;
	std::vector<std::vector<char>> screen(screen_size, std::vector<char>(screen_size, ' '));

	POINT onScreen[8];
	for (int i = 0; i < 8; i++) {
		onScreen[i] = POINT(points[i].x + screen_size / 2, points[i].y + screen_size / 2, points[i].z);
	}

	std::array<std::pair<int, int>, 12> lines = {{
	{0, 1}, {0, 2}, {0, 4}, {1, 3}, {1, 5}, {7, 5},
	{7, 3}, {7, 6}, {2, 6}, {4, 6}, {4, 5}, {2, 3}
	}};

	for (auto& line : lines) {
		int x1 = onScreen[line.first].x, x2 = onScreen[line.second].x;
		int y1 = onScreen[line.first].y, y2 = onScreen[line.second].y;
		int difference_x = std::abs(x1 - x2);
		int difference_y = std::abs(y1 - y2);
		int direction_x = x1 < x2 ? 1 : -1;
		int direction_y = y1 < y2 ? 1 : -1;
		int error = difference_x - difference_y;
		int error_2;

		while (true) {
			if (x1 >= 0 && x1 < screen_size && y1 >= 0 && y1 < screen_size) screen[y1][x1] = '&';
			if (x1 == x2 && y1 == y2) break;
			error_2 = 2 * error;
			if (error_2 >= -difference_y) { error -= difference_y; x1 += direction_x; }
			if (error_2 <= difference_x) { error += difference_x; y1 += direction_y; }
		}
	}

	for (auto& str : screen) {
		for (auto& c : str) {
			std::cout << c;
		}
		std::cout << '\n';
	}
}

int main(int argc, char* argv[]) {
	POINT points[8] = { 
		{ -10, -10, -10 }, { -10, 10, -10 }, { 10, -10, -10 }, { 10, 10, -10 },
		{ -10, -10, 10 }, {-10, 10, 10}, { 10, -10, 10 }, { 10, 10, 10 } 
	};

	float alpha = 0.15f, beta = 0.1f, delta = 0.1f;

	while (true) {
		drawCube(points);
		for (int i = 0; i < 8; i++) {
			points[i].rotate(alpha, beta, delta);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		system("cls");
	}
	return 0;
}