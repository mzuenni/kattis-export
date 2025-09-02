Themen: Zeichenketten, Travelling Salesman, DP

Geschätzte Schwierigkeit: 90 (Prozent der Teams lösen sie nicht)

Lösung:
Das Problem kann mit dynamischer Programmierung gelöst werden:

	Sei S eine Teilmenge der Strings und s in S.
	dp[S][s] = die lexikographisch minimale Position (Zeile,Spalte) an der ein
	           Text enden kann der alle Strings in S enthält und Suffix s hat

Die Berechnung ist dann ähnlich wie beim DP zum Travelling-Salesman-Problem (TSP).
Im Spezialfall eines Grids der Höhe 1 (also keine Zeilenumbrüche) erhält man sogar
genau TSP, wobei die Distanzen gegeben sind durch:

	d(s,t) = minimale Anzahl an Buchstaben, die man an s anhängen muss um einen
	         String mit Suffix t zu erhalten, z.B. d("ABC","CDE") = 2, d("ABC","DEF") = 3

Diese Distanzen kann man vorberechnen und im DP verwenden.

Bei der Implementierung zu beachten:
- einige Strings können Infixe von anderen sein;
- Zeilenumbrüche müssen im DP korrekt behandelt werden;
- das DP muss Rekonstruktion einer Lösung ermöglichen.

Komplexität: O(n^2 * 2^n)
