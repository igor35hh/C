<?php 

$mentions = array();

$mentions['alex'] = array();
$mentions['alex'][1] = 5.0;
$mentions['alex'][2] = 3.0;
$mentions['alex'][5] = 4.0;

$mentions['rob'] = array();
$mentions['rob'][1] = 4.0;
$mentions['rob'][6] = 1.0;
$mentions['rob'][8] = 2.0;
$mentions['rob'][9] = 3.0;

$mentions['bob'] = array();
$mentions['bob'][2] = 5.0;
$mentions['bob'][3] = 5.0;

$mentions['david'] = array();
$mentions['david'][3] = 4.0;
$mentions['david'][4] = 3.0;
$mentions['david'][6] = 2.0;
$mentions['david'][7] = 1.0;

//print_r($mentions);
//echo "\n";

function distCosine($vecA, $vecB) {
    if (!function_exists('dotProduct')) {
        function dotProduct($vecA, $vecB) {
            $d = 0.0;
            foreach ($vecA as $dim => $value) {
                //echo "$dim $value \n";
                if(isset($vecB[$dim])) {
                    $d += $vecA[$dim] * $vecB[$dim];
                }
            }
            return $d;
        }
    }
    return dotProduct($vecA, $vecB) / sqrt(dotProduct($vecA, $vecA)) / sqrt(dotProduct($vecB, $vecB));
}

function makeRecommendation($userID, $userRates, $nBestUsers, $nBestProducts) {
    
    $matches = array();
    
    foreach ($userRates as $u => $value) {
        if($u != $userID){
            $matches[$u] = distCosine($userRates[$userID], $userRates[$u]);
        }
    }
    
    function cmp($a, $b) { if ($a == $b) { return 0; } return ($a > $b) ? -1 : 1; }
    uasort($matches, 'cmp');
    
    echo "Most suitable for $userID users: \n";
    $i=0;
    foreach ($matches as $key => $value) {
        echo "UserID: $key coeff: $value \n";
        if (++$i==$nBestUsers)
            break;
    }
    
    $sim = array();
    $sim_all = array_sum($matches);
    foreach ($matches as $relatedUser => $value) {
        if($value == 0) { continue; }
        
        foreach ($userRates[$relatedUser] as $product => $value) {
            if(!isset($sim[$product])) {
                $sim[$product] = 0.0;
            }
            $sim[$product] += $userRates[$relatedUser][$product] * $matches[$relatedUser];
        } 
    }
    
    foreach ($sim as $product => $value) {
        $sim[$product] /= $sim_all;
    }
    
    echo "Most suitable products:";
    uasort($sim, 'cmp');
    $i=0;
    foreach ($sim as $key => $value) {
        echo "ProductID: $key suitable coeff: $value \n";
        if (++$i==$nBestProducts) 
            break;
    }
    
    //print_r($matches);
    //echo "\n";
}

makeRecommendation('rob', $mentions, 5, 5);

?>