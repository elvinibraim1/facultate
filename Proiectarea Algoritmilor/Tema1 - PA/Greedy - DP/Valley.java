import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Collections;
import java.util.Scanner;
import java.util.Vector;

public class Valley {

	public static int n;
	public static Vector<Long> v = new Vector<Long>();

	public void readValley() {
		try {
			Scanner sc3 = new Scanner(new File("valley.in"));
			n = sc3.nextInt();
	
			for (int i = 0; i < n; i ++) {
				v.add(sc3.nextLong());
			}

			sc3.close();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}
	
	public void writeValley(long timeS) {
		try {
			PrintWriter pw3 = new PrintWriter(new File("valley.out"));
			pw3.printf("%d\n", timeS);
			pw3.close();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}		
	}
	
	public long timeSpent(Vector<Long> v) {
		int size = v.size();
		long timeS = 0; // timpul de returnat
		
		long x = Collections.min(v); // valoarea minimului
		long first = v.firstElement(); // valoarea primului element
		long last = v.lastElement(); // valoare ultimului element
		
		if (x == last) {
			if (v.get(size - 2) > last) {
				timeS = timeS + v.get(size - 2) - last;
				v.set(size - 2, last);
			}
				
			for (int i = 1; i < size - 2; i++) { //for pentru creearea prefixului
				if (first < v.get(i)) {
					timeS = timeS + v.get(i) - first;
				} else {
					first = v.get(i);
				}
			}
			
			return timeS; // returnare rezultat pentru cazul special
		}
		
		if (x == first) {
			if (v.get(1) > first) {
				timeS = timeS + v.get(1) - first;
				v.set(1, first);
			}
				
			for (int i = size - 2; i < 2; i--) { //for pentru creearea sufixului
				if (last < v.get(i)) {
					timeS = timeS + v.get(i) - last;
				} else {
					last = v.get(i);
				}
			}
			
			return timeS; // returnare rezultat pentru cazul special
		}
		
		int index = 1;	
		for (index = 1; index <= size - 2; index++) { // cautare index al primului minim
			if (v.get(index) == x) {
				break;
			}
		}		
		
		for (int i = 1; i <= index; i++) { // creare prefix de la inceput pana la minim
			if (first > v.get(i)) {
				first = v.get(i);
			} else {
				timeS = timeS + v.get(i) - first;
			}		
		}
		
		for (int i = size - 2; i >= index; i--) { //creare sufix de la sfarsit pana la minim
			if (last > v.get(i)) {
				last = v.get(i);
			} else {
				timeS = timeS + v.get(i) - last;
			}
		}	
		
		return timeS;
	}

	public void solve3() {
		new Valley().readValley();
		new Valley().writeValley(timeSpent(v));	
	}	

	public static void main(String[] args) {
		new Valley().solve3();
	}
}