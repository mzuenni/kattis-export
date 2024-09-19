import Control.Monad
import Data.List

type Point = (Int,Int)

collinear :: Point -> Point -> Point -> Bool
collinear (x1,y1) (x2,y2) (x3,y3) = (x2-x1)*(y3-y1) == (x3-x1)*(y2-y1)

removeLine :: [Point] -> [Point]
removeLine (p:q:qs) = [r | r <- qs, not $ collinear p q r]

fewLines :: Int -> [Point] -> Bool
fewLines _ [] = True
fewLines 0 _  = False
fewLines n ps = any (fewLines (n-1) . removeLine) $ take (product [1..n+1]) $ permutations ps

readPoint :: String -> Point
readPoint = (\[a,b] -> (a,b)) . map read . words

main :: IO ()
main = do
  points <- map readPoint . tail . lines <$> getContents
  putStrLn $ if fewLines 3 points then "possible" else "impossible"
