-- @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
-- This code is questionable on many levels, so we should ignore it for
-- purposes of setting the time limit.
import Control.Monad
import Data.Char
import Data.List

lev :: String -> String -> Int
lev s "" = length s
lev "" t = length t
lev s@(c:s') t@(d:t')
  | c == d     = lev s' t'
  | otherwise  = 1 + min (min (lev s t') (lev s' t)) (lev s' t')

allPasswords :: [String]
allPasswords = filter ok $ replicateM 8 $ map chr [33..126]
  where
    ok s =
      let c = nub $ map generalCategory s
       in length c > 3 && all (`elem` c) [DecimalNumber, UppercaseLetter, LowercaseLetter]

chosenPasswords :: [String]
chosenPasswords = go allPasswords
  where
    go [] = []
    go (s:ts) = s : go (filter (\t -> lev s t >= 2) ts)

main :: IO ()
main = interact $ unlines . flip take chosenPasswords . read
