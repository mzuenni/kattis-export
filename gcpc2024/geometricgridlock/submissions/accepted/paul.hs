import Data.List

solve :: Int -> Int -> Maybe [String]
solve h w
  | h*w `mod` 5 /= 0   = Nothing
  | w `mod` 5 /= 0     = transpose <$> solve w h
  | h == 1 && w ==  5  = Just ["IIIII"]
  | h == 1             = Nothing
  | h == 2 && w ==  5  = Nothing
  | h == 2 && w == 10  = Just ["LLLLYYYYPP", "LIIIIIYPPP"]
  | h == 2 && w == 15  = Just ["LLLLNNNYYYYNNPP", "LIIIIINNYNNNPPP"]
  | h == 2             = zipWith (++) <$> solve h 10 <*> solve h (w-10)
  | h == 3 && w ==  5  = Just ["UUUPP", "UYUPP", "YYYYP"]
  | h == 4 && w ==  5  = Just ["UUUPP", "UFUPP", "FFFYP", "FYYYY"]
  | h == 5 && w ==  5  = Just ["UUUPP", "UXUPP", "XXXPT", "LXTTT", "LLLLT"]
  | h == 6 && w ==  5  = Just ["UUUZZ", "UNUZI", "NNZZI", "NVVVI", "NPPVI", "PPPVI"]
  | h == 7 && w ==  5  = Just ["UUUPP", "UWUPP", "YWWPI", "YYWWI", "YPPPI", "YPPLI", "LLLLI"]
  | w > 5              = map (take w . cycle) <$> solve h 5
  | otherwise          = (++) <$> solve 5 w <*> solve (h-5) w

main :: IO ()
main = interact $ unlines . process . map read . words
  where process [h, w] = maybe ["no"] ("yes":) $ solve h w
