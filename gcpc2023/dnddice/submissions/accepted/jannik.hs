import Data.Array
import Data.List
import Data.Function

main = interact $ unwords . map show . solve . map read . words

vals = [4,6,8,12,20]

solve cnt = reverse $ sortBy (on compare (final!)) [sum cnt .. r]
  where
    r = sum $ zipWith (*) cnt vals
    f count c = accumArray (+) 0 (0,r) [ (i+d,x) | (i,x) <- assocs count, x > 0, d <- [1..c] ]
    final = foldl' f (listArray (0,r) $ 1 : [0,0..]) $ concat $ zipWith replicate cnt vals
