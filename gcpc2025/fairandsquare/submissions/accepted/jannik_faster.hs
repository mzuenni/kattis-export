{-# LANGUAGE FlexibleContexts #-}
import Control.Monad
import Control.Monad.ST
import Control.Monad.Trans
import Control.Monad.Trans.Maybe
import Data.Array.ST
import qualified Data.ByteString.Char8 as B
import Data.Maybe
import Data.Array.Unboxed (UArray, (!))
import Data.List

main = B.getContents >>= print . solve . B.words

mkA :: (Int,Int) -> ST s (STUArray s Int Bool)
mkA bnds = newArray bnds False
mThaw :: UArray Int Bool -> ST s (STUArray s Int Bool)
mThaw = thaw

solve (h':w':grid) = head $ catMaybes [test x | x <- reverse [2..base], rem area (x*x) == 0, rem base x == 0]++[1]
 where
  idx i j = w * i + j
  rd d i j = lift $ readArray d (idx i j)
  wr d i j = writeArray d (idx i j) True
  lgcd f n r = foldl' gcd r [ length g | g <- group (f <$> [0..n-1]), not $ head g ]
  [h,w] = (\(Just(x,_)) -> x) . B.readInt <$> [h',w']
  area = sum $ B.count '#' <$> grid
  base = foldl' gcd area $ [ lgcd (\j -> init ! idx i j) w area | i <- [0..h-1] ] ++ [ lgcd (\i -> init ! idx i j) h area | j <- [0..w-1] ]
  init = runSTUArray $ do
   d <- mkA (0,h*w-1)
   zipWithM_ (\i -> mapM_ (wr d i) . B.elemIndices '.') [0..] grid
   pure d
  test x = runST $ do
   done <- mThaw init
   runMaybeT $ x <$ do
    let set i j
         | i >= h || j >= w = mzero
         | otherwise = rd done i j >>= \b -> if b then mzero else lift (wr done i j)
    forM_ ((,) <$> [0..h-1] <*> [0..w-1]) $ \(i,j) -> rd done i j >>= \b -> unless b $
      sequence_ $ set <$> [i..i+x-1] <*> [j..j+x-1]
