{-# LANGUAGE OverloadedStrings, TypeSynonymInstances #-}

import qualified Data.ByteString.Char8 as B
import qualified Data.Array.Unboxed as A
import qualified Data.Map.Strict as M
import Data.Maybe
import Data.Bool
import Data.List

type Hash = Int
instance Semigroup Hash where
  (<>) = (+)
instance Monoid Hash where
  mempty = 0
neg :: Hash -> Hash
neg = negate

hashes :: [Hash]
hashes = iterate (\c -> mod (c * 123456789) (10^9+7)) 1

data Trie = Trie !(M.Map Char Trie) !Hash
emptyTrie = Trie M.empty mempty

buildTrie :: [(String, Hash)] -> Trie
buildTrie = foldl' insertTrie emptyTrie
insertTrie t (str,h) = go t str
 where
  go (Trie g hs) s = case s of
   [] -> Trie g (hs <> h)
   (c:cs) -> Trie (M.alter (Just . flip go cs . fromMaybe emptyTrie) c g) hs

data AC = AC (M.Map Char AC) !Hash
hash (AC _ h) = h

build :: [(B.ByteString, Hash)] -> AC
build s = let res = go t 0 (M.fromList [ (i, res) | i <- ' ' : ['a'..'z']]) in res
 where
  t = buildTrie [ (B.unpack b, h) | (b,h) <- s ]
  go (Trie ch h) h' old = AC (M.union ch' old) (h <> h')
   where
    ch' = M.mapWithKey (\c t -> let AC ago ah = old M.! c in go t ah ago) ch
walk a = mconcat . map hash . scanl' (\(AC nx _) c -> nx M.! c) a . B.unpack

ints :: B.ByteString -> [Int]
ints = map ((\(Just(x,_)) -> x) . B.readInt) . B.words

main :: IO ()
main = B.getContents >>= mapM_ (B.putStrLn . bool "no" "yes") . solve . filter ((>0) . B.length) . B.lines

solve :: [B.ByteString] -> [Bool]
solve (header:xs) = (==mempty) . walk ac <$> articles
 where
  [n,m,k] = ints header
  (names,xs') = splitAt n xs
  (rivalries,articles) = splitAt m xs'
  rivHash :: A.UArray Int Hash
  rivHash = A.accumArray (<>) 0 (1,n) $ concat $ zipWith (\h r -> let [a,b] = ints r in [(a,neg h),(b,h)]) hashes rivalries
  ac = build $ zip names (A.elems rivHash)
