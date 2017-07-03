package algoritms;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Queue;

public class BreadthSearch {
	
	private static Map<String, List<String>> graph = new HashMap<>();
	
	private static boolean search(String name) {
		
		Queue<String> searchQueue = new ArrayDeque<>(graph.get(name));
		List<String> searched = new ArrayList<>();
		
		while(!searchQueue.isEmpty()) {
			String person = searchQueue.poll();
			if(!searched.contains(person)) {
				if(person_is_seller(person)) {
					System.out.println(person + " is a mango seller");
				} else {
					searchQueue.addAll(graph.get(person));
					searched.add(person);
				}
			}
		}
		
		return false;
		
	}
	
	private static boolean person_is_seller(String name) {
		return name.endsWith("m");
	}

	public static void main(String[] args) {
		
		graph.put("you", Arrays.asList("alice", "bob", "claire"));
		graph.put("bob", Arrays.asList("anuj", "peggy"));
		graph.put("alice", Arrays.asList("peggy"));
		graph.put("claire", Arrays.asList("thom", "jonny"));
		graph.put("anuj", Collections.emptyList());
		graph.put("peggy", Collections.emptyList());
		graph.put("thom", Collections.emptyList());
		graph.put("jonny", Collections.emptyList());
		
		search("you");
		
	}

}
