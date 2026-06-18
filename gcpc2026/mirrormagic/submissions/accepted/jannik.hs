import Data.Bool
import Data.ByteString.Char8 qualified as B
import Data.List
import Data.Maybe
import Data.Ratio
import Data.Set qualified as S

data Pt
  = Pt {x :: !Rational, y :: !Rational}
  deriving (Eq, Ord)

(Pt a b) .+ (Pt c d) = Pt (a + c) (b + d)
(Pt a b) .- (Pt c d) = Pt (a - c) (b - d)
(Pt a b) .* (Pt c d) = a*c + b*d
(Pt a b) ./ x = Pt (a / x) (b / x)
(Pt a b) @* x = Pt (a * x) (b * x)

int :: B.ByteString -> Int
int = fst . fromJust . B.readInt

frac :: Int -> Rational
frac = (% 1) . fromIntegral

main = B.getContents >>= solve . map (map int . B.words) . B.lines

com :: [Pt] -> Pt
com p = foldl' (.+) (Pt 0 0) p ./ frac (length p)

toDouble = fromRational :: Rational -> Double

solve ([n] : xs)
 | any (\p -> (c .- p) .* normal >= 0) alice = putStrLn "impossible" -- this covers the case normal=0
 | S.fromList bob /= S.fromList (mirror <$> alice) = putStrLn "impossible"
 | otherwise = putStrLn "possible"
 where
  (alice, bob) = splitAt n $ map ((\[x, y] -> Pt x y) . map frac) xs
  ca = com alice
  cb = com bob
  c = (ca .+ cb) ./ 2
  normal = ca .- c
  mirror p = let k = ((c .- p) .* normal) / (normal .* normal) in p .+ (normal @* (2 * k))
