import Control.Monad
import Data.Graph
import qualified Data.IntSet as S

ints :: IO [Int]
ints = map read . words <$> getLine

main :: IO ()
main = do
  [n, m] <- ints
  edges <- replicateM m $ (\[a, b] -> (a, b)) <$> ints
  let graph = buildG (1, n) edges
  [sa, sb] <- map (S.fromList . reachable graph) <$> ints
  let s = S.intersection sa sb
  if S.null s then putStrLn "no" else putStrLn "yes" >> print (S.findMin s)
