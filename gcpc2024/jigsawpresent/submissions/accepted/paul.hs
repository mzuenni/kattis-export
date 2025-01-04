import Control.Monad
import Data.Bits
import Data.List

merge :: Ord a => [a] -> [a] -> [a]
merge [] ys = ys
merge xs [] = xs
merge (x:xs) (y:ys) = if x <= y then x : merge xs (y:ys) else y : merge (x:xs) ys

type Point = (Int, Int)
type Entry = (Int, Int, Int, Int)
type Solution = Maybe (Int, Int)

showMask :: Int -> String
showMask mask = unwords $ map show $ length ones : map (+1) ones
  where ones = filter (testBit mask) [0..31]

showSolution :: Solution -> String
showSolution = unlines . maybe ["yes"] (\(mask1, mask2) -> "no" : map showMask [mask1, mask2])

twoPointer :: Int -> Point -> [Entry] -> [Entry] -> Solution
twoPointer i (x,y) = go
  where
    go (p@(px,py,pmask1,pmask2) : ps) (q@(qx,qy,qmask1,qmask2) : qs) =
      case compare (px+x,py+y) (qx,qy) of
        LT -> go ps (q:qs)
        EQ -> Just (pmask1 .|. qmask2 .|. bit i, pmask2 .|. qmask1)
        GT -> go (p:ps) qs
    go _ _ = Nothing

extend :: Int -> Point -> [Entry] -> [Entry]
extend i (x,y) ps = merge ps (merge qs rs)
  where
    qs = [(px+x, py+y, setBit mask1 i, mask2) | (px, py, mask1, mask2) <- ps]
    rs = [(px-x, py-y, mask1, setBit mask2 i) | (px, py, mask1, mask2) <- ps]

solve :: [Point] -> String
solve = showSolution . msum . take 28 . go 0 [(0,0,0,0)] [(0,0,0,0)]
  where
    go i ps qs (a:as) = twoPointer i a ps qs : go (i+1) qs (extend i a ps) as
    go _ _ _ _ = []

main :: IO ()
main = interact $ solve . map readPair . tail . lines
  where readPair l = let [x,y] = map read $ words l in (x,y)
