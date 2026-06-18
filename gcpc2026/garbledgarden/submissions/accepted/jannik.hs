{-# LANGUAGE LambdaCase #-}
import Data.List
import Data.Array.ST
import Data.Array
import Control.Monad.ST
import Control.Monad.Writer
import Control.Monad
import Data.Monoid

euler g' = runST $ do
 g <- (thaw g' :: ST s (STArray s Int [(Int, Int)]))
 let dfs i = lift (readArray g i) >>= \case
      [] -> pure ()
      ((k,j):rest) -> lift (writeArray g i rest) >> dfs k >> tell (Endo (j:)) >> dfs i
 fmap (filter (not . null) . map (`appEndo` [])) $ forM (indices g') $ \i -> execWriterT (dfs i)

main = interact $ output . solve . map read . words
 where
  output xs = unlines . map (unwords . map show) $ [length xs] : concat [[[length x], x] | x <- xs]

solve (n:p)
  | p == p_sorted = []
  | length cycles <= 2 = cycles
  | otherwise = [ concat cycles, reverse $ last <$> cycles ]
 where
  p_sorted = sort p
  g = accumArray (flip (:)) [] (1,n)
    $ filter (\(a,(b,_)) -> a /= b)
    $ zipWith3 (\i p p' -> (p', (p, i))) [1..n] p p_sorted 
  cycles = euler g
