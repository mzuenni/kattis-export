{-# Language OverloadedStrings, BangPatterns, MultiWayIf #-}
import qualified Data.ByteString.Char8 as C
import Data.Bits
import Data.List

int s = case C.readInt s of Just (x,_) -> x
main = C.getContents >>= print . solve . rd . tail . C.words

binarySearch :: Integral a => (a -> Bool) -> a -> a -> a
binarySearch p = bs
  where
    bs !l !h = let m = div (l + h) 2 in
      if | l + 1 >= h -> l
         | p m        -> bs m h
         | otherwise  -> bs l m

toI = toInteger

data Shape
  = Triangle { dim :: !Int }
  | Circle   { dim :: !Int }
  | Square   { dim :: !Int }

rd (a:b:xs) = (case a of
  "circle" -> Circle
  "square" -> Square
  _        -> Triangle) (int b) : rd xs
rd _ = []

grundy :: Shape -> Int
grundy s = case s of
  Triangle a -> a - 1
  Circle   a -> max 2 $ floor $ fromIntegral a * sqrt 3
  Square   a -> floor $ fromIntegral a * 4 / (sqrt 6 + sqrt 2)

fits :: Shape -> Shape -> Bool
fits (Triangle a1) (Circle   a2) = toI a1^2 < 3*toI a2^2
fits (Triangle a1) (Square   a2) = let [x,y]=toI<$>[a1,a2]; d = 2*y^2 - x^2 in d > 0 && 3*x^4 < 4*d^2
fits (Circle   a1) (Triangle a2) = let [x,y]=toI<$>[a1,a2] in x^2*12 < y^2
fits (Circle   a1) (Square   a2) = toI a1 * 2 < toI a2
fits (Square   a1) (Triangle a2) = let [x,y]=toI<$>[a1,a2] in 3*(y-x)^2 > 4*x^2
fits (Square   a1) (Circle   a2) = toI a1^2 < 2*toI a2^2
fits a b = dim a < dim b

solve shapes = length [ undefined | s <- shapes, t <- [ Triangle, Circle, Square ], test s t $ total `xor` grundy s ]
  where
    total = foldl' (\a -> xor a . grundy) 0 shapes
    test s c !tar = let a = binarySearch ((<=tar) . grundy . c) 1 (2*dim s) in c a `fits` s && grundy (c a) == tar
