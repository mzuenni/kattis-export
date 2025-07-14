main = interact $ maybe "no\n" (\xs -> "yes\n"++unwords (show <$> xs)) . solve . map read . words
solve [n,a,b]
 | a + b - 1 > n = Nothing
 | max a b == 1  = Nothing
 | otherwise     = Just $ if a >= b then f n a b else reverse (f n b a)
f n a b = [n-a+1..n-1] ++ [1..n-a-b+1] ++ [n] ++ reverse [n-a-b+2..n-a]


