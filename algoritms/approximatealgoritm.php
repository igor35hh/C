<?php

$states_needed = array('mt', 'wa', 'or', 'id', 'nv', 'ut', 'ca', 'az');

$stations = array(
    'kone' => array('id', 'nv', 'ut'),
    'ktwo' => array('wa', 'id', 'mt'),
    'kthree' => array('or', 'nv', 'ca'),
    'kfour' => array('nv', 'ut'),
    'kfive' => array('ca', 'az'),
);

$final_stations = array();

foreach ($states_needed as $state) {
    $best_station = Null;
    $states_covered = array();
    foreach ($stations as $station => $states) {
        $covered = array_uintersect($states_needed, $states, "strcasecmp");
        if(count($covered) > count($states_covered)) {
            $best_station = $station;
            $states_covered = $covered;
        }
    }
    $states_needed = array_diff($states_needed, $states_covered);
    array_push($final_stations, $best_station);
       
}

//print_r($final_stations);

foreach ($final_stations as $key => $val) {
    echo "$val ";  
}