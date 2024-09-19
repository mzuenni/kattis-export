// Usage: cat ../data/sample/2.{in,ans} | asy -nosafe ./sample.asy

import fontsize;
import patterns;
import settings;
outformat="pdf";

add("hatch", hatch(0.75mm));
defaultpen(0.25);
bbox(white, Fill);

pen[] colours = {
  red,
  lightblue,
  fuchsia,
  orange,
  green,
  purple,
  lightgrey,
};

int n = stdin;
int s1 = stdin;
int s2 = stdin;

int w = 16;
int h = 16;

for (int x = 0; x <= w+10; x += w+10) {
  int z = (x == 0 ? s1 : s2);

  for (int y = 0; y < z*h; y += h) {
    int id = stdin;
    path box = (x, y) -- (x+w, y) -- (x+w, y+h) -- (x, y+h) -- cycle;
    pen self = (id == 0 ? orange : rgb(173, 135, 98)); // colours[id % colours.length];
    filldraw(box, self, grey);

    for (int q = 5; q < w*2; q += 5) {
      path dent = (-0.5, 2.0) -- (0.5, 2.0) -- (0.5, h-2.0) -- (-0.5, h-2.0) -- cycle;
      fill(shift(x + q / 2.0 - 0.5, y) * scale(1.0, 1.0) * dent, self * 0.8 + black * 0.2);
      fill(shift(x + q / 2.0 + 0.5, y) * scale(0.5, 1.0) * dent, self * 0.9 + white * 0.1);
    }
    if (id == 0) {
      // Arrow to container 0
      /*
      draw(
        (x-20, y+h/2.0+2) -- (x-10, y+h/2.0+2) -- (x-10, y+h/2.0+4) -- (x-3, y+h/2.0) --
        (x-10, y+h/2.0-4) -- (x-10, y+h/2.0-2) -- (x-20, y+h/2.0-2) -- cycle, black);
      */
    } else {
      filldraw((x+1, y+h-11) -- (x+11, y+h-11) -- (x+11, y+h-1) -- (x+1, y+h-1) -- cycle, (id == 0 ? black : white), grey);
      label((string) id, (x+5.5, y+h-5.5), NoAlign, (id == 0 ? black : black) + fontsize(10pt));
    }
  }
}

// Gantry beam
filldraw(
  (199, 87) --
  (199, 85) --
  (-39, 85) --
  (-39, 87) --
  cycle,
  lightgrey,
  grey
);

// Dolly
filldraw(
  (12, 86) -- (28, 86) -- (28, 84) --
  (26, 82) -- (14, 82) --
  (12, 84) --cycle,
  /*blue*/ lightgrey, black);

// Ropes
for (int i = 0; i < 4; ++i) {
  real x = 20 + (i - 1.5);
  draw((x, 82) -- (x, 74), black);
}

// Hook pulley
filldraw(
  circle((20, 75), 1.5),
  black,
  black);

// Hook body
filldraw(
  (19, 76) --
  (18, 73) --
  (19, 72) --
  (21, 72) --
  (22, 73) --
  (21, 76) -- cycle,
  /*yellow*/ lightgrey,
  black);

// Hook crane
fill(circle((20, 69), 3), black);
fill(circle((20, 68), 2.7), white);

// Wheels
filldraw(circle((14, 86), 1.8), /*blue*/ lightgrey, black);// draw(circle((14, 86), 0.75), black);
filldraw(circle((18, 86), 1.8), /*blue*/ lightgrey, black);// draw(circle((18, 86), 0.75), black);
filldraw(circle((22, 86), 1.8), /*blue*/ lightgrey, black);// draw(circle((22, 86), 0.75), black);
filldraw(circle((26, 86), 1.8), /*blue*/ lightgrey, black);// draw(circle((26, 86), 0.75), black);

shipout();
