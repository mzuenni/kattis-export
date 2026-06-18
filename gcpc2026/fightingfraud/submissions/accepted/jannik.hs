import Data.Set qualified as S
main = interact $ (\b -> if b then "yes\n" else "no\n") . solve S.empty S.empty . tail . words
solve :: S.Set String -> S.Set String -> [String] -> Bool
solve s se ("dropoff":b:xs) = S.member b s && solve (S.delete b s) se xs
solve s se (_:b:xs) = not (S.member b se) && solve (S.insert b s) (S.insert b se) xs
solve s _ [] = S.null s
