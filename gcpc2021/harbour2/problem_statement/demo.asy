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
  ( 81, 127) --
  ( 81, 125) --
  (-39, 125) --
  (-39, 127) --
  cycle,
  lightgrey,
  grey
);

// Dolly
filldraw(
  (12, 126) -- (28, 126) -- (28, 124) --
  (26, 122) -- (14, 122) --
  (12, 124) --cycle,
  /*blue*/ lightgrey, black);

// Ropes
for (int i = 0; i < 4; ++i) {
  real x = 20 + (i - 1.5);
  draw((x, 122) -- (x, 114), black);
}

// Hook pulley
filldraw(
  circle((20, 115), 1.5),
  black,
  black);

// Hook body
filldraw(
  (19, 116) --
  (18, 113) --
  (19, 112) --
  (21, 112) --
  (22, 113) --
  (21, 116) -- cycle,
  /*yellow*/ lightgrey,
  black);

// Hook crane
fill(circle((20, 109), 3), black);
fill(circle((20, 108), 2.7), white);


{
    int id = stdin;
	int x = 12;
	int y = 92;
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




// Wheels
filldraw(circle((14, 126), 1.8), /*blue*/ lightgrey, black);// draw(circle((14, 126), 0.75), black);
filldraw(circle((18, 126), 1.8), /*blue*/ lightgrey, black);// draw(circle((18, 126), 0.75), black);
filldraw(circle((22, 126), 1.8), /*blue*/ lightgrey, black);// draw(circle((22, 126), 0.75), black);
filldraw(circle((26, 126), 1.8), /*blue*/ lightgrey, black);// draw(circle((26, 126), 0.75), black);


shipout();
