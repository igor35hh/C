<?php 

$graph = array(
    'a' => array('b' => -1,'c' => 4),
    'b' => array('c' => 3, 'd' => 2, 'e' => 2),
    'c' => array(),
    'd' => array('b' => 1,'c' => 5),
    'e' => array('d' => -3),
);

$destination = array();
$predecessor = array();

foreach ($graph as $key => $value) {
    $destination[$key] = INF;
    $predecessor[$key] = Null;
}

$destination['a'] = 0;

function find_cost($node, $neighbour, $graph, &$destination, &$predecessor) {
    if($destination[$node] != INF and $destination[$neighbour] > $destination[$node] + $graph[$node][$neighbour]) {
        $destination[$neighbour] = $destination[$node] + $graph[$node][$neighbour];
        $predecessor[$neighbour] = $node;
    }
}

$len = count($graph)-1;
for ($i=0; $i<=$len; $i++) {
    foreach ($graph as $node => $values) {
        foreach ($values as $neighbour => $nvalue) {
            find_cost($node, $neighbour, $graph, $destination, $predecessor);
        }
    }
}

foreach ($graph as $node => $values) {
    foreach ($values as $neighbour => $nvalue) {
        assert( $destination[$neighbour] <= $destination[$node] + $graph[$node][$neighbour] );
    }
}

print_r($destination);
echo "\n";
print_r($predecessor);

?>