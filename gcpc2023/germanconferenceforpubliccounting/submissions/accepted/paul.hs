xs = 0 : take 8 (iterate (*10) 100) ++ ((*) <$> [1..9] <*> take 9 (iterate (\x -> 10*x+1) 1))
main = interact $ (++"\n") . show . (\x -> length $ filter (<= x) xs) . read
