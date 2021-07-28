import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Poduri {

	public static final String INPUT_FILE = "poduri.in";
	public static final String OUTPUT_FILE = "poduri.out";

	// distanta maxima in graf
	public static final int INF = (int)1e9; // 10^9 = 1.000.000.000

	public static int n, m; //linii, coloane
	public static int x, y; //coordonate Gigel

	ArrayList<Integer> iesiri = new ArrayList<Integer>();

	// nodul sursa in parcurgerea BFS
	int source;

	public void solve() {
		writeOutput(bfs(readInput()));
	}

	public ArrayList<Integer>[] readInput() {
		try {
			Scanner sc = new Scanner(new BufferedReader(new FileReader(
							INPUT_FILE)));
			n = sc.nextInt();
			m = sc.nextInt();
			x = sc.nextInt();
			y = sc.nextInt();
			source = (x - 1) * m + y;
			sc.nextLine();

			@SuppressWarnings("unchecked")
			ArrayList<Integer>[] adj = new ArrayList[m * n + 1];

			ArrayList<String> line = new ArrayList<String>();
			char iesire = '0';

			line.add(new String(new char[m + 2]).replace('\0', iesire));
			for (int i = 1; i <= n; i++) {
				line.add(iesire + sc.nextLine() + iesire);                   
			}
			line.add(new String(new char[m + 2]).replace('\0', iesire));

			for (int node = 0; node <= n * m; node++) {
				adj[node] = new ArrayList<Integer>();
			}

			//construire lista adiacenta
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					adj[(i - 1) * m + j].add((i - 1) * m + j);
					if (line.get(i).charAt(j) == 'V') {
						//pod vertical, are posibili vecini sus/jos din matrice
						if (line.get(i - 1).charAt(j) != iesire
							&& line.get(i - 1).charAt(j) != '.') {
							adj[(i - 1) * m + j].add((i - 2) * m + j); // sus
						}
						if (line.get(i + 1).charAt(j) != iesire
							&& line.get(i + 1).charAt(j) != '.') {
							adj[(i - 1) * m + j].add((i) * m + j); // jos
						}
						if (line.get(i + 1).charAt(j) == iesire
							|| line.get(i - 1).charAt(j) == iesire) {
							iesiri.add((i - 1) * m + j);
						}
					}
					if (line.get(i).charAt(j) == 'O') {
						//pod orizontal, are posibili vecini stanga.dreapta din matrice
						if (line.get(i).charAt(j - 1) != iesire
							&& line.get(i).charAt(j - 1) != '.') {
							adj[(i - 1) * m + j].add((i - 1) * m + j - 1); // stanga
						}
						if (line.get(i).charAt(j + 1) != iesire
							&& line.get(i).charAt(j + 1) != '.') {
							adj[(i - 1) * m + j].add((i - 1) * m + j + 1); // dreapta
						}
						if (line.get(i).charAt(j + 1) == iesire
							|| line.get(i).charAt(j - 1) == iesire) {
							iesiri.add((i - 1) * m + j);
						}
					}
					if (line.get(i).charAt(j) == 'D') {
						//pod dublu, are posibili vecini sus/jos/stanga/dreapta din matrice
						if (line.get(i - 1).charAt(j) != iesire
							&& line.get(i - 1).charAt(j) != '.') {
							adj[(i - 1) * m + j].add((i - 2) * m + j); // sus
						}
						if (line.get(i + 1).charAt(j) != iesire
							&& line.get(i + 1).charAt(j) != '.') {
							adj[(i - 1) * m + j].add((i) * m + j); // jos
						}
						if (line.get(i).charAt(j - 1) != iesire
							&& line.get(i).charAt(j - 1) != '.') {
							adj[(i - 1) * m + j].add((i - 1) * m + j - 1); // stanga
						}
						if (line.get(i).charAt(j + 1) != iesire
							&& line.get(i).charAt(j + 1) != '.') {
							adj[(i - 1) * m + j].add((i - 1) * m + j + 1); // dreapta
						}

						if (line.get(i + 1).charAt(j) == iesire
							|| line.get(i - 1).charAt(j) == iesire
							|| line.get(i).charAt(j + 1) == iesire
							|| line.get(i).charAt(j - 1) == iesire) {
							iesiri.add((i - 1) * m + j);
						}
					}
				}
			}
			sc.close();
			
			return adj;
		} catch (IOException e) {
			throw new RuntimeException(e);
		}

	}

	private void writeOutput(int n) {
		try {
			PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
							OUTPUT_FILE)));
			pw.printf("" + n);
			pw.close();
		} catch (IOException e) {
			throw new RuntimeException(e);    
		}
	}

	private int bfs(ArrayList<Integer> [] adj) {
		int[] d = new int[n * m + 1];
		Arrays.fill(d, INF);

		Queue<Integer> q = new LinkedList<>();
		q.add(source);
		d[source] = 0;;

		while (!q.isEmpty()) {
			int node = q.poll();

			for (Integer neigh : adj[node]) {
				if (d[neigh] == INF) {
					d[neigh] = d[node] + 1;
					q.add(neigh);
				}
			}
		}

		int min = INF;

		for (int iesire : iesiri) {
			if (d[iesire] > 0 && d[iesire] < min) {
				min = d[iesire];
			}
		}

		min = min + 1;
		return min;
	}

	public static void main(String[] args) {
		new Poduri().solve();
	}
}