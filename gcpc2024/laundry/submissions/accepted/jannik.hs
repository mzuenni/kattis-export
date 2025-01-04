import Data.List
import Control.Monad
import Control.Monad.State.Strict

rd = state (\(x:xs) -> (read x,xs))

main = getContents >>= evalStateT (rd >>= \t -> replicateM_ t (replicateM 8 rd >>= liftIO . print . solve)) . words
solve [k,a,b,c,ab,bc,ac,abc] = minimum [ ans (([a,b,c]!!) <$> [i,j,k]) [i🔧j,i🔧k,j🔧k] | [i,j,k] <- permutations [0..2] ]
 where
  i🔧j = [ab,ac, ab,bc, ac,bc] !! (i*2 + if i < j then j-1 else j)
  f n = max 0 $ div (n + k - 1) k
  r n = k * f n - n
  w xs = sum (f <$> xs) + f (abc - sum (r <$> xs))
  ans [a,b,c] [ab,ac,bc] = w [a' + ac', b + bc', c + ac + bc - ac' - bc']
   where
    a' = a + ab
    ac' = min (r a') ac
    bc' = min (r b) bc
