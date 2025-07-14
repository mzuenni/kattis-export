import qualified Data.ByteString.Char8 as B
import Data.Graph
import Data.Function
import Data.IntSet as S

main = B.getContents >>= putStrLn . maybe "no" (\n -> "yes\n" ++ show n) . solve . fmap ((\(Just(x,_)) -> x) . B.readInt) . B.words

solve (n:m:xs) = S.lookupGT 0 $ S.intersection ra rb
 where
  (es,[(a,b)]) = splitAt m $ fix (\f x -> case x of (a:b:y) -> (a,b) : f y; _ -> []) xs
  g = buildG (1,n) es
  [ra,rb] = S.fromList . reachable g <$> [a,b]

