#pragma once 
/*
Cell SearchWay(Cell click_pos, Cell unit_pos)
{
	int matrix[32][32][3];
	int step;
	bool added = true, result = true;
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if (map[i][j] != 0) matrix[i][j][0] = -2;
			else matrix[i][j][0] = -1;
		}
	}
	matrix[click_pos.getY()][click_pos.getX()][0] = 0;

	step = 0;
	while (added && matrix[unit_pos.getY()][unit_pos.getX()][0] == -1) {
		added = false;
		step++;
		for (int i = 0; i < 32; i++) {
			for (int j = 0; j < 32; j++) {
				if (matrix[i][j][0] == step - 1) {
					int _i, _j;
					_i = i + 1; _j = j;
					if (_i >= 0 && _j >= 0 && _i < 32 && _j < 32) {
						if (matrix[_i][_j][0] == -1 && matrix[_i][_j][0] != -2) {
							matrix[_i][_j][0] = step;
							matrix[_i][_j][1] = i;
							matrix[_i][_j][2] = j;
							added = true;
						}
					}
					_i = i - 1; _j = j;
					if (_i >= 0 && _j >= 0 && _i < 32 && _j < 32) {
						if (matrix[_i][_j][0] == -1 && matrix[_i][_j][0] != -2) {
							matrix[_i][_j][0] = step;
							matrix[_i][_j][1] = i;
							matrix[_i][_j][2] = j;
							added = true;
						}
					}
					_i = i; _j = j + 1;
					if (_i >= 0 && _j >= 0 && _i < 32 && _j < 32) {
						if (matrix[_i][_j][0] == -1 && matrix[_i][_j][0] != -2) {
							matrix[_i][_j][0] = step;
							matrix[_i][_j][1] = i;
							matrix[_i][_j][2] = j;
							added = true;
						}
					}
					_i = i; _j = j - 1;
					if (_i >= 0 && _j >= 0 && _i < 32 && _j < 32) {
						if (matrix[_i][_j][0] == -1 && matrix[_i][_j][0] != -2) {
							matrix[_i][_j][0] = step;
							matrix[_i][_j][1] = i;
							matrix[_i][_j][2] = j;
							added = true;
						}
					}
				}
			}
		}
	}
	if (matrix[unit_pos.getY()][unit_pos.getX()][0] == -1) {
		result = false;
	}
	if (result) {
		int _i = unit_pos.getY(), _j = unit_pos.getX();
		int count = 0;
		while (matrix[_i][_j][0] != 0) {
			if (count != 0) return Cell(Cell(_i, _j)); // вернуть позицию €чейки
			int li = matrix[_i][_j][1];
			int lj = matrix[_i][_j][2];
			_i = li; _j = lj;
			count++;
		}
	}
	return Step(BoardPoint());
}
*/