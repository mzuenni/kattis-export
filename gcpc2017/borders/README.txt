Themen: Geometrie, konstruktives Problem

Geschätzte Schwierigkeit: 50 (Prozent der Teams lösen sie nicht)

Lösung:
Ein Bild sagt mehr als 1000 Worte, daher sei auf die Bilder in data/secret verwiesen.

Es gibt immer eine Lösung. Sortiere alle Punkte lexikographisch, dann führe beide
Linien im Zickzack parallel zueinander an allen Punkten der Reihenfolge nach vorbei.
Dabei verschiebt man je nach Farbe ein Stück nach links/rechts, sodass die Punkte auf
der richtigen Seite der Linien liegen. Am Ende führt man die Linien zurück zum
Ausgangspunkt.

Komplexität: O(n * log n)
