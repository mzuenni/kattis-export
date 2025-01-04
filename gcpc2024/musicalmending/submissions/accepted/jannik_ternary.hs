import qualified Data.ByteString.Char8 as B
import Data.List

main = B.getContents >>= print . solve . map ((\(Just(x,_)) -> x) . B.readInt) . B.words

ternary f lo hi
  | lo + 2 >= hi = head $ sortOn f [lo..hi]
  | f m1 < f m2  = ternary f lo m2
  | otherwise    = ternary f m1 hi
 where
  m1 = div (2 * lo + hi) 3
  m2 = div (lo + 2 * hi) 3

solve (_:ts) = f $ ternary f (-b) b
 where
  b = 3 * 10^5
  f x = sum $ zipWith (\t i -> abs $ t-i-x) ts [0..]
