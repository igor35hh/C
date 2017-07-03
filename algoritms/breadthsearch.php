<?php 

$graph = array(
    'you' => array('alice', 'bob', 'claire'),
    'bob' => array('anuj', 'peggy'),
    'alice' => array('peggy'),
    'claire' => array('thom', 'jonny'),
    'anuj' => array(),
    'peggy' => array(),
    'thom' => array(),
    'jonny' => array(),  
);

function person_is_seller($name) {
    $value = substr($name, -1);
    return strcasecmp($value,'m'); 
}
    
function searchseller($name, $graph) {
      
    $searchQueue = array();
    $searched = array();
        
    $searchQueue[$name] = $graph[$name];
    
    $n = 0;
    $c = count($searchQueue);
       
    while ($n < $c) {
        $keys = array_keys($searchQueue);
        $key = $keys[$n];
        $value = $searchQueue[$key];
        $n += 1;
        
        if(!isset($searched[$key])) {  
            if(!person_is_seller($key)) {
                echo "$key is a mango seller";
                break;
            } else {
                unset($searchQueue[$key]);
                foreach ($value as $k => $v) {
                    $searchQueue[$v] = $graph[$v];
                }
                $searched[$key] = array();
                $c = count($searchQueue);
                $n = 0;       
            }
            
        } else {
            echo "end";
        }
        
    }
        
}
    
searchseller('you', $graph);
