import Data.Array
import Control.Applicative
import Data.Maybe
import Data.List
import Control.Monad
import System.IO
import Data.Bool

prnt s = putStrLn s >> hFlush stdout

go _ _ (_,_,0,0,0) _ = pure ()
go dp me st cs
  | me = let Just i = dp!st; (Card c n,cs') = hd cs i in prnt (c : (" " ++ show n)) >> go dp False (step i st) cs'
  | otherwise = getLine >>= (\c -> go dp True (step (idx c) st) (delete c cs)) . rdCard

main = do
 n <- read <$> getLine
 cards <- replicateM n (rdCard <$> getLine)
 x <- odd . read <$> getLine
 let [na,nb,nc] = [ sum [ 1 | c <- cards, idx c == i ] | i <- [0..2]]
     mb i = maybe (Just i) (const Nothing)
     bnds = ((False,False,0,0,0),(True,True,na,nb,nc))
     dp = listArray bnds $ f <$> range bnds
      where
       f s@(x,t,a,b,c)
         | a+b+c == 0 = bool Nothing (Just 0) (x == t)
         | otherwise = msum
         [ bool empty (mb 0 $ dp!step 0 s) (a>0)
         , bool empty (mb 1 $ dp!step 1 s) (b>0)
         , bool empty (mb 2 $ dp!step 2 s) (c>0)
         ]
     dpMe = dp
     me = isJust (dp!(x,True,na,nb,nc))
 prnt $ bool "you" "me" me
 go dp me (x,True,na,nb,nc) cards

data Card = Card !Char !Int
 deriving (Eq)
idx (Card c i) = fromEnum (c == '+') + mod i 2
rdCard = (\[[c],i] -> Card c (read i)) . words

hd cs i = let (no,c:rs) = break ((i==) . idx) cs in (c, no++rs)

step 0 (x,t,a,b,c) = (False,not t,a-1,b,c)
step 1 (x,t,a,b,c) = (x,    not t,a,b-1,c)
step 2 (x,t,a,b,c) = (not x,not t,a,b,c-1)
