main = interact $ show . solve . read
solve n
  | n < 10    = n + 1
  | otherwise = length $ concatMap (takeWhile (<=n)) $ ((10^) <$> [1..]) : [ iterate ((d+) . (*10)) d | d <- [1..9] ]
