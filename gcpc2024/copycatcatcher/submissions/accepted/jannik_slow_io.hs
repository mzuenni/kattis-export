import Data.Bool
import Data.Char
import qualified Data.IntMap as IM
import qualified Data.Map as M
import Data.List
import Data.Maybe
import Control.Monad.State.Strict
import Control.Monad


main = getContents >>= evalStateT solve . (,) M.empty . words

rdInt = read <$> state (\(l, x : xs) -> (x, (l, xs)))

var x = 1 == length x && isAlpha (head x)
rd = state $ \(l, x : xs) ->
  let l' = M.insertWith (flip const) x (if var x then M.size l else -M.size l - 1) l
   in (l' M.! x, (l', xs))

parse = rdInt >>= \n -> replicateM n rd

pre = go 0 IM.empty
  where
    go _ _ [] = []
    go i last (c : cs) = bool (maybe 0 (i -) $ IM.lookup c last) c (c < 0) : go (i + 1) (IM.insert c i last) cs

newtype Trie = Trie {unTrie :: IM.IntMap Trie}

emptyTrie = Trie IM.empty

mkTrie :: [Int] -> Trie -> Trie
mkTrie (x : xs) = Trie . IM.alter (Just . mkTrie xs . fromMaybe emptyTrie) x . unTrie
mkTrie _ = id

tMember :: [Int] -> Trie -> Bool
tMember (x : xs) = maybe False (tMember xs) . IM.lookup x . unTrie
tMember _ = const True

solve = do
  haystack <- foldl' (flip mkTrie) emptyTrie . map pre . tails <$> parse
  q <- rdInt
  replicateM q (parse >>= liftIO . putStrLn . bool "no" "yes" . flip tMember haystack . pre)
