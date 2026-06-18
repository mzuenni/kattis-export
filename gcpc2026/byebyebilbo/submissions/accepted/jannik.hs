import Data.Graph
import Data.Array.IArray
import Control.Monad.Trans.Writer
import Data.Monoid

main = interact $ unwords . map show . (\xs -> length xs : xs) . solve . map read . words

solve (n : k : pas) = execWriter (dfs 1) `appEndo` []
 where
  t = buildG (1, n) $ zip pas [2 .. n]
  dfs i = do
   d <- foldl max 1 . map succ <$> mapM dfs (t!i)
   if d >= k || i == 1
      then 0 <$ tell (Endo (i:))
      else pure d
