{-# LANGUAGE LambdaCase, OverloadedStrings #-}
import qualified Data.ByteString.Char8 as B
import Control.Monad.State.Strict

rd = state (\(x:xs) -> (x,xs))
int = (\(Just (x,_)) -> x) . B.readInt <$> rd
main = B.getContents >>= output . evalState solve . B.words
output xs = mapM_ print (reverse xs)
solve = do
 (n,_) <- (,) <$> int <*> int
 let go 0 acc _ = pure acc
     go i acc waves = rd >>= \case
      "!" -> (,,) <$> int <*> int <*> int >>= go (i-1) acc . (:waves)
      _ -> int >>= \p -> go (i-1) (-calc waves p : acc) waves
     calc w q = sum [ (mod (q-p) 4 - 1) * a | (p,l,a) <- w, p <= q, p + l > q, even (q - p) ]
 go n [] [] 
