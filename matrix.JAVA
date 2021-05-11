package matrix;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class matrix {

    private final static int N = 3;
    private final static int M = 3;
    private final static int K = 2;
    private final static int[][] MAT_A = { { 1, 4 }, { 2, 5 }, { 3, 6 } };
    private final static int[][] MAT_B = { { 8, 7, 6 }, { 5, 4, 3 } };
    private final static int THREAD_COUNT = 9;

    public static void main(String[] args) {
        ExecutorService threadPool = Executors.newFixedThreadPool(THREAD_COUNT);
        int[][] matResult = new int[M][N];

        for (int row = 0; row < M; row++)
            for (int column = 0; column < N; column++) {
                final int[] pos = new int[] { row, column };
                threadPool.submit(new Runnable() {
                    public void run() {
                        for (int i = 0; i < K; i++)
                            matResult[pos[0]][pos[1]] += MAT_A[pos[0]][i] * MAT_B[i][pos[1]];
                    }
                });
            }

        for (int row = 0; row < M; row++) {
            for (int column = 0; column < N; column++)
                System.out.printf("%d ", matResult[row][column]);
            System.out.println();
        }

        threadPool.shutdown();
    }
}
