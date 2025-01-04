-- @EXPECTED_RESULTS@: ACCEPTED, RUN_TIME_ERROR, TIME_LIMIT_EXCEEDED
import Data.Char
import Data.List

data Op = I | H | V | R deriving (Show, Read, Eq)

instance Semigroup Op where
  I <> x = x
  x <> I = x
  x <> y | x == y = I
  H <> V = R
  V <> H = R
  H <> R = V
  R <> H = V
  V <> R = H
  R <> V = H

instance Monoid Op where
  mempty = I

(#) :: Op -> Char -> Char
I # c = c
H # 'b' = 'd'
H # 'd' = 'b'
H # 'p' = 'q'
H # 'q' = 'p'
V # 'b' = 'p'
V # 'd' = 'q'
V # 'p' = 'b'
V # 'q' = 'd'
R # 'b' = 'q'
R # 'd' = 'p'
R # 'p' = 'd'
R # 'q' = 'b'

(##) :: Op -> String -> String
I ## s = s
H ## s = map (H #) (reverse s)
V ## s = map (V #) s
R ## s = map (R #) (reverse s)  

solve :: String -> String -> String
solve s t = mconcat (map (read . pure . toUpper) t) ## s

main :: IO ()
main = interact $ (++ "\n") . (\[s, t] -> solve s t) . words
