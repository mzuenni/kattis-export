import Data.Array.ST
import Data.Array.Unboxed
import Data.Maybe
import Data.List
import Control.Monad
import System.IO

prnt s = putStrLn s >> hFlush stdout

go _ _ (_,_,0,0,0) _ = pure ()
go dp me st cs
  | me = dp st >>= \(Just i) -> let (Card c n,cs') = hd cs i in prnt (c : (" " ++ show n)) >> go dp False (step i st) cs'
  | otherwise = getLine >>= (\c -> go dp True (step (idx c) st) (delete c cs)) . rdCard

ifM b t = if b then t else pure False

step 0 (x,t,a,b,c) = (False,not t,a-1,b,c)
step 1 (x,t,a,b,c) = (x,    not t,a,b-1,c)
step 2 (x,t,a,b,c) = (not x,not t,a,b,c-1)

play q st@(_,_,a,b,c) = fmap fst . find snd . zip [0..2] <$> sequence
  [ ifM (a>0) $ not <$> q (step 0 st)
  , ifM (b>0) $ not <$> q (step 1 st)
  , ifM (c>0) $ not <$> q (step 2 st)
  ]

runDP :: Int -> Int -> Int -> UArray (Bool,Bool,Int,Int,Int) Bool
runDP na nb nc = runSTUArray $ do
 dp <- newArray ((False,False,0,0,0),(True,True,na,nb,nc)) False
 let w = writeArray dp
     r = readArray dp
 w (True,True,0,0,0) True >> w (False,False,0,0,0) True
 dp <$ sequence_
  [ play r (x,t,a,b,c) >>= w (x,t,a,b,c) . isJust
  | a <- [0..na], b <- [0..nb], c <- [if a+b == 0 then 1 else 0..nc]
  , x <- [False,True], t <- [False,True]
  ]

main = do
 n <- read <$> getLine
 cards <- replicateM n (rdCard <$> getLine)
 x <- odd . read <$> getLine
 let [na,nb,nc] = [ sum [ 1 | c <- cards, idx c == i ] | i <- [0..2]]
     dp = runDP na nb nc
     me = dp!(x,True,na,nb,nc)
 prnt $ if me then "me" else "you"
 go (play (pure . (dp!))) me (x,True,na,nb,nc) cards

data Card = Card !Char !Int
 deriving (Eq)
idx (Card c i) = fromEnum (c == '+') + mod i 2
rdCard = (\[[c],i] -> Card c (read i)) . words

hd cs i = let (no,c:rs) = break ((i==) . idx) cs in (c, no++rs)
