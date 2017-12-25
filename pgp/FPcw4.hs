import Data.Char
import Test.QuickCheck

main :: IO ()
main = return ()

chomp :: String -> String
chomp s = takeWhile ( == head s ) s

munch :: String -> String
munch s = take 9 (chomp s)

runs :: String -> [String]
runs []       = []
runs s        = cs : runs( restS )
  where cs    = munch s
        restS = drop (length cs) s

encode :: String -> [(Char,Int)]
encode s = [(head cs, length cs) | cs <- runs s ]

flatten :: [(Char,Int)] -> String
flatten ts = concat [[a, intToDigit b] | (a,b) <- ts]

compress :: String -> String
compress s = flatten (encode s)

decode :: [(Char,Int)] -> String
decode ts = concat [replicate b a | (a,b) <- ts]

expand :: String -> [(Char,Int)]
expand []       = []
expand (a:b:cs) = (a, digitToInt b) : expand cs

decompress :: String -> String
decompress s = if even (length s) then decode (expand s) else ""

inverse :: String -> Bool
inverse xs = decompress (compress xs) == xs
