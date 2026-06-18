import Data.ByteString.Char8 qualified as B
import Data.Array.ST
import Data.Array.IArray
import Data.Graph
import Control.Monad

int = (\(Just (x,_)) -> x) . B.readInt

main = B.getContents >>= putStrLn . solve . map (map int . B.words) . B.lines
solve ([n,m]:es')
  | any (\(a,b) -> (d1!a) + (dn!b) == (dn!1)) (edges g) = "possible"
  | otherwise = "impossible"
 where
  g = buildG (1, n) $ concat [[(a,b),(b,a)] | [a,b] <- es']
  bfs i = runSTUArray $ do
   d <- newArray (1,n) (n + 10)
   writeArray d i 0
   let go [] [] = pure d
       go [] r = go (reverse r) []
       go (i:l) r = do
         d' <- succ <$> readArray d i
         ns <- filterM (fmap (> d') . readArray d) (g!i)
         forM_ ns (\j -> writeArray d j d')
         go l (ns ++ r)
   go [i] []
  d1 = bfs 1
  dn = bfs n
