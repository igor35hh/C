<?php

$graph1 = array(
    'start' => array(),
    'start' => array('a' => 6),
    'start' => array('b' => 2), 
    'a' => array(),
    'a' => array('fin' => 1), 
    'b' => array(),
    'b' => array('a' => 3),
    'b' => array('fin' => 5),  
    'fin' => array(), 
);

$graph = array(
    'start' => array(
        array('a' => 6),
        array('b' => 2),
    ),
    'a' => array(
       array('fin' => 1),
    ),
    'b' => array(
       array('a' => 3),
       array('fin' => 5),
    ),
    'fin' => array(
        array('fin' => 0),
    ),
);

$infinity = INF;

$costs = array(
    'a' => 6,
    'b' => 2,
    'fin' => $infinity,
);

$parents = array(
    'a' => 'start',
    'b' => 'start',
    'fin' => NULL,
);

$processed = array();

function find_lowest_cost_node($costs, $processed) {
    $lowest_cost = INF;
    $lowest_cost_node = NULL;
    
    foreach ($costs as $key => $val) {
        if($val < $lowest_cost && !isset($processed[$key])) {
            $lowest_cost = $val;
            $lowest_cost_node = $key;
        }  
    }
    return $lowest_cost_node;
}

$node = find_lowest_cost_node($costs, $processed);
while ($node <> NULL) {
    $cost = $costs[$node];
    $neighbors = $graph[$node];
    foreach ($neighbors as $keys => $values) {
        foreach ($values as $key => $val) {
            $new_cost = $cost + $val;
            if($costs[$key] > $new_cost) {
                $costs[$key] = $new_cost;
                $parents[$key] = $node;
            }
        }
    }
    $processed[$node] = TRUE;
    $node = find_lowest_cost_node($costs, $processed);
 
}

print_r($costs);
