solve :: [Int] -> IO ()
solve [n, a, b]
  | a+b > n+1         = putStrLn "no"
  | a == 1 && b == 1  = putStrLn "no"
  | a == 1            = yes $ [n] ++ [1..n-b] ++ [n-1,n-2..n-b+1]
  | otherwise         = yes $ [n-a-b+2..n-b] ++ [1..n-a-b+1] ++ [n,n-1..n-b+1]
  where yes hs = putStrLn "yes" >> putStrLn (unwords $ map show hs)

main :: IO ()
main = getLine >>= solve . map read . words
