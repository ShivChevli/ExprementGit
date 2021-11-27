
/* 
    program for Multiplication of two Matix of equal size and shap.
*/
import java.util.*;

public class MatrixMultiplication {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        int a[][] = new int[3][3];
        int b[][] = new int[3][3];
        int c[][] = new int[3][3];
        int i, j, k, sum = 0;

        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                System.out.print("Enter value of metrice a[" + i + "][" + j + "] : ");
                a[i][j] = kb.nextInt();
            }
            System.out.println("");
        }

        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                System.out.print("Enter value of metrice b[" + i + "][" + j + "] : ");
                b[i][j] = kb.nextInt();
            }
            System.out.println("");
        }

        System.out.println("A :-        B :-");
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                System.out.print(a[i][j] + "  ");
                // b[i][j]=kb.nextInt();
            }

            for (j = 0; j < 3; j++) {
                System.out.print("  " + b[i][j]);
            }
            System.out.println("");
        }

        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                sum = 0;
                for (k = 0; k < 3; k++) {
                    sum = sum + a[i][k] * b[k][j];
                }
                c[i][j] = sum;
            }
        }

        System.out.println("c:-");
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                System.out.print(c[i][j] + "  ");
            }
            System.out.println("");
        }
    }
}