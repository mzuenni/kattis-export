{-# LANGUAGE OverloadedStrings #-}

import Control.Monad
import Control.Monad.State.Strict
import Data.Bool
import qualified Data.ByteString.Char8 as B
import Data.List
import qualified Data.Map as M
import qualified Data.Set as S
import qualified Data.IntMap as IM
import Data.Char

main = B.getContents >>= evalStateT solve . (,) M.empty . B.words

rdInt = (\(Just (x, _)) -> x) . B.readInt <$> state (\(l, x : xs) -> (x, (l, xs)))

var x = 1 == B.length x && isAlpha (B.head x)
rd = state $ \(l, x : xs) ->
  let l' = M.insertWith (flip const) x (if var x then M.size l else -M.size l - 1) l
   in (l' M.! x, (l', xs))

parse = rdInt >>= \n -> replicateM n rd

pre = go 0 IM.empty
  where
    go _ _ [] = []
    go i last (c : cs) = bool (maybe 0 (i -) $ IM.lookup c last) c (c < 0) : go (i + 1) (IM.insert c i last) cs

solve = do
  haystack <- S.fromList . map pre . tails <$> parse
  let member p = maybe False (isPrefixOf p) $ S.lookupGE p haystack
  q <- rdInt
  replicateM q (parse >>= liftIO . B.putStrLn . bool "no" "yes" . member . pre)
