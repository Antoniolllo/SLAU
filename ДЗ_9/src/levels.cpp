#include "matrix.h"

#include <algorithm>

std::vector<std::vector<int>> level_matrix(
    const SparseMatrix& A
) {
    int n = A.n;
    int inf = 1000000000;

    std::vector<std::vector<int>> level(n, std::vector<int>(n, inf));

    for (int i = 0; i < n; i++) {
        level[i][i] = 0;

        for (int j = A.rows[i]; j < A.rows[i + 1]; j++) {
            int col = A.columns[j];

            if (col <= i) {
                level[i][col] = 0;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = k + 1; i < n; i++) {
            if (level[i][k] == inf) {
                continue;
            }

            for (int j = k + 1; j <= i; j++) {
                if (level[j][k] == inf) {
                    continue;
                }

                int new_level = level[i][k] + level[j][k] + 1;

                if (new_level < level[i][j]) {
                    level[i][j] = new_level;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (level[i][j] == inf) {
                level[i][j] = -1;
            }
        }
    }

    return level;
}
