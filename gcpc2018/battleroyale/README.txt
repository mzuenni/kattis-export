Battle Royale
Geometrie, Kreis, Tangente, Kreisbogen, Kürzester Weg

Problem:
Im Problem 'Battle Royale' geht es darum die Länge des kürzesten Weges zwischen zwei Punkten in einer 2D-Ebene
zu finden. Der Weg ist durch einen blauen und einen roten Kreis beschränkt.
Der blaue Kreis darf nicht verlassen und der rote darf nicht betreten werden.
Roter Kreis sowie Start- und Zielpunkt sind komplett innerhalb des blauen Kreises.
Die Kreise dürfen berührt werden. Der direkte Weg ist immer durch den roten Kreis blockiert.

Lösungsidee:
	Berechne vier Tangenten zum roten Kreis. Zwei durch den Startpunkt und zwei durch den Endpunkt.
	Die Tangentenpunkte am Kreis können über den Kreisbogen verbunden werden, was in Summe zu vier
	möglichen Pfaden führt. Die Länge der vier Kreisbögen lässt sich über den Kreiswinkel der Punkte
	bestimmen. Der blaue Kreis ist irrelevant.

Laufzeit und Inputconstraints:
	Irrelevant.
	
Varianten:
* Der direkte Weg ist nicht immer durch den roten Weg blockiert. 
	Dann ist ein zusätzlicher Kreis-Liniensegment-Schnitttest nötig.
	Dieser Test sollte Teams die den Rest der Aufgabe lösen nicht vor größere Probleme stellen,
	verlängert die Aufgabe allerdings.
* Der rote Kreis darf den blauen Kreis schneiden. Dann ist nicht garantiert das die Tangentenpunkte innerhalb
	des blauen Kreises liegen, diese können dann einfach nicht betrachtet werden. Der deutlich schwieriger Fall
	ist das alle Tangentenpunkte im blauen Kreis sind aber die Verbindungen trotzdem außerhalb des blauen Kreises
	verlaufen. Diese Variante erfordert einen Kreis-Kreis-Schnitttest sowie eine Parametersierung der Schnittpunkte
	über den Kreiswinkel.
	
Schwierigkeit:
	Basisvariante ungelöst von 95%
	
Martin Tillmann
martin.tillmann@kit.edu