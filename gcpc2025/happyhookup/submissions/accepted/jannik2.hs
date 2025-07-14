import Data.Graph
import Data.Function
import Data.IntSet as S

main = interact $ maybe "no" (\n -> "yes\n" ++ show n) . solve . fmap read . words

solve (n:m:xs) = S.lookupGT 0 $ S.intersection ra rb
 where
  (es,[(a,b)]) = splitAt m $ fix (\f x -> case x of (a:b:y) -> (a,b) : f y; _ -> []) xs
  g = buildG (1,n) es
  [ra,rb] = S.fromList . reachable g <$> [a,b]

