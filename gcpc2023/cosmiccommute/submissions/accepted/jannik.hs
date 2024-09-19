import qualified Data.ByteString.Char8 as C
import Data.Function
import Control.Monad
import Data.Array.Unboxed
import Data.Array.ST
import Text.Printf (printf)
import Data.List
import Data.Graph

int s = case C.readInt s of Just (x,_) -> x
red (a,b) = let g = gcd a b in (div a g, div b g)

main = C.getContents >>= uncurry (printf "%i/%i\n") . red . solve . map int . C.words

pairs (u:v:xs) = (u,v) : (v,u) : pairs xs
pairs _ = []

bfs :: Graph -> Vertex -> UArray Vertex Int
bfs g s = runSTUArray $ do
  dist <- newArray (bounds g) maxBound
  writeArray dist s 0
  let step _ [] = pure ()
      step d ns = (\j -> readArray dist j >>= \d' -> if d' > d+1 then True <$ writeArray dist j (d+1) else pure False) `filterM` concatMap (g!) ns >>= step (d+1)
  dist <$ step 0 [s]

solve :: [Int] -> (Int,Int)
solve (n:m:k:xs) = (foldl' min ((dist_s!n)*(k-1)) [ (dist_s!i)*(k-1) + sum_t - dist_t!i | i <- wormholes ], k-1)
  where
    (wormholes,es) = splitAt k xs
    g = buildG (1,n) $ pairs es
    (dist_s, dist_t) = (bfs g 1, bfs g n)
    sum_t = sum $ (dist_t!) <$> wormholes
