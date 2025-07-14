{-# LANGUAGE FlexibleContexts #-}

import Control.Monad
import Control.Monad.ST
import Control.Monad.Trans
import Control.Monad.Trans.Maybe
import Data.Array.ST
import qualified Data.ByteString.Char8 as B
import Data.Maybe

main = B.getContents >>= print . solve . B.words

mkA :: (Int,Int) -> ST s (STUArray s Int Bool)
mkA bnds = newArray bnds False

solve (h':w':grid) = last $ 1 : catMaybes [test x | x <- [2..minimum [area,h,w]], rem area (x*x) == 0]
 where
  [h,w] = (\(Just(x,_)) -> x) . B.readInt <$> [h',w']
  area = sum $ B.count '#' <$> grid
  idx i j = w * i + j
  test x = runST $ do
   done <- mkA (0,h*w-1)
   let rd i j = lift $ readArray done (idx i j)
       wr i j = writeArray done (idx i j) True
   zipWithM_ (\i -> mapM_ (wr i) . B.elemIndices '.') [0..] grid
   runMaybeT $ x <$ do
    let set i j
         | i >= h || j >= w = mzero
         | otherwise = rd i j >>= \b -> if b then mzero else lift (wr i j)
    forM_ ((,) <$> [0..h-1] <*> [0..w-1]) $ \(i,j) -> rd i j >>= \b -> unless b $
      sequence_ $ set <$> [i..i+x-1] <*> [j..j+x-1]
