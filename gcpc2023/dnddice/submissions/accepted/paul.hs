import Data.List

weave :: [Int] -> [Int]
weave [] = []
weave (x:xs) = weave (reverse xs) ++ [x]

solve :: [Int] -> [Int]
solve xs = weave [sum xs .. sum (zipWith (*) xs [4,6,8,12,20])]

main :: IO ()
main = interact $ (++ "\n") . unwords . map show . solve . map read . words
