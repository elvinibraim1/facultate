import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

class Persoana implements Comparable<Object> {
	String name;
	int n; //numarul de mail-uri
	ArrayList<String> mails = new ArrayList<String>();

	public Persoana(String name, int n, ArrayList<String> mails) {
		this.name = name;
		this.n = n;
		this.mails = mails;
	}

	public void modifyName(String name) {
		if (this.name.compareTo(name) > 0) {
			this.name = name;
		}
	}

	public void addMails(ArrayList<String> mails) {
		for (String mail : mails) {
			if (!this.mails.contains(mail)) {
				this.mails.add(mail);
				this.n = this.n + 1;
			}
		}
	}

	public int containsMail(String mail) {
		for (String m : this.mails) {
			if (m.compareTo(mail) == 0) {
				return 1; // exista
			}
		}

		return 0; // nu exista
	}

	public void mailSort() {
		Collections.sort(this.mails);
	}

	public int compareTo(Object o) {
		if (o == null) {
			return 0;
		}

		Persoana p = (Persoana) o;

		if (p.n == n) {
			return name.compareTo(p.name);
		}

		return n - p.n;
		
	}

}

public class Adrese {

	public static final String INPUT_FILE = "adrese.in";
	public static final String OUTPUT_FILE = "adrese.out";

	int n; // persoane de analizat
	int m; // persoane final
	ArrayList<Persoana> persoane = new ArrayList<Persoana>();

	public void solve() {
		readInput();
		writeOutput();
	}

	public void readInput() {
		try {
			Scanner sc = new Scanner(new BufferedReader(new FileReader(
							INPUT_FILE)));

			n = sc.nextInt();
			sc.nextLine();

			for (int i = 1; i <= n; i++) {
				String[] line = sc.nextLine().split(" "); // citire linie, apoi parsare in
				String name = line[0]; // nume
				int noMails = Integer.parseInt(line[1]); // si numar mail-uri
				int duplicate = 0; // verifica daca persoana curenta exista deja

				ArrayList<String> mails = new ArrayList<String>();

				for (int j = 1;  j <= noMails; j ++) {
					String mail = sc.nextLine();
					mails.add(mail);
				}

				for (String mail : mails) {
					for (Persoana pers : persoane) {
						if (pers.containsMail(mail) == 1) {
							duplicate = 1;
							pers.modifyName(name);
							pers.addMails(mails);
							break;
						}
					}
				}

				if (duplicate == 0) {
					persoane.add(new Persoana(name, noMails, mails));
				}

				for (Persoana pers : persoane) {
					pers.mailSort();
				}
			}

			sc.close();
			
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

	}

	private void writeOutput() {
		try {
			PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
							OUTPUT_FILE)));

			pw.printf(persoane.size() + "\n");

			Collections.sort(persoane);

			for (Persoana pers : persoane) {
				pw.printf(pers.name + " " + pers.mails.size() + "\n");
				for (String s : pers.mails) {
					pw.printf(s + "\n");
				}
			}

			pw.close();
		} catch (IOException e) {
			throw new RuntimeException(e);    
		}
	}

	public static void main(String[] args) {
		new Adrese().solve();
	}
}