import Control.Monad
import Data.Array
import Data.Char
import Data.List
import Data.Maybe
import System.IO

data Card = Plus Int | Times Int deriving (Eq, Ord)

instance Show Card where
  show (Plus x) = "+ " ++ show x
  show (Times x) = "* " ++ show x

instance Read Card where
  readsPrec _ s
    | a == "+ " = [(Plus (read x), c)]
    | a == "* " = [(Times (read x), c)]
    | otherwise  = []
    where
      (a, b) = splitAt 2 s
      (x, c) = span isDigit b

data CardType = A | B | C deriving (Eq, Ord, Show)

getType :: Card -> CardType
getType (Plus x) = if even x then B else C
getType (Times x) = if even x then A else B

type State = (Bool, Bool, Int, Int, Int)

play :: State -> CardType -> Maybe State
play (isOdd, wantOdd, a, b, c) cardType =
  case cardType of
    A -> if a > 0 then Just (False,     not wantOdd, a-1, b, c) else Nothing
    B -> if b > 0 then Just (isOdd,     not wantOdd, a, b-1, c) else Nothing
    C -> if c > 0 then Just (not isOdd, not wantOdd, a, b, c-1) else Nothing

table :: Int -> Int -> Int -> Array State Bool
table aMax bMax cMax = dpTable
  where
    dpBounds = ((False, False, 0, 0, 0), (True, True, aMax, bMax, cMax))
    dpTable = listArray dpBounds $ map win $ range dpBounds
    win state@(isOdd, wantOdd, a, b, c)
      | a == 0 && b == 0 && c == 0 = isOdd == wantOdd
      | otherwise = not $ all (dpTable !) $ mapMaybe (play state) [A, B, C]

main :: IO ()
main = do
  n <- readLn
  cards <- replicateM n $ read <$> getLine
  startValue <- readLn
  let
    count t = length $ filter (== t) $ map getType cards
    dpTable = table (count A) (count B) (count C)

    playGame :: Bool -> [Card] -> State -> IO ()
    playGame isMe cards state
      | null cards  = return ()
      | isMe        = do
          let winning = maybe False (not . (dpTable !)) . play state
              cardType = head $ filter winning [A, B, C]
              card = head $ filter (\card -> getType card == cardType) cards
          print card
          hFlush stdout
          playGame False (delete card cards) (fromJust $ play state cardType)
      | otherwise   = do
          card <- read <$> getLine
          let Just nextState = play state (getType card)
          playGame True (delete card cards) nextState
  
  let startState = (odd startValue, True, count A, count B, count C)
  putStrLn (if dpTable ! startState then "me" else "you")
  hFlush stdout
  playGame (dpTable ! startState) cards startState
