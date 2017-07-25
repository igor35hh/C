<?php 

$wordA = 'hish';
$wordB = 'fish';

$cell = array();

for($i = 0, $j = strlen($wordA); $i < $j; $i++) {
    for($p = 0, $k = strlen($wordB); $p < $k; $p++) {
        $cell[$i][$p] = 0;
    }
}

foreach ($cell as $key => $value) {
    foreach ($value as $key => $value) {
        echo "$value ";
    }
    echo "\n";
}

echo "\n";

for($i = 0, $j = strlen($wordA); $i < $j; $i++) {
    for($p = 0, $k = strlen($wordB); $p < $k; $p++) {
        if($wordA[$i] == $wordB[$p]) {
            if($i > 0 && $p > 0) {
                $cell[$i][$p] = $cell[$i-1][$p-1]+1;
            } else {
                $cell[$i][$p] = 1;
            }
        } else {
            if($i > 0 && $p > 0) {
                $cell[$i][$p] =  max($cell[$i-1][$p], $cell[$i][$p-1]);
            } else {
                $cell[$i][$p] = 0;
            }
        }
    }
}

foreach ($cell as $key => $value) {
    foreach ($value as $key => $value) {
        echo "$value ";
    }
    echo "\n";
}

//print_r($cell);

?>