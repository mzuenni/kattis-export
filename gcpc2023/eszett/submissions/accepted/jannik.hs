import Data.Char

main = getContents >>= (&"") . map toLower
(x:xs)&acc = xs&(x:acc) >> case (x:xs) of
    ('s':'s':ys) -> ys&('B':acc)
    _ -> pure ()
""&acc = putStrLn $ reverse acc
