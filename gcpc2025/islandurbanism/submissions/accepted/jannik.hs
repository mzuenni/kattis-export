{-# LANGUAGE ScopedTypeVariables, FlexibleContexts #-}

import qualified Data.ByteString.Char8 as B
import Data.Array.Unboxed
import Data.Array.Base
import qualified Data.IntSet as S
import qualified Data.IntMap as M
import Data.Maybe
import Data.Bifunctor
import Data.Array.ST
import Data.Bits
import Control.Monad
import Control.Applicative
import Data.List
import Data.Function
import Data.Bool
import Control.DeepSeq

main = B.getContents >>= print . solve . map ((\(Just(x,_)) -> x) . B.readInt) . B.words

type Graph = Array Int [(Int,Int)]
oo :: Int = div maxBound 2

toE :: (Int -> (Int,Int)) -> [Int] -> ([(Int,Int)], [(Int,(Int,Int,Int))])
toE _ [] = ([], [])
toE f (a:b:c:xs)
  | ia == ib = (nx, (ia, (a - sa, b - sa, c)) : es)
  | otherwise = ((bool ib ia (ia + 1 == ib || ia > ib + 1), c) : nx, es)
 where
  ((sa,ia),(sb,ib)) = (f a, f b)
  (nx,es) = toE f xs

bitSubsets :: Word -> [Word]
bitSubsets s = takeWhile (/=0) $ iterate (\s2 -> (s2 - 1) .&. s) ((s - 1) .&. s)

insertL :: (Int,Int) -> M.IntMap [Int] -> M.IntMap [Int]
insertL (v,i) = M.alter (Just . maybe [v] (v:)) i

dijkstra :: Monad m => (Int -> [(Int,Int)]) -> Int -> (Int -> m Int) -> (Int -> Int -> m Bool) -> m ()
dijkstra g n rd upd = do
  init <- foldl' (flip insertL) M.empty . filter ((<oo) . snd) <$> sequence [ (,) i <$> rd i | i <- [1..n] ]
  let go m = case M.minViewWithKey m of
       Just ((d,is),m) -> filterM (fmap (== d) . rd) is
        >>= (filterM (uncurry upd) >=> (go . foldl' (flip insertL) m))
          . map (second (+d))
          . concatMap g
       _ -> pure ()
  go init

solveSmall :: Graph -> [Int] -> UArray Word Int
solveSmall g ts = runSTUArray $ do
  let n = snd $ bounds g
      isTerminal :: UArray Int Word = accumArray (.|.) 0 (1,n) (zip ts $ (2^) <$> [0..])
  mem <- newArray (0, fromIntegral $ n * 2 ^ length ts - 1) oo
  let idx i s = s * fromIntegral n + fromIntegral i - 1
      get i = readArray mem . idx i
      mmin s i v = get i s >>= \k -> (k > v) <$ writeArray mem (idx i s) (min v k)
  forM_ [1..n] (\i -> mmin 0 i 0)
  forM_ [1..(2^length ts)-1] $ \s -> do
    forM_ [1..n] $ \i -> do
      when (((isTerminal!i) .&. s) /= 0) $ get i (s `xor` (isTerminal!i)) >>= void . mmin s i
      forM_ (bitSubsets s) $ \s2 -> liftA2 (+) (get i s2) (get i (s `xor` s2)) >>= void . mmin s i
    dijkstra (g !) n (`get` s) (mmin s)
  pure mem

single :: Graph -> S.IntSet -> ((Int,Int,Int,Int), Int)
single g terminals =
  (( dp!(n*(everyone .&. last) + 0) -- conn_l
  , dp!(n*(everyone .&. first) + n - 1) --conn_r
  , connBoth, connLR)
  , dp!(n*(everyone .&. first .&. last) + fromIntegral (S.findMin terminals) - 1))
 where
  (n',n) = (snd $ bounds g, fromIntegral n')
  tmp = S.insert 1 $ S.insert n' terminals
  kv = S.size tmp
  first = complement $ bool 1 0 $ S.member 1 terminals
  last = complement $ bool (bit (kv - 1)) 0 $ S.member n' terminals
  dp = solveSmall g (S.elems tmp)
  everyone = bit kv - 1
  connBoth = dp!(n*everyone + 0)
  connLR = foldl' min connBoth
   [ dp!(n*mask + n - 1) + dp!(n * (everyone `xor` mask) + 0)
   | mask <- [bit (kv - 1),bit (kv - 1)+2 .. bit kv - 1]
   ]


solve (n:m:v:k:xs) = min cutIn (min cutBetween onlyOne)
 where
  (us',xs') = splitAt v xs
  us, nx :: UArray Int Int
  us = listArray (1,v) us'
  getV = let s = M.fromAscList (zip (scanl (+) 0 us') [1..v]) in \i -> fromJust $ M.lookupLT i s
  ((nx,es),terminals') = bimap (first (array (1,v)) . toE getV) (map (\i -> let (s,ii) = getV i in (ii,i-s))) (splitAt (3*m) xs')
  terminals :: Array Int S.IntSet
  terminals = force $ accumArray (flip S.insert) S.empty (1,v) terminals'
  gs :: Array Int Graph
  gs = force $ listArray (1,v)
   [ accumArray (flip (:)) [] (1,us!i) [ (u,(v,c)) | (a,b,c) <- e, (u,v) <- [(a,b),(b,a)] ]
   | (i,e) <- assocs (accumArray (flip (:)) [] (1,v) es :: Array Int [(Int,Int,Int)])
   ]
  (sols,only) = unzip $ uncurry single <$> zip (elems gs) (elems terminals)
  cutBetween = minimum $ take v
   [ connR + go (k - nT) xs nex nTs
   | ((_,connR,_,_):xs,nex,nT:nTs) <- map unzip3 $ tails $ cycle $ zip3 sols (elems nx) (S.size <$> elems terminals)
   ]
  go 0 _ _ _ = 0
  go k ((connL,_,connB,_):xs) (nx:nxs) (numT:nTs) = nx + bool connB connL (k == numT) + go (k - numT) xs nxs nTs
  cutIn = sum (elems nx)
    + sum [ connB | (_,_,connB,_) <- sols ]
    + minimum (take v [ connLR  - connB | (_,_,connB,connLR) <- sols ])
  onlyOne = foldl' min oo [ v | (v,ts) <- zip only (elems terminals), S.size ts == k ]
