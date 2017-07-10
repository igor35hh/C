package algoritms;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class dijkstraAlgorithm {
	
	private static Map<String, Map<String, Double>> graph = new HashMap<>();
	private static List<String> processed = new ArrayList<>();
	
	private static String findlowestCostNode(Map<String, Double> costs) {
		Double lowestCost = Double.POSITIVE_INFINITY;
		String lowestCostNode = null;
		
		for(Map.Entry<String, Double> node: costs.entrySet()) {
			Double cost = node.getValue();
			if (cost < lowestCost && !processed.contains(node.getKey())) {
				lowestCost = cost;
				lowestCostNode = node.getKey();
			}
		}
		
		return lowestCostNode;
		
	}

	public static void main(String[] args) {
		
		graph.put("start", new HashMap<>());
		graph.get("start").put("a", 6.0);
		graph.get("start").put("b", 2.0);
		
		graph.put("a", new HashMap<>());
		graph.get("a").put("fin", 1.0);
		
		graph.put("b", new HashMap<>());
		graph.get("b").put("a", 3.0);
		graph.get("b").put("b", 5.0);
		
		graph.put("fin", new HashMap<>());
		
		Map<String, Double> costs = new HashMap<>();
		costs.put("a", 6.0);
		costs.put("b", 2.0);
		costs.put("fin", Double.POSITIVE_INFINITY);
		
		Map<String, String> parents = new HashMap<>();
		parents.put("a", "start");
		parents.put("b", "start");
		parents.put("fin", null);
		
		String node = findlowestCostNode(costs);
		while (node != null) {
			Double cost = costs.get(node);
			Map<String, Double> neighbors = graph.get(node);
			for (String n : neighbors.keySet()) {
				double newCost = cost + neighbors.get(n);
				if (costs.get(n) > newCost) {
					costs.put(n, newCost);
					parents.put(node,  node);
				}
			}
			processed.add(node);
			node = findlowestCostNode(costs);
		}
		
		System.out.println(costs);
		
	}

}
