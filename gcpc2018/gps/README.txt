Problem: GPS
Difficulty: 85%


Idea:  3D geometry

Problem: We are on the surface of the earth (a sphere of size 63XYkm) and do a GPS measurement.
		 We have a description of all X (~30) satellites.
			- we assume that the orbit of each satellite is a circle centred at the centre of the earth
			- the orbit is described by two angles (e.g. intersection angle with the equator and geographic length of that intersection), the orbit radius, the satellites speed, and the initial phase angle at time 0

		 We measure the time of n \geq 3 satellites and our current local time.

Input: aktuelle Position auf der Erdoberfläche, Orbits und aktuelle Positionen der Satelliten, Messdaten der Satelliten mit Timestamp und ID
Output: für jeden Satelliten die Abweichung zwischen der Uhr an Bord des Satelliten und der Uhrzeit an der Messstation auf der Erde

Solution:
		From the difference between local time and the time of the satellite signal, we can compute its distance.
		From each satellites time, we can compute its position on its orbit.

		Our position is then the intersection of all spheres induced by the satellite positions and distances.
		(3 Satellites is sufficient if we know that we are on the surface of the earch)

To make this problem more nasty: introduce imprecisions
