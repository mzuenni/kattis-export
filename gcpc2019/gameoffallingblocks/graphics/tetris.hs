{-# LANGUAGE NoMonomorphismRestriction, FlexibleContexts, TypeFamilies, RecordWildCards #-}
import Diagrams.Prelude
import Diagrams.Backend.SVG.CmdLine

trapezoid :: Diagram B
trapezoid = fromVertices vertices # closeLine # strokeLoop # translate (1 ^& 1)
  where vertices = map p2 [(1,1),(1.3,1.3),(-1.3,1.3),(-1,1)]

tetrisBlock :: Colour Double -> Diagram B
tetrisBlock baseCol = (square 2 # fc baseCol <> border) # lwG 0 # scaleUToX 1
  where
    topCol  = blend 0.5 baseCol white
    sideCol = blend 0.8 baseCol black
    botCol  = blend 0.3 baseCol black
    params  = zip [topCol,sideCol,botCol,sideCol] [i/4 | i <- [0..3]]
    border = mconcat [trapezoid # fc col # rotateBy ang | (col,ang) <- params]

tetrisBlocks :: Params -> Diagram B
tetrisBlocks Params{..} =
  mconcat [tetrisBlock baseCol # translate v | v <- offsets] # alignBL

data Piece = I | J | L | O | S | T | Z deriving (Eq,Ord,Enum,Show)

data Params = Params { offsets :: [V2 Double], baseCol :: Colour Double }

params :: Piece -> Params
params I = Params (map r2 [(0,0),(1,0),(2,0),(3,0)]) cyan
params J = Params (map r2 [(0,0),(1,0),(2,0),(0,1)]) blue
params L = Params (map r2 [(0,0),(1,0),(2,0),(2,1)]) orange
params O = Params (map r2 [(0,0),(1,0),(0,1),(1,1)]) yellow
params S = Params (map r2 [(0,0),(1,0),(1,1),(2,1)]) lime
params T = Params (map r2 [(0,0),(1,0),(2,0),(1,1)]) magenta
params Z = Params (map r2 [(1,0),(2,0),(0,1),(1,1)]) red

tetrisPiece :: Piece -> Int -> Diagram B
tetrisPiece p k = tetrisBlocks ps'
  where
    ps  = params p
    ps' = ps { offsets = offsets ps # rotateBy (fromIntegral k / 4) } 

labelledPiece :: Piece -> Diagram B
labelledPiece p = vsep 1.5 [tetrisPiece p 0 # centerX, text (show p) # font "monospace"]

allPieces :: Diagram B
allPieces = hsep 1 $ map labelledPiece [I .. Z]

walls :: Diagram B
walls = fromVertices (map p2 [(0,5),(0,0),(10,0),(10,5)])
          # strokePath # moveOriginBy (5 ^& 5) # scale 1.01 # moveOriginBy ((-5) ^& (-5))

sampleInteraction :: Diagram B
sampleInteraction =
  vsep 0.2 [ mconcat [ tetrisPiece S 1 # translate (0 ^& 0)
                     , tetrisPiece O 0 # translate (3 ^& 0)
                     , tetrisPiece T 2 # translate (1 ^& 1)
                     , tetrisPiece J 1 # translate (8 ^& 0)
                     , tetrisPiece I 0 # translate (5 ^& 1)
                     ] <> walls
           , hcat [    text (show k) # font "monospace" # scale 0.4
                    <> square 1 # lw none | k <- [1..10]] # alignL
           ]

orientedPieces :: Diagram B
orientedPieces = mconcat [ tetrisPiece I 1 # translate ( 0 ^& 0)
                         , tetrisPiece J 2 # translate ( 2 ^& 0)
                         , tetrisPiece L 2 # translate ( 6 ^& 0)
                         , tetrisPiece O 0 # translate (10 ^& 0)
                         , tetrisPiece S 1 # translate (13 ^& 0)
                         , tetrisPiece T 1 # translate (16 ^& 0)
                         , tetrisPiece Z 1 # translate (19 ^& 0)
                         , square 1 # scaleY 0.6 # scaleX 22 # translate (10.5 ^& 1.5)
                                    # lw 0 # fc gray
                         ]

exampleRun :: [Diagram B]
exampleRun = [ tetrisPiece J 2 # translate (0 ^& 0)
             , tetrisPiece I 1 # translate (3 ^& 0)
             , tetrisPiece Z 1 # translate (4 ^& 0)
             , tetrisPiece O 0 # translate (6 ^& 0)
             , tetrisPiece L 2 # translate (0 ^& 2)
             , tetrisPiece S 1 # translate (8 ^& 0)
             ]

exampleFrame :: Int -> Diagram B
exampleFrame k = mconcat (take k exampleRun) <> walls

main :: IO ()
main = mainWith $ sampleInteraction # scaleUToY 150 # frame 25
