import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Collections;
import java.util.Scanner;
import java.util.Vector;

class Pair implements Comparable<Object> {
	int i; // puterea de minare
	int j; // pretul de upgrade
	
	public Pair(int i, int j) {
		this.i = i;
		this.j = j;
	}
	
	public int compareTo(Object o) {
		if (o == null) {
			return 0;
		}
		
		Pair p = (Pair) o;

		if (p.i == i) {
			if (p.j == j) {
				return 0;
			}
			if (p.j > j) {
				return -1;
			} else {
				return 1;
			}
		}
		
		if (p.i > i) {
			return -1;
		} else {
			return 1;
		}
	}
}

public class Crypto {
	
	public final String Input = "crypto.in";
	public final String Output = "crypto.out";

	public static int n; //Numar calculatoare
	public static int B; //Bani
	
	public static Vector<Pair> PiUi = new Vector<Pair>();
	
	static int crypto = 0;

	public void readInput() {
		try {
			Scanner sc1 = new Scanner(new File(Input));
			n = sc1.nextInt();
			B = sc1.nextInt();
			
			for (int i = 0; i < n; i ++) {
				PiUi.add(new Pair(sc1.nextInt(), sc1.nextInt()));	
			}
			
			PiUi.add(new Pair(999999999, 0));
			
			Collections.sort(PiUi);

		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}
	
	public void writeOutput() {
		try {
			PrintWriter pw1 = new PrintWriter(new File(Output));
			pw1.printf("%d\n", crypto);
			pw1.close();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}		
	}

	public void solve() {
		new Crypto().readInput();
		int index = 0;
		
		while (B > 0) {	// cat timp mai avem bani	
			B = B - PiUi.get(index).j;
			if (B < 0) { // daca dupa ce am upgrada am ramane fara bani se termina programul
				break;
			}
			
			PiUi.get(index).i ++; // se face upgrade-ul
			
			if (PiUi.get(index).i <= PiUi.get(index + 1).i) {
				index = 0; // o ia de la 0 pana cand o sa fie aceeasi putere de minare
			} else {
				index ++; // se trece la indicele urmator, incercand sa ajunga la aceeasi putere
			}
			
			if (index > PiUi.size()) {
				index = 0;
			} // daca se ajunge la ultimul calculator, se ia indexul din nou 0;
		}
		
		Collections.sort(PiUi);
		crypto = PiUi.get(0).i;
		new Crypto().writeOutput();
	}	

	public static void main(String[] args) {
		new Crypto().solve();
	}
}
