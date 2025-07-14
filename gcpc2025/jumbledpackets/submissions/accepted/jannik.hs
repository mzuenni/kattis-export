import Data.List
main = interact $ solve . words

findRot s = take (length s) $ head [ c1:cs | (c0:c1:cs) <- tails (cycle s), c1 == '2' && c0 /= '2']

solve ['E':_,_,s] = case elemIndex '1' s of
 Nothing -> s
 Just i -> replicate (i+1) '2' ++ drop (i+1) s
solve [_,_,s]
  | elem '2' s = zipWith (%) s' $ tail s' ++ ['0']
  | otherwise = s
 where
  s' = if all (=='2') s then s else findRot s
  '2'%'2' = '0'
  '2'%_ = '1'
  c%_ = c
