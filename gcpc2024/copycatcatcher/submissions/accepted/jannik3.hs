{-# LANGUAGE OverloadedStrings, FlexibleContexts #-}

import Data.Bool
import qualified Data.ByteString.Char8 as B
import qualified Data.Set as S
import qualified Data.Map as M
import Control.Monad.ST
import Data.List
import Data.Array.ST
import Data.Array.Unboxed
import Control.Monad.State.Strict
import Control.Applicative

main = B.getContents >>= evalStateT solve . (,) (M.fromList $ zip (B.singleton <$> (['a'..'z'] ++ ['A'..'Z'])) [0..]) . B.words

rdInt = (\(Just (x, _)) -> x) . B.readInt <$> state (\(l, x : xs) -> (x, (l, xs)))

rd = state $ \(l, x : xs) ->
  let l' = M.insertWith (flip const) x (M.size l) l
   in (l' M.! x, (l', xs))

parse = rdInt >>= \n -> replicateM n rd

mkSTUArray :: (Ix i, MArray (STUArray s) e (ST s)) => (i,i) -> e -> ST s (STUArray s i e)
mkSTUArray = newArray

pre :: [Int] -> UArray Int Int
pre s = listArray (1, length s) $ runST $ do
  last <- mkSTUArray (0,51) (-1)
  let go _ [] = pure []
      go i (c:s) = liftA2 (:) (getC i c) (go (i+1) s)
      getC i c
        | c < 52    = readArray last c >>= \j -> i-j <$ writeArray last c i
        | otherwise = pure (-c - 1)
  go 0 s

solve = do
  haystack <- S.fromList . map pre . tails <$> parse
  let member p = maybe False (isPrefixOf (elems p) . elems) $ S.lookupGE p haystack
  q <- rdInt
  replicateM q (parse >>= liftIO . B.putStrLn . bool "no" "yes" . member . pre)
