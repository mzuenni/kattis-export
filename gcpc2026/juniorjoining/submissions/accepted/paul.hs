import Data.Function
import Data.List
import Data.Maybe
import qualified Data.ByteString.Char8 as B

solve :: [[Int]] -> Int
solve xs = base + sum (drop (length xs `div` 2) $ sort $ concatMap process diffs)
  where
    base = sum $ map (!! 1) xs
    diffs = groupBy ((==) `on` fst) $ sort [(c, l-r) | [l, r, c] <- xs]
    process ps = zipWith (+) (map snd ps) cs
      where
        n = length ps
        c = fst (head ps)
        cs = replicate (n`div`2) (-c) ++ [0 | odd n] ++ replicate (n`div`2) c

main :: IO ()
main = B.getContents >>= print . solve . map parseLine . tail . B.lines
  where parseLine = map (fst . fromJust . B.readInt) . B.words
