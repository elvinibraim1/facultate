import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Stocks {

	public static int n, b, l;
	public static int[] current;
	public static int[] minim;
	public static int[] maxim;
	
	public void readStocks() {
		try {
			Scanner sc2 = new Scanner(new File("stocks.in"));
			n = sc2.nextInt();
			b = sc2.nextInt();
			l = sc2.nextInt();
			
			current = new int[n + 1]; // adaugare element fictiv pentru indexare de la 1
			minim = new int[n + 1];
			maxim = new int[n + 1];
	
			for (int i = 1; i <= n; i ++) {
				current[i] = sc2.nextInt();
				minim[i] = sc2.nextInt();
				maxim[i] = sc2.nextInt();
			}

			sc2.close();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}
	
	public void writeStocks(int profit) {
		try {
			PrintWriter pw2 = new PrintWriter(new File("stocks.out"));
			pw2.printf("%d\n", profit);
			pw2.close();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}		
	}
	
	public void solve2() {
		new Stocks().readStocks();
		
		int [][][] dp = new int [n + 1][b + 1][l + 1];
		
		for (int bug = 0; bug <= b; bug++) { // caz de baza
			for (int los = 0; los <= l; los++) {
				dp[0][bug][los] = 0;
			}
		}
		
		for (int i = 1; i <= n; i++) { // caz general | parcurgere vector tridimensional
			for (int bug = 0; bug <= b; bug++) {
				for (int los = 0; los <= l; los++) {
					dp[i][bug][los] = dp[i - 1][bug][los];
					// se salveaza solutia de la pastul anterior
					//la final se alege maximul dintre sol_aux si solutia anterioara
					
					if (bug - current[i] >= 0) { 
						if (los - (current[i] - minim[i]) >= 0) {
							int sol_aux = dp[i - 1][bug - current[i]][los - (current[i] - minim[i])]
									+ maxim[i] - current[i];
							dp[i][bug][los] = Math.max(dp[i][bug][los], sol_aux);
						}
					}
				}
			}
		}
		
		new Stocks().writeStocks(dp[n][b][l]); // se scrie in fisier profitul maxim
	}
	
	public static void main(String[] args) {
		new Stocks().solve2();
	}

}
