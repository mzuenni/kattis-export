import Data.List

solve :: [Int] -> Int
solve (n:xs) = sum $ map (abs . subtract y) ys
  where
    ys = zipWith (-) xs [0..]
    y = sort ys !! (n`div`2)

main :: IO ()
main = interact $ (++ "\n") . show . solve . map read . words
