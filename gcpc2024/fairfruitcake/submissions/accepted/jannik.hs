-- shamlessly translated from submissions/accepted/mzuenni.cpp because it's shorter than my solution

import qualified Data.ByteString.Char8 as B
import Data.List

data Pt
 = Pt !Int !Int

instance Num Pt where
 Pt x1 y1 + Pt x2 y2 = Pt (x1+x2) (y1+y2)
 negate (Pt x y) = Pt (-x) (-y)

Pt x1 y1 × Pt x2 y2 = x1 * y2 - y1 * x2
(Pt x y) % d = Pt (div x d) (div y d)

ccw p0 p1 p2 = signum $ (p1 - p0) × (p2 - p0)

main = B.getContents >>= putStrLn . solve . map ((\(Just(x,_)) -> x) . B.readInt) . B.words

toPoly :: [Int] -> [Pt]
toPoly (x:y:cs) = Pt (2*x) (2*y) : toPoly cs
toPoly [] = []

comp c (lp,la,ld) (rp,ra,rd)
 | ccw c lp rp /= 0 = compare 0 (ccw c lp rp)
 | la /= ra = compare la ra
 | otherwise = compare rd ld

solve (n:inp) = maybe "impossible" print $ go $ sortBy (comp center) ev
 where
  print (Pt x y) = unwords $ (++"/2") . show <$> [cx, cy, x, y]
  poly = cycle $ toPoly inp
  es = take n $ zip poly (tail poly)
  ps = take n $ zip3 poly (tail poly) (drop 2 poly)
  center@(Pt cx cy) = (poly!!0 + poly!!div n 2) % 2
  upper (Pt x y) = y > cy || y >= cy && x > cx
  initOpen = sum
   [ 1
   | (a,b) <- es
   , upper a /= upper b
   , let (a',b') = if upper b then (a,b) else (b,a)
   , ccw center b' a' < 0
   ]
  ev = [ (b, above, diff)
       | (a,b,c) <- ps
       , upper b
       , let sa' = ccw center b a; sc' = ccw center b c
             sa = if sa' == 0 then sc' else sa'
             sc = if sc' == 0 then sa' else sc'
       , sa == sc
       , let above = ccw b a c * sa < 0
             diff = (if sa < 0 then negate else id) $ sum [1 | x <- [sa', sc'], x /= 0 ]
       ]
  go [] = Just (Pt (cx+1) cy)
  go xs@((p0,_,_):_) = go' initOpen $ zip xs (tail [p | (p,_,_) <- xs] ++ [-p0])
  go' open [] = Nothing
  go' open (((p,a,d),p'):xs)
   | o > 1     = go' o xs
   | otherwise = Just $ if a then (p + p') % 2 else p
   where o = open + d
