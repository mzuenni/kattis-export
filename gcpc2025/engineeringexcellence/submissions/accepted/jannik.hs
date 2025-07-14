import qualified Data.ByteString.Char8 as B
import Text.Printf
import Data.Complex
import Data.Function
import Data.List

main = B.getContents >>= printf "%.10f\n" . solve . map ((\(Just(x,_)) -> x) . B.readInt) . B.words

type Pt = Complex Double

eps = 1e-7

cross a b = imagPart (conjugate a * b)
ccw :: Pt -> Pt -> Pt -> Int
ccw a b c = let t = cross (b - a) (c - b) in if t < 0 then 1 else if t > eps then -1 else 0

x = realPart
y = imagPart

lineIntersect :: Pt -> Pt -> Pt -> Pt -> Maybe Pt
lineIntersect a0 a1 b0 b1
  | abs ud < eps = Nothing
  | otherwise = Just $ (x a0 + un * x d21 / ud) :+ (y a0 + un * y d21 / ud)
 where
  d13 = a0 - b0
  d43 = b1 - b0
  d21 = a1 - a0
  un = x d43 * y d13 - y d43 * x d13
  ud = y d43 * x d21 - x d43 * y d21

lineCircleIntersect :: Pt -> Pt -> Pt -> Double -> [Pt]
lineCircleIntersect st d center r
  | det < 0 = []
  | otherwise = [ st + d * ((-b + t) / (2*a) :+ 0) | t <- [sqrt det,-sqrt det]]
 where
  p = st - center
  a = x d^2 + y d^2
  b = 2*dot p d
  c = x p^2 + y p^2 - r^2
  det = b^2 - 4*a*c

dot :: Pt -> Pt -> Double
dot (a :+ b) (c :+ d) = a*c + b*d

dist a b c = magnitude (a - b) + magnitude (b - c)

test :: Pt -> Pt -> Pt -> Pt -> Pt -> Double
test aa a b c cc
  | and [ccw aa a opt <= 0, ccw opt c cc <= 0, dot (a - aa) (opt - a) > -eps, dot (c - cc) (opt - c) > -eps]  = dist a opt c - old
  | otherwise = case find (\p -> magnitude (p - center) < r + eps) (lineIntersect aa a c cc) of
     Just p -> dist a p c - old
     Nothing -> foldl' max 0
      [ dist a p c - old
      | p <- lineCircleIntersect a ((a - aa) * (0 :+ 1)) center r ++ lineCircleIntersect c ((c - cc) * (0 :+ 1)) center r
      , ccw aa a p <= 0, ccw cc c p >= 0
      ]
 where
  r = magnitude (a - c) / 2
  center = (a + c) / 2
  old = dist a b c
  opt = center + (0 :+ 0.5) * (a - c)

solve :: [Int] -> Double
solve (n:cs) = maximum $ take n $ zipWith5 test poly (drop 1 poly) (drop 2 poly) (drop 3 poly) (drop 4 poly)
 where
  poly = cycle $ take n $ fix (\f (x:y:xs) -> (x :+ y) : f xs) (fromIntegral <$> cs)
     
