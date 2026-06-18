import Data.Map.Strict qualified as M
main = interact $ (\b -> if b then "yes\n" else "no\n") . solve M.empty . tail . words
solve :: M.Map String Bool -> [String] -> Bool
solve s ("dropoff":b:xs) = M.lookup b s == Just True && solve (M.adjust not b s) xs
solve s (_:b:xs) = not (M.member b s) && solve (M.insert b True s) xs
solve s [] = all not $ M.elems s
